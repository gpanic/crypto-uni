#pragma once

class Aes
{
public:
	void Encrypt();
protected:
	unsigned char key_size;
	unsigned char key_schedule_size;

	virtual void ExpandKey() = 0;
	void Rotate(unsigned char *arr, unsigned int size);
	void ScheduleCore(unsigned char *in, unsigned char i);
	void ExpandKeyGeneric(unsigned char *key, unsigned char *keys, const int key_size, const int key_schedule_size);
	void FillT(unsigned char* t, unsigned char *key_schedule, int cnt);
	void SetNext4(unsigned char* t, unsigned char *key_schedule, int *cnt, int key_size);
	void FillTAndSetNext4(int loop, unsigned char* t, unsigned char *key_schedule, int *cnt, int key_size);
};

class Aes128 : public Aes
{
public:
	Aes128(unsigned char key[16]);
private:
	unsigned char key[16];
	unsigned char key_schedule[176];

	void ExpandKey();
};

class Aes192 : public Aes
{
public:
	Aes192(unsigned char key[24]);
private:
	unsigned char key[24];
	unsigned char key_schedule[208];

	void ExpandKey();
};

class Aes256 : public Aes
{
public:
	Aes256(unsigned char key[32]);
private:
	unsigned char key[32];
	unsigned char key_schedule[240];

	void ExpandKey();
};