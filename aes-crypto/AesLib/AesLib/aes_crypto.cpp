#include <iostream>
#include <iomanip>

#include <Windows.h>
#include <bcrypt.h>

#include "print_utils.h"
#include "aes_statics.h"

using namespace std;

void GenerateKey(unsigned char *in, unsigned int size)
{
	BCryptGenRandom(0, in, size, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
}

void Rotate(unsigned char *arr, unsigned int size)
{
	unsigned char first = arr[0];
	for (unsigned char i = 0; i < size - 1; ++i)
	{
		arr[i] = arr[i + 1];
	}
	arr[size - 1] = first;
}

void ScheduleCore(unsigned char *in)
{
	PrintHex(in, 4);
	Rotate(in, 4);
	PrintHex(in, 4);
	for (unsigned char i = 0; i < 4; ++i)
	{
		in[i] = AesStatics::sbox[in[i]];
	}
	PrintHex(in, 4);
}

int main()
{
	unsigned char buffer[4] = { 0x01, 0x02, 0x03, 0x04 };
	ScheduleCore(buffer);
	
	std::cin.get();
	return 0;
}

