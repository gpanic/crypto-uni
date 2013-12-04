#include <iostream>
#include <chrono>

#include <Windows.h>
#include <bcrypt.h>

#include "aes2.h"

#include "aes.h"
#include "modes.h"
#include "files.h"

using namespace std;

void MeasureAesLib()
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed;

	unsigned char key[16];
	Aes::GenerateKey(16, key);
	unsigned char iv[16];
	Aes::GenerateIv(iv);
	Aes128 aes(key);

	cout << endl;
	cout << "AesLib" << endl;
	cout << "ENCRYPTION" << endl;

	start = chrono::system_clock::now();
	aes.EncryptFileCbc("D:/1kb", "D:/1kb_enc", iv);
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "1KB: " << elapsed.count() << " " << (1 / elapsed.count()) / 1024 << " MB/s" << endl;

	start = chrono::system_clock::now();
	aes.EncryptFileCbc("D:/1mb", "D:/1mb_enc", iv);
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "1MB: " << elapsed.count() << " " << 1 / elapsed.count() << " MB/s" << endl;

	start = chrono::system_clock::now();
	aes.EncryptFileCbc("D:/10mb", "D:/10mb_enc", iv);
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "10MB: " << elapsed.count() << " " << (1 / elapsed.count()) * 10 << " MB/s" << endl;
}

void Profiling()
{
	unsigned char buffer[16] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
	Aes128 aes = Aes128(buffer);
	aes.EncryptFileCbc("D:/1mb", "D:/1mb_enc", buffer);
}

void MeasureReference()
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed;

	byte key2[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
	CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption cbfEnc(key2, CryptoPP::AES::DEFAULT_KEYLENGTH, iv);
	CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption cbfDec(key2, CryptoPP::AES::DEFAULT_KEYLENGTH, iv);

	cout << "Crypto++" << endl;
	cout << "ENCRYPTION" << endl;

	start = chrono::system_clock::now();
	CryptoPP::FileSource f1("D:/1kb", true, new CryptoPP::StreamTransformationFilter(cbfEnc, new CryptoPP::FileSink("D:/1kb_enc", true)));
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "1KB: " << elapsed.count() << " " << (1 / elapsed.count()) / 1024 << " MB/s" << endl;

	start = chrono::system_clock::now();
	CryptoPP::FileSource f2("D:/1mb", true, new CryptoPP::StreamTransformationFilter(cbfEnc, new CryptoPP::FileSink("D:/1mb_enc", true)));
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "1MB: " << elapsed.count() << " " << 1 / elapsed.count() << " MB/s" << endl;

	start = chrono::system_clock::now();
	CryptoPP::FileSource f3("D:/10mb", true, new CryptoPP::StreamTransformationFilter(cbfEnc, new CryptoPP::FileSink("D:/10mb_enc", true)));
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "10MB: " << elapsed.count() << " " << (1 / elapsed.count()) * 10 << " MB/s" << endl;
}

void Create1KB(string out)
{
	unsigned char bytes[1024];
	BCryptGenRandom(0, bytes, 1024, BCRYPT_USE_SYSTEM_PREFERRED_RNG);

	ofstream ifsout(out, ios::out | ios::binary);
	if (ifsout.is_open())
	{
		ifsout.write((const char*)bytes, 1024);
	}
}

void Create1MB(string out)
{
	unsigned char bytes[1024];
	BCryptGenRandom(0, bytes, 1024, BCRYPT_USE_SYSTEM_PREFERRED_RNG);

	ofstream ifsout(out, ios::out | ios::binary);
	if (ifsout.is_open())
	{
		for (int i = 0; i < 1024; ++i)
		{
			ifsout.write((const char*)bytes, 1024);
		}
	}
}

void Create10MB(string out)
{
	unsigned char bytes[1024];
	BCryptGenRandom(0, bytes, 1024, BCRYPT_USE_SYSTEM_PREFERRED_RNG);

	ofstream ifsout(out, ios::out | ios::binary);
	if (ifsout.is_open())
	{
		for (int i = 0; i < 10 * 1024; ++i)
		{
			ifsout.write((const char*)bytes, 1024);
		}
	}
}


void CreateFiles()
{
	Create1KB("D:/1kb");
	Create1MB("D:/1mb");
	Create10MB("D:/10mb");
}

int main()
{
	//CreateFiles();
	MeasureAesLib();
	//MeasureReference();
	//Profiling();
	cin.get();
}