#include <iostream>
#include <string>
#include <Windows.h>
#include <bcrypt.h>
#include <chrono>
#include <fstream>

#include "sha256.h"
#include "print_utils.h"

#include "sha.h"
#include "base64.h"
#include "files.h"

using namespace std;

/*
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
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed;

	start = chrono::system_clock::now();
	Sha256::hash("D:/1kb");
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "1KB: " << elapsed.count() << " " << (1 / elapsed.count()) / 1024 << " MB/s" << endl;

	start = chrono::system_clock::now();
	Sha256::hash("D:/1mb");
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "1MB: " << elapsed.count() << " " << 1 / elapsed.count() << " MB/s" << endl;

	start = chrono::system_clock::now();
	Sha256::hash("D:/10mb");
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "10MB: " << elapsed.count() << " " << (1 / elapsed.count()) * 10 << " MB/s" << endl;

	CryptoPP::SHA256 hash;
	string digest;
	
	start = chrono::system_clock::now();
	CryptoPP::FileSource("D:/1kb", true, new CryptoPP::HashFilter(hash, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(digest))));
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "1KB: " << elapsed.count() << " " << (1 / elapsed.count()) / 1024 << " MB/s" << endl;

	start = chrono::system_clock::now();
	CryptoPP::FileSource("D:/1mb", true, new CryptoPP::HashFilter(hash, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(digest))));
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "1MB: " << elapsed.count() << " " << 1 / elapsed.count() << " MB/s" << endl;

	start = chrono::system_clock::now();
	CryptoPP::FileSource("D:/10mb", true, new CryptoPP::HashFilter(hash, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(digest))));
	end = chrono::system_clock::now();
	elapsed = end - start;
	cout << "10MB: " << elapsed.count() << " " << (1 / elapsed.count()) * 10 << " MB/s" << endl;
		
	cin.get();
}
*/