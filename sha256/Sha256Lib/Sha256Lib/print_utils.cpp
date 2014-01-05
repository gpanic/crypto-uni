#include <iostream>
#include <iomanip>

using namespace std;

void PrintHex(const unsigned char *arr, unsigned int size);
void PrintHexCol(const unsigned char *arr, unsigned int size, unsigned int col_cnt);
void PrintKeySchedule(const unsigned char arr[][16]);
void PrintByte(unsigned char * byte);

void PrintHex(const unsigned char *arr, unsigned int size)
{
	PrintHexCol(arr, size, size);
}

void PrintHexCol(const unsigned char *arr, unsigned int size, unsigned int col_cnt)
{
	for (int i = 0; i < size; ++i)
	{
		cout << hex << uppercase << setw(2) << setfill('0') << static_cast<int>(arr[i]);
		if (i != size - 1)
		{
			cout << " ";
		}
		if ((i + 1) % col_cnt == 0)
		{
			cout << endl;
		}
	}
	cout << dec;
}

void PrintKeySchedule(const unsigned char arr[11][16])
{
	for (int j = 0; j < 11; ++j)
	{
		for (int i = 0; i < 16; ++i)
		{
			cout << hex << uppercase << setw(2) << setfill('0') << static_cast<int>(arr[j][i]);
			if (i != 15)
			{
				cout << " ";
			}
		}
		cout << endl;
	}
	cout << dec;
}

void PrintState(const unsigned char st[4][4])
{
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 4; ++i)
		{
			cout << hex << uppercase << setw(2) << setfill('0') << static_cast<int>(st[j][i]);
			if (i != 3)
			{
				cout << " ";
			}
		}
		cout << endl;
	}
	cout << dec;
}

void PrintByte(unsigned char * byte)
{
	cout << hex << uppercase << setw(2) << setfill('0') << static_cast<int>(*byte) << endl;
	cout << dec;
}