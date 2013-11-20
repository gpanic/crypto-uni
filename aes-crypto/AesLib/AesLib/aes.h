#pragma once

class Aes
{
public:
	void Encrypt();
protected:
	unsigned char key[32];
	int key_size;
	unsigned char key_schedule[240];
	int key_schedule_size;
	unsigned char state[4][4];
	const int nb;
	int nr;
	int nk;

	Aes(unsigned char *key, int key_size);
	void ExpandKey();
	void RotWord(unsigned char *in);
	void ScheduleCore(unsigned char *in, unsigned char i);
	void SubWord(unsigned char *in);
	void FillT(unsigned char* t, int cnt);
	void SetNext4(unsigned char* t, int *cnt);
	void FillTAndSetNext4(int loop, unsigned char* t, int *cnt);
};

class Aes128 : public Aes
{
public:
	Aes128(unsigned char *key);
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