#pragma once
#include <string>

using namespace std;

class Aes
{
public:
	void EncryptBlock(unsigned char * ptxt, unsigned char * out);
	void EncryptBlockAesNi(unsigned char * ptxt, unsigned char * out);
	void DecryptBlock(unsigned char * ctxt, unsigned char * out);
	static void GenerateKey(unsigned int size, unsigned char *out);
	static bool CreateKey(string out, int size);
	static void LoadKey(string in, int size, unsigned char *out);
	static void GenerateIv(unsigned char * out);
	bool EncryptFileCbc(string fin, string fout, unsigned char *iv);
	bool EncryptFileCbc2(string fin, string fout, string key);
	bool DecryptFileCbc(string fin, string fout);
	bool DecryptFileCbc2(string fin, string fout, string key);
protected:
	unsigned char key[32];
	int key_size;
	unsigned char key_schedule[240];
	int key_schedule_size;
	unsigned char state[4][4];
	const int nb;
	const int block_size;
	int nr;
	int nk;

	Aes(unsigned char *key, int key_size);
	Aes(int key_size);

	void ExpandKey();
	void RotWord(unsigned char *in);
	void ScheduleCore(unsigned char *in, unsigned char i);
	void SubWord(unsigned char *in);
	void FillT(unsigned char* t, int cnt);
	void SetNext4(unsigned char* t, int *cnt);
	void FillTAndSetNext4(int loop, unsigned char* t, int *cnt);

	void BuildState(unsigned char * block);
	void ExtractState(unsigned char * out);
	void AddRoundKey(int round);
	void SubBytes();
	void InvSubBytes();
	void SubBytesGeneric(const unsigned char *sbox);
	void ShiftRows();
	void InvShiftRows();
	void MixColumns();
	void InvMixColumns();
	void MixColumnsGeneric(const int * mat);
	void MixColumnsGenericOld(const int * mat);
	unsigned char Gmul(int index, unsigned char *multiplicant, const int * mat);
};

class Aes128 : public Aes
{
public:
	Aes128(unsigned char *key);
	Aes128();
};

class Aes192 : public Aes
{
public:
	Aes192(unsigned char *key);
};

class Aes256 : public Aes
{
public:
	Aes256(unsigned char *key);
};