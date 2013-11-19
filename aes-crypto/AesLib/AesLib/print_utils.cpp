#include <iostream>
#include <iomanip>

using namespace std;

void PrintHexCol(const unsigned char *, unsigned int, unsigned int);
void PrintHex(const unsigned char *, unsigned int);

void PrintHex(const unsigned char *arr, unsigned int size)
{
	PrintHexCol(arr, size, size);
}

void PrintHexCol(const unsigned char *arr, unsigned int size, unsigned int col_cnt)
{
	for (unsigned int i = 0; i < size; ++i)
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