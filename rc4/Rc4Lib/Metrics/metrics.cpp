#include <iostream>
#include <fstream>
#include <chrono>

#include <Windows.h>
#include <bcrypt.h>

#include "arc4.h"
#include "files.h"

#include "rc4.h"
#include "print_utils.h"


using namespace std;

void SanityCheck()
{
	unsigned char key[] = { "Key" };
	Rc4::encrypt_file("D:/test.txt", "D:/test.enc", key, 3);
	Rc4::encrypt_file("D:/test.enc", "D:/dec.txt", key, 3);
}

void Profiling()
{
	unsigned char key[] = { "0123456789012345" };
	Rc4::encrypt_file("D:/1mb", "D:/1mb.enc", key, 16);
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

void MeasureLib()
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed;

	unsigned char key[] = { "0123456789012345" };

	cout << "Rc4Lib" << endl;
	cout << "ENCRYPTION" << endl;

	start = chrono::system_clock::now();
	Rc4::encrypt_file("D:/1kb", "D:/1kb.enc", key, 16);
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "1KB: " << elapsed.count() << " " << (1 / elapsed.count()) / 1024 << " MB/s" << endl;

	start = chrono::system_clock::now();
	Rc4::encrypt_file("D:/1mb", "D:/1mb.enc", key, 16);
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "1MB: " << elapsed.count() << " " << 1 / elapsed.count() << " MB/s" << endl;

	start = chrono::system_clock::now();
	Rc4::encrypt_file("D:/10mb", "D:/10mb.enc", key, 16);
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "10MB: " << elapsed.count() << " " << (1 / elapsed.count()) * 10 << " MB/s" << endl;
}

void MeasureReference()
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed;

	unsigned char key[] = { "0123456789012345" };

	CryptoPP::ARC4::Encryption enc(key, 16);

	start = chrono::system_clock::now();
	CryptoPP::FileSource f1("D:/1kb", true, new CryptoPP::StreamTransformationFilter(enc, new CryptoPP::FileSink("D:/1kb_enc", true)));
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "1KB: " << elapsed.count() << " " << (1 / elapsed.count()) / 1024 << " MB/s" << endl;

	start = chrono::system_clock::now();
	CryptoPP::FileSource f2("D:/1mb", true, new CryptoPP::StreamTransformationFilter(enc, new CryptoPP::FileSink("D:/1mb_enc", true)));
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "1MB: " << elapsed.count() << " " << 1 / elapsed.count() << " MB/s" << endl;

	start = chrono::system_clock::now();
	CryptoPP::FileSource f3("D:/10mb", true, new CryptoPP::StreamTransformationFilter(enc, new CryptoPP::FileSink("D:/10mb_enc", true)));
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "10MB: " << elapsed.count() << " " << (1 / elapsed.count()) * 10 << " MB/s" << endl;
}

int main()
{
	//SanityCheck();
	MeasureLib();
	//MeasureReference();
	//Profiling();

	cout << "DONE" << endl;
	cin.get();
}