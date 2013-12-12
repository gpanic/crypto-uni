#include <iostream>
#include <fstream>
#include <tuple>

#include <Windows.h>
#include <bcrypt.h>

#include "base64.h"
#include "rc4.h"

using namespace std;

void Rc4::ksa(unsigned char s[], unsigned char key[], int key_len)
{
	for (int i = 0; i < 256; ++i)
	{
		s[i] = static_cast<unsigned char>(i);
	}
	int j = 0;
	unsigned char temp;
	for (int i = 0; i < 256; ++i)
	{
		j = (j + s[i] + key[i % key_len]) % 256;
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}
}

void Rc4::prga(unsigned char s[], unsigned char out[], int out_cnt)
{
	int i = 0;
	int j = 0;
	unsigned char temp;

	for (int k = 0; k < out_cnt; ++k)
	{

		i = (i + 1) % 256;
		j = (j + s[i]) % 256;

		temp = s[i];
		s[i] = s[j];
		s[j] = temp;

		out[k] = s[(s[i] + s[j]) % 256];
	}

}
void Rc4::iprga(unsigned char s[], unsigned char out[], int out_cnt, int &i, int &j)
{
	unsigned char temp;
	for (int k = 0; k < out_cnt; ++k)
	{

		i = (i + 1) % 256;
		j = (j + s[i]) % 256;

		temp = s[i];
		s[i] = s[j];
		s[j] = temp;

		out[k] = s[(s[i] + s[j]) % 256];
	}
}

void Rc4::xor_array(unsigned char a1[], unsigned char a2[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		a1[i] ^= a2[i];
	}
}

void Rc4::encrypt_file(string in, string out, unsigned char key[], int key_len)
{
	unsigned char s[256];
	unsigned char buffer[buffer_size];
	unsigned char buffer2[buffer_size / 2];
	unsigned char key_buffer[buffer_size];
	int prga_i = 0;
	int prga_j = 0;
	int rcnt = 0;

	ksa(s, key, key_len);

	ifstream ifsin(in, ios::in | ios::binary | ios::ate);
	ofstream ifsout(out, ios::out | ios::binary);
	ifstream::pos_type size;
	if (ifsin.is_open() && ifsout.is_open())
	{
		size = ifsin.tellg();
		ifsin.seekg(0, ios::beg);
		while (rcnt + buffer_size <= size)
		{
			ifsin.read((char*)buffer, buffer_size);
			rcnt += buffer_size;
			iprga(s, key_buffer, buffer_size, prga_i, prga_j);
			xor_array(buffer, key_buffer, buffer_size);
			ifsout.write((char*)buffer, buffer_size);
		}

		int left = size - ifsin.tellg();
		for (int i = 0; i < left / (buffer_size / 4); ++i)
		{
			ifsin.read((char*)buffer2, buffer_size / 4);
			iprga(s, key_buffer, buffer_size / 4, prga_i, prga_j);
			xor_array(buffer2, key_buffer, buffer_size / 4);
			ifsout.write((char*)buffer2, buffer_size / 4);
		}

		left = size - ifsin.tellg();
		for (int i = 0; i < left; ++i)
		{
			ifsin.read((char*)buffer2, 1);
			iprga(s, key_buffer, 1, prga_i, prga_j);
			xor_array(buffer2, key_buffer, 1);
			ifsout.write((char*)buffer2, 1);
		}
		ifsin.close();
		ifsout.close();
	}
}

void Rc4::encrypt_file2(string in, string out, string key_path)
{
	unsigned char key[16];
	load_key(key_path, key);
	encrypt_file(in, out, key, 16);
}

void Rc4::generate_key(unsigned int size, unsigned char *out)
{
	BCryptGenRandom(0, out, size, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
}

void Rc4::create_key(string out)
{
	unsigned char key[16];
	generate_key(16, key);
	ofstream ifsout(out, ios::out | ios::binary);
	if (ifsout.is_open())
	{
		ifsout << "Rc4 Key:\n";
		ifsout << base64_encode(key, 16);
	}
	ifsout.close();
}

void Rc4::load_key(string in, unsigned char *out)
{
	ifstream ifsin(in, ios::in);
	if (ifsin.is_open())
	{
		string key;
		getline(ifsin, key);
		getline(ifsin, key);
		key = base64_decode(key);
		for (int i = 0; i < 16; ++i)
		{
			out[i] = (unsigned char)key[i];
		}
	}
	ifsin.close();
}