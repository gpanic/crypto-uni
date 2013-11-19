#include <iostream>
#include <iomanip>

#include <Windows.h>
#include <bcrypt.h>

#include "print_utils.h"

void GenerateKey(unsigned char in[], unsigned int size)
{
	BCryptGenRandom(0, in, size, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
}


int main()
{
	unsigned char buffer[16];
	PrintHex(buffer, 16);
	GenerateKey(buffer, 16);
	PrintHex(buffer, 16);
	std::cin.get();
	return 0;
}

