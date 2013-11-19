#include <iostream>
#include <iomanip>

using namespace std;

void PrintHex(unsigned char *arr, unsigned int size)
{
	for (unsigned int i = 0; i < size; ++i)
	{
		cout << hex << uppercase << setw(2) << setfill('0') << static_cast<int>(arr[i]);
		if (i != size - 1)
		{
			cout << " ";
		}
	}
	cout << endl;
}