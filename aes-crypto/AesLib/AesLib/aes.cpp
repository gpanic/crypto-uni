#include <algorithm>
#include <iostream>
#include <fstream>

#include <Windows.h>
#include <bcrypt.h>

#include "aes2.h"
#include "aes_statics.h"
#include "print_utils.h"
#include "array_utils.h"
#include "base64.h"

#include "wmmintrin.h";
#include <stdint.h>;

using namespace std;

Aes::Aes(int key_size) :nb(4), block_size(16)
{
	this->key_size = key_size;
	this->nk = key_size / 4;
	this->nr = nk + 6;
	this->key_schedule_size = (nr + 1) * block_size;
	fill(begin(this->key), end(this->key), 0x00);
	fill(begin(this->key_schedule), end(this->key_schedule), 0x00);
}

Aes::Aes(unsigned char *key, int key_size) : nb(4), block_size(16)
{
	this->key_size = key_size;
	this->nk = key_size / 4;
	this->nr = nk + 6;
	this->key_schedule_size = (nr + 1) * block_size;

	fill(begin(this->key), end(this->key), 0x00);
	fill(begin(this->key_schedule), end(this->key_schedule), 0x00);

	for (int i = 0; i < key_size; ++i)
	{
		this->key[i] = key[i];
	}
}

__m128i keyexpand(__m128i k, __m128i kg)
{
	k = _mm_xor_si128(k, _mm_slli_si128(k, 4));
	k = _mm_xor_si128(k, _mm_slli_si128(k, 4));
	k = _mm_xor_si128(k, _mm_slli_si128(k, 4));
	kg = _mm_shuffle_epi32(kg, _MM_SHUFFLE(3, 3, 3, 3));
	return _mm_xor_si128(k, kg);
}

void Aes::EncryptBlockAesNi(unsigned char * ptxt, unsigned char * out)
{
	__declspec(align(16)) unsigned char keya[16];
	for (int i = 0; i < 16; ++i)
	{
		keya[i] = key[i];
	}
	__m128i k0 = _mm_load_si128((__m128i *)keya);
	__m128i k1 = keyexpand(k0, _mm_aeskeygenassist_si128(k0, 0x01));
	__m128i k2 = keyexpand(k1, _mm_aeskeygenassist_si128(k1, 0x02));
	__m128i k3 = keyexpand(k2, _mm_aeskeygenassist_si128(k2, 0x04));
	__m128i k4 = keyexpand(k3, _mm_aeskeygenassist_si128(k3, 0x08));
	__m128i k5 = keyexpand(k4, _mm_aeskeygenassist_si128(k4, 0x10));
	__m128i k6 = keyexpand(k5, _mm_aeskeygenassist_si128(k5, 0x20));
	__m128i k7 = keyexpand(k6, _mm_aeskeygenassist_si128(k6, 0x40));
	__m128i k8 = keyexpand(k7, _mm_aeskeygenassist_si128(k7, 0x80));
	__m128i k9 = keyexpand(k8, _mm_aeskeygenassist_si128(k8, 0x1b));
	__m128i k10 = keyexpand(k9, _mm_aeskeygenassist_si128(k9, 0x36));

	__declspec(align(16)) unsigned char ptxta[16];
	for (int i = 0; i < 16; ++i)
	{
		ptxta[i] = ptxt[i];
	}

	__m128i state = _mm_load_si128((__m128i *)ptxta);
	state = _mm_xor_si128(state, k0);
	state = _mm_aesenc_si128(state, k1);
	state = _mm_aesenc_si128(state, k2);
	state = _mm_aesenc_si128(state, k3);
	state = _mm_aesenc_si128(state, k4);
	state = _mm_aesenc_si128(state, k5);
	state = _mm_aesenc_si128(state, k6);
	state = _mm_aesenc_si128(state, k7);
	state = _mm_aesenc_si128(state, k8);
	state = _mm_aesenc_si128(state, k9);
	state = _mm_aesenclast_si128(state, k10);

	__declspec(align(16)) unsigned char outa[16] = { 0x00 };
	_mm_store_si128((__m128i *)outa, state);

	for (int i = 0; i < 16; ++i)
	{
		out[i] = outa[i];
	}
}

void Aes::EncryptBlock(unsigned char * ptxt, unsigned char * out)
{
	ExpandKey();
	BuildState(ptxt);

	AddRoundKey(0);

	for (int r = 1; r < nr; ++r)
	{
	SubBytes();
	ShiftRows();
	MixColumns();
	AddRoundKey(r);
	}

	SubBytes();
	ShiftRows();
	AddRoundKey(nr);

	ExtractState(out);
}

void Aes::DecryptBlock(unsigned char * ctxt, unsigned char * out)
{
	ExpandKey();
	BuildState(ctxt);

	AddRoundKey(nr);
	InvShiftRows();
	InvSubBytes();

	for (int r = nr - 1; r > 0; --r)
	{
		AddRoundKey(r);
		InvMixColumns();
		InvShiftRows();
		InvSubBytes();
	}

	AddRoundKey(0);

	ExtractState(out);
}

bool Aes::EncryptFileCbc2(string fin, string fout, string key)
{
	LoadKey(key, this->key_size, this->key);
	return EncryptFileCbc(fin, fout, this->key);
}

bool Aes::DecryptFileCbc2(string fin, string fout, string key)
{
	LoadKey(key, this->key_size, this->key);
	return DecryptFileCbc(fin, fout);
}


bool Aes::EncryptFileCbc(string fin, string fout, unsigned char *iv)
{
	ifstream ifsin(fin, ios::in | ios::binary | ios::ate);
	ofstream ifsout(fout, ios::out | ios::binary);
	ifstream::pos_type size;
	unsigned char *buffer;
	unsigned char *tmp;
	unsigned char *tmp2;
	if (ifsin.is_open() && ifsout.is_open())
	{
		size = ifsin.tellg();
		buffer = new unsigned char[64];
		tmp = new unsigned char[16];
		tmp2 = new unsigned char[16];
		for (int i = 0; i < 16; ++i)
		{
			tmp[i] = iv[i];
		}
		ifsout.write((const char*)tmp, 16);

		ifsin.seekg(0, ios::beg);
		int rcnt = 0;
		while (rcnt + static_cast<ifstream::pos_type>(64) <= size)
		{
			ifsin.read((char*)buffer, 64);
			rcnt += 64;

			for (int i = 0; i < 16; ++i)
			{
				tmp2[i] = buffer[i];
			}
			XorArray(tmp2, tmp, 16);
			EncryptBlock(tmp2, tmp2);
			ifsout.write((const char*)tmp2, 16);
			CopyArray(tmp2, tmp, 16);

			for (int i = 0; i < 16; ++i)
			{
				tmp2[i] = buffer[i+16];
			}
			XorArray(tmp2, tmp, 16);
			EncryptBlock(tmp2, tmp2);
			ifsout.write((const char*)tmp2, 16);
			CopyArray(tmp2, tmp, 16);

			for (int i = 0; i < 16; ++i)
			{
				tmp2[i] = buffer[i + 32];
			}
			XorArray(tmp2, tmp, 16);
			EncryptBlock(tmp2, tmp2);
			ifsout.write((const char*)tmp2, 16);
			CopyArray(tmp2, tmp, 16);

			for (int i = 0; i < 16; ++i)
			{
				tmp2[i] = buffer[i + 48];
			}
			XorArray(tmp2, tmp, 16);
			EncryptBlock(tmp2, tmp2);
			ifsout.write((const char*)tmp2, 16);
			CopyArray(tmp2, tmp, 16);
		}



		unsigned char left = size - ifsin.tellg();
		for (int i = 0; i < (left / 16); ++i)
		{
			ifsin.read((char*)tmp2, 16);
			XorArray(tmp2, tmp, 16);
			EncryptBlock(tmp2, tmp2);
			ifsout.write((const char*)tmp2, 16);
			CopyArray(tmp2, tmp, 16);
		}

		left = size - ifsin.tellg();
		
		if (left != 0)
		{
			ifsin.read((char*)buffer, left);
			for (int i = left; i < 16; i++)
			{
				buffer[i] = 16 - left;
			}
		}
		else
		{
			for (int i = 0; i < 16; i++)
			{
				buffer[i] = 0x10;
			}
		}

		XorArray(buffer, tmp, 16);
		EncryptBlock(buffer, buffer);
		ifsout.write((const char*)buffer, 16);

		ifsin.close();
		ifsout.close();

		delete[] buffer;
		delete[] tmp;
		delete[] tmp2;
		return true;
	}
	else
	{
		return false;
	}
}

bool Aes::DecryptFileCbc(string fin, string fout)
{
	ifstream ifsin(fin, ios::in | ios::binary | ios::ate);
	ofstream ifsout(fout, ios::out | ios::binary);
	ifstream::pos_type size;
	unsigned char *buffer;
	unsigned char *tmp1;
	unsigned char *tmp2;
	if (ifsin.is_open() && ifsout.is_open())
	{
		size = ifsin.tellg();
		buffer = new unsigned char[16];
		tmp1 = new unsigned char[16];
		tmp2 = new unsigned char[16];

		ifsin.seekg(0, ios::beg);
		ifsin.read((char*)tmp2, 16);


		while (ifsin.tellg() + static_cast<ifstream::pos_type>(16) < size)
		{
			ifsin.read((char*)buffer, 16);
			DecryptBlock(buffer, tmp1);
			XorArray(tmp1, tmp2, 16);
			ifsout.write((const char*)tmp1, 16);
			CopyArray(buffer, tmp2, 16);
		}

		unsigned char left = size - ifsin.tellg();
		if (left != 16)
		{
			return false;
		}

		ifsin.read((char*)buffer, 16);
		DecryptBlock(buffer, tmp1);
		XorArray(tmp1, tmp2, 16);
		int padd = tmp1[15];
		if (padd != 16)
		{
			ifsout.write((const char*)tmp1, 16 - padd);
		}
		ifsin.close();
		ifsout.close();

		delete[] buffer;
		delete[] tmp1;
		delete[] tmp2;
		return true;
	}
	else
	{
		return false;
	}
}

void Aes::GenerateKey(unsigned int size, unsigned char *out)
{
	BCryptGenRandom(0, out, size, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
}

bool Aes::CreateKey(string out, int size)
{
	if (size == 128 || size == 192 || size == 256)
	{
		unsigned char key[32];
		Aes::GenerateKey(size / 8, key);
		ofstream ifsout(out, ios::out | ios::binary);
		if (ifsout.is_open())
		{
			ifsout << "AES Key:\n";
			ifsout << base64_encode(key, size / 8);
		}
		ifsout.close();
	}
	return false;
}

void Aes::LoadKey(string in, int size, unsigned char *out)
{
	if (size == 128 || size == 192 || size == 256)
	{
		ifstream ifsin(in, ios::in);
		if (ifsin.is_open())
		{
			string key;
			getline(ifsin, key);
			getline(ifsin, key);
			key = base64_decode(key);
			if (key.size() >= size / 8)
			{
				for (int i = 0; i < size / 8; ++i)
				{
					out[i] = (unsigned char)key[i];
				}
			}
		}
		ifsin.close();
	}
}

void Aes::GenerateIv(unsigned char * out)
{
	BCryptGenRandom(0, out, 16, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
}

void Aes::ExpandKey()
{

	for (int j = 0; j < key_size; ++j)
	{
		key_schedule[j] = key[j];
	}
	int i = 1;
	int cnt = key_size;

	unsigned char t[4];
	while (cnt < key_schedule_size)
	{
		FillT(t, cnt);
		ScheduleCore(t, i);
		++i;

		SetNext4(t, &cnt);

		//FillTAndSetNext4(3, t, &cnt);
		FillT(t, cnt);
		SetNext4(t, &cnt);
		FillT(t, cnt);
		SetNext4(t, &cnt);
		FillT(t, cnt);
		SetNext4(t, &cnt);
		//

		if (key_size == 32 && cnt < key_schedule_size)
		{
			FillT(t, cnt);
			SubWord(t);
			SetNext4(t, &cnt);
		}

		if (key_size == 24 && cnt < key_schedule_size)
		{
			//FillTAndSetNext4(2, t, &cnt);
			FillT(t, cnt);
			SetNext4(t, &cnt);
			FillT(t, cnt);
			SetNext4(t, &cnt);
			///
		}
		else if (key_size == 32 && cnt < key_schedule_size)
		{
			//FillTAndSetNext4(3, t, &cnt);
			FillT(t, cnt);
			SetNext4(t, &cnt);
			FillT(t, cnt);
			SetNext4(t, &cnt);
			FillT(t, cnt);
			SetNext4(t, &cnt);
			///
		}
	}
}

void Aes::RotWord(unsigned char *in)
{
	unsigned char first = in[0];
	for (unsigned char i = 0; i < 3; ++i)
	{
		in[i] = in[i + 1];
	}
	in[3] = first;
}

void Aes::ScheduleCore(unsigned char *in, unsigned char i)
{
	RotWord(in);
	SubWord(in);
	in[0] ^= AesStatics::rcon[i];
}

void Aes::SubWord(unsigned char *in)
{
	for (unsigned char j = 0; j < 4; ++j)
	{
		in[j] = AesStatics::sbox[in[j]];
	}
}

void Aes::FillT(unsigned char* t, int cnt)
{
	for (int j = 0; j < 4; ++j)
	{
		t[j] = key_schedule[j + cnt - 4];
	}
}

void Aes::SetNext4(unsigned char* t, int *cnt)
{
	for (int j = 0; j < 4; ++j)
	{
		key_schedule[*cnt + j] = t[j] ^ key_schedule[j + *cnt - key_size];
	}
	(*cnt) += 4;
}

void Aes::FillTAndSetNext4(int loop, unsigned char* t, int *cnt)
{
	for (int j = 0; j < loop; j++)
	{
		FillT(t, *cnt);
		SetNext4(t, cnt);
	}
}

void Aes::BuildState(unsigned char * block)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			state[j][i] = block[i * 4 + j];
		}
	}
}

void Aes::ExtractState(unsigned char * out)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			out[4 * i + j] = state[j][i];
		}
	}
}

void Aes::AddRoundKey(int round)
{
	/*
	for (int i = 0; i < 4; ++i)
	{
	for (int j = 0; j < 4; ++j)
	{
	state[j][i] ^= key_schedule[i * 4 + j + round * block_size];
	}
	}
	*/

	//unroll
	int add = round * block_size;

	state[0][0] ^= key_schedule[0 + add];
	state[1][0] ^= key_schedule[1 + add];
	state[2][0] ^= key_schedule[2 + add];
	state[3][0] ^= key_schedule[3 + add];

	state[0][1] ^= key_schedule[4 + add];
	state[1][1] ^= key_schedule[5 + add];
	state[2][1] ^= key_schedule[6 + add];
	state[3][1] ^= key_schedule[7 + add];

	state[0][2] ^= key_schedule[8 + add];
	state[1][2] ^= key_schedule[9 + add];
	state[2][2] ^= key_schedule[10 + add];
	state[3][2] ^= key_schedule[11 + add];

	state[0][3] ^= key_schedule[12 + add];
	state[1][3] ^= key_schedule[13 + add];
	state[2][3] ^= key_schedule[14 + add];
	state[3][3] ^= key_schedule[15 + add];
	//
}

void Aes::SubBytes()
{
	SubBytesGeneric(AesStatics::sbox);
}

void Aes::InvSubBytes()
{
	SubBytesGeneric(AesStatics::sbox_inv);
}

void Aes::SubBytesGeneric(const unsigned char *sbox)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			state[j][i] = sbox[state[j][i]];
		}
	}
}

void Aes::ShiftRows()
{
	unsigned char temp = 0x00;

	// row 0 unchanged
	// row 1
	temp = state[1][0];
	state[1][0] = state[1][1];
	state[1][1] = state[1][2];
	state[1][2] = state[1][3];
	state[1][3] = temp;

	// row 2
	temp = state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = temp;

	temp = state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = temp;

	// row 3
	temp = state[3][3];
	state[3][3] = state[3][2];
	state[3][2] = state[3][1];
	state[3][1] = state[3][0];
	state[3][0] = temp;
}

void Aes::InvShiftRows()
{
	unsigned char temp = 0x00;

	// row 0 unchanged
	// row 1
	temp = state[1][3];
	state[1][3] = state[1][2];
	state[1][2] = state[1][1];
	state[1][1] = state[1][0];
	state[1][0] = temp;

	// row 2
	temp = state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = temp;

	temp = state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = temp;

	// row 3
	temp = state[3][0];
	state[3][0] = state[3][1];
	state[3][1] = state[3][2];
	state[3][2] = state[3][3];
	state[3][3] = temp;
}

void Aes::MixColumns()
{
	MixColumnsGeneric(AesStatics::mix_mat);
}

void Aes::InvMixColumns()
{
	MixColumnsGeneric(AesStatics::mix_mat_inv);
}

void Aes::MixColumnsGenericOld(const int * mat)
{
	unsigned char sum;
	unsigned char state_clm[4] = { 0x00 };

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			sum = 0x00;
			for (int k = 0; k < 4; ++k)
			{
				sum ^= Gmul(4 * j + k, &state[k][i], mat);
			}
			state_clm[j] = sum;
		}

		for (int j = 0; j < 4; ++j)
		{
			state[j][i] = state_clm[j];
		}
	}
}

void Aes::MixColumnsGeneric(const int * mat)
{
	unsigned char sum;
	unsigned char state_clm[4] = { 0x00 };

	for (int i = 0; i < 4; ++i)
	{
		// i == 0
		sum = 0x00;
		sum ^= Gmul(4 * 0 + 0, &state[0][i], mat);
		sum ^= Gmul(4 * 0 + 1, &state[1][i], mat);
		sum ^= Gmul(4 * 0 + 2, &state[2][i], mat);
		sum ^= Gmul(4 * 0 + 3, &state[3][i], mat);
		state_clm[0] = sum;

		sum = 0x00;
		sum ^= Gmul(4 * 1 + 0, &state[0][i], mat);
		sum ^= Gmul(4 * 1 + 1, &state[1][i], mat);
		sum ^= Gmul(4 * 1 + 2, &state[2][i], mat);
		sum ^= Gmul(4 * 1 + 3, &state[3][i], mat);
		state_clm[1] = sum;

		sum = 0x00;
		sum ^= Gmul(4 * 2 + 0, &state[0][i], mat);
		sum ^= Gmul(4 * 2 + 1, &state[1][i], mat);
		sum ^= Gmul(4 * 2 + 2, &state[2][i], mat);
		sum ^= Gmul(4 * 2 + 3, &state[3][i], mat);
		state_clm[2] = sum;

		sum = 0x00;
		sum ^= Gmul(4 * 3 + 0, &state[0][i], mat);
		sum ^= Gmul(4 * 3 + 1, &state[1][i], mat);
		sum ^= Gmul(4 * 3 + 2, &state[2][i], mat);
		sum ^= Gmul(4 * 3 + 3, &state[3][i], mat);
		state_clm[3] = sum;

		state[0][i] = state_clm[0];
		state[1][i] = state_clm[1];
		state[2][i] = state_clm[2];
		state[3][i] = state_clm[3];
	}

}

unsigned char Aes::Gmul(int index, unsigned char *multiplicant, const int * mat)
{
	if (mat[index] == 1)
	{
		return *multiplicant;
	}
	else if (mat[index] == 2)
	{
		return AesStatics::gmul2[*multiplicant];
	}
	else if (mat[index] == 3)
	{
		return AesStatics::gmul3[*multiplicant];
	}
	else if (mat[index] == 9)
	{
		return AesStatics::gmul9[*multiplicant];
	}
	else if (mat[index] == 11)
	{
		return AesStatics::gmul11[*multiplicant];
	}
	else if (mat[index] == 13)
	{
		return AesStatics::gmul13[*multiplicant];
	}
	else if (mat[index] == 14)
	{
		return AesStatics::gmul14[*multiplicant];
	}
	return 0x00;
}

Aes128::Aes128(unsigned char key[16]) : Aes(key, 16) {}
Aes128::Aes128() : Aes(16) {}
Aes192::Aes192(unsigned char key[24]) : Aes(key, 24) {}
Aes256::Aes256(unsigned char key[32]) : Aes(key, 32) {}