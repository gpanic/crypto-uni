#include <iostream>
#include <iomanip>

using namespace std;

void PrintHex(const unsigned char *arr, unsigned int size);
void PrintHexCol(const unsigned char *arr, unsigned int size, unsigned int col_cnt);
void PrintKeySchedule(const unsigned char arr[][16]);

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
}