#include <algorithm>
#include <iostream>

#include "aes.h"
#include "aes_statics.h"
#include "print_utils.h"

using namespace std;

Aes::Aes(unsigned char *key, int key_size) : nb(4)
{
	this->key_size = key_size;
	this->nk = key_size / 4;
	this->nr = nk + 6;
	this->key_schedule_size = (nr + 1) * 16;

	fill(begin(this->key), end(this->key), 0x00);
	fill(begin(this->key_schedule), end(this->key_schedule), 0x00);

	for (int i = 0; i < key_size; ++i)
	{
		this->key[i] = key[i];
	}
}

void Aes::Encrypt()
{
	ExpandKey();
	PrintHexCol(key_schedule, key_schedule_size, 16);
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

Aes128::Aes128(unsigned char key[16]) : Aes(key, 16) {}
Aes192::Aes192(unsigned char key[24]) : Aes(key, 24) {}
Aes256::Aes256(unsigned char key[32]) : Aes(key, 32) {}