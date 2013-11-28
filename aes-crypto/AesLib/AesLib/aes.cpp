#include <algorithm>
#include <iostream>

#include <Windows.h>
#include <bcrypt.h>

#include "aes.h"
#include "aes_statics.h"
#include "print_utils.h"

using namespace std;

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

void Aes::GenerateKey(unsigned int size, unsigned char * out)
{
	BCryptGenRandom(0, out, size, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
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
		FillTAndSetNext4(3, t, &cnt);

		if (key_size == 32 && cnt < key_schedule_size)
		{
			FillT(t, cnt);
			SubWord(t);
			SetNext4(t, &cnt);
		}

		if (key_size == 24 && cnt < key_schedule_size)
		{
			FillTAndSetNext4(2, t, &cnt);
		}
		else if (key_size == 32 && cnt < key_schedule_size)
		{
			FillTAndSetNext4(3, t, &cnt);
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
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			state[j][i] ^= key_schedule[i * 4 + j + round * block_size];
		}
	}
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

void Aes::MixColumnsGeneric(const int * mat)
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

unsigned char Aes::Gmul(int index, unsigned char *multiplicant, const int * mat)
{
	switch (mat[index])
	{
	case 1:
		return *multiplicant;
		break;
	case 2:
		return AesStatics::gmul2[*multiplicant];
		break;
	case 3:
		return AesStatics::gmul3[*multiplicant];
		break;
	case 9:
		return AesStatics::gmul9[*multiplicant];
		break;
	case 11:
		return AesStatics::gmul11[*multiplicant];
		break;
	case 13:
		return AesStatics::gmul13[*multiplicant];
		break;
	case 14:
		return AesStatics::gmul14[*multiplicant];
		break;
	default:
		return 0x00;
		break;
	}
}

Aes128::Aes128(unsigned char key[16]) : Aes(key, 16) {}
Aes192::Aes192(unsigned char key[24]) : Aes(key, 24) {}
Aes256::Aes256(unsigned char key[32]) : Aes(key, 32) {}