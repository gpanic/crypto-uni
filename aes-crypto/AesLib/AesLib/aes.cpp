#include <algorithm>
#include <iostream>

#include "aes_statics.h"
#include "print_utils.h"

#include "aes.h"

using namespace std;

void Aes::Rotate(unsigned char *arr, unsigned int size)
{
	unsigned char first = arr[0];
	for (unsigned char i = 0; i < size - 1; ++i)
	{
		arr[i] = arr[i + 1];
	}
	arr[size - 1] = first;
}

void Aes::ScheduleCore(unsigned char *in, unsigned char i)
{
	Rotate(in, 4);
	for (unsigned char j = 0; j < 4; ++j)
	{
		in[j] = AesStatics::sbox[in[j]];
	}
	in[0] ^= AesStatics::rcon[i];
}

void Aes::FillT(unsigned char* t, unsigned char *key_schedule, int cnt)
{
	for (int j = 0; j < 4; ++j)
	{
		t[j] = key_schedule[j + cnt - 4];
	}
}

void Aes::SetNext4(unsigned char* t, unsigned char *key_schedule, int *cnt, int key_size)
{
	for (int j = 0; j < 4; ++j)
	{
		key_schedule[*cnt + j] = t[j] ^ key_schedule[j + *cnt - key_size];
	}
	(*cnt) += 4;
}

void Aes::FillTAndSetNext4(int loop, unsigned char* t, unsigned char *key_schedule, int *cnt, int key_size)
{
	for (int j = 0; j < loop; j++)
	{
		FillT(t, key_schedule, *cnt);
		SetNext4(t, key_schedule, cnt, key_size);
	}
}

void Aes::ExpandKeyGeneric(unsigned char *key, unsigned char *key_schedule, const int key_size, const int key_schedule_size)
{

	for (int j = 0; j < 16; ++j)
	{
		key_schedule[j] = key[j];
	}
	int i = 1;
	int cnt = key_size;

	unsigned char t[4];
	while (cnt < key_schedule_size)
	{
		FillT(t, key_schedule, cnt);
		ScheduleCore(t, i);
		++i;
		
		SetNext4(t, key_schedule, &cnt, key_size);
		FillTAndSetNext4(3, t, key_schedule, &cnt, key_size);

		if (key_size == 32 && cnt < key_schedule_size)
		{
			FillT(t, key_schedule, cnt);
			for (int j = 0; j < 4; ++j)
			{
				t[j] = AesStatics::sbox[t[j]];
			}
			SetNext4(t, key_schedule, &cnt, key_size);
		}

		if (key_size == 24 && cnt < key_schedule_size)
		{
			FillTAndSetNext4(2, t, key_schedule, &cnt, key_size);
		}
		else if (key_size == 32 && cnt < key_schedule_size)
		{
			FillTAndSetNext4(3, t, key_schedule, &cnt, key_size);
		}
	}
	PrintHexCol(key_schedule, 240, 16);
}

void Aes::Encrypt()
{
	ExpandKey();
}

Aes128::Aes128(unsigned char key[16])
{
	for (int i = 0; i < 16; ++i)
	{
		this->key[i] = key[i];
	}
	this->key_size = 16;
	this->key_schedule_size = 176;
	fill(begin(this->key_schedule), end(this->key_schedule), 0x00);
}

void Aes128::ExpandKey()
{
	ExpandKeyGeneric(key, key_schedule, key_size, key_schedule_size);
}


Aes192::Aes192(unsigned char key[24])
{
	for (int i = 0; i < 24; ++i)
	{
		this->key[i] = key[i];
	}
	this->key_size = 24;
	this->key_schedule_size = 208;
	fill(begin(this->key_schedule), end(this->key_schedule), 0x00);
}

void Aes192::ExpandKey()
{
	ExpandKeyGeneric(key, key_schedule, key_size, key_schedule_size);
}

Aes256::Aes256(unsigned char key[32])
{
	for (int i = 0; i < 32; ++i)
	{
		this->key[i] = key[i];
	}
	this->key_size = 32;
	this->key_schedule_size = 240;
	fill(begin(this->key_schedule), end(this->key_schedule), 0x00);
}

void Aes256::ExpandKey()
{
	ExpandKeyGeneric(key, key_schedule, key_size, key_schedule_size);
}