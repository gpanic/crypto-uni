#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>

#include "print_utils.h"
#include "aes_statics.h"

#include "aes2.h"

#include "base64.h"

using namespace std;

void SanityCheck()
{
	unsigned char buffer[16] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
	unsigned char plain[16] = { 0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34 };
	Aes128 aes = Aes128(buffer);

	PrintHex(plain, 16);
	aes.EncryptBlock(plain, plain);
	PrintHex(plain, 16);
	aes.DecryptBlock(plain, plain);
	PrintHex(plain, 16);
}

void Measure()
{
	unsigned char key[16];
	Aes::GenerateKey(16, key);
	Aes128 aes(key);

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed;

	cout << endl;
	cout << "AesLib" << endl;
	cout << "ENCRYPTION" << endl;

	start = chrono::system_clock::now();
	aes.EncryptFileCbc("D:/1kb", "D:/1kb_enc");
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "1KB: " << elapsed.count() << " " << (1 / elapsed.count()) / 1024 << " MB/s" << endl;

	start = chrono::system_clock::now();
	aes.EncryptFileCbc("D:/1mb", "D:/1mb_enc");
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "1MB: " << elapsed.count() << " " << 1 / elapsed.count() << " MB/s" << endl;

	start = chrono::system_clock::now();
	aes.EncryptFileCbc("D:/10mb", "D:/10mb_enc");
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "10MB: " << elapsed.count() << " " << (1 / elapsed.count()) * 10 << " MB/s" << endl;

	cin.get();
}

int main()
{
	SanityCheck();
	Measure();
}