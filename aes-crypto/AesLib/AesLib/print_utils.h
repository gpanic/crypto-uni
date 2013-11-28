#pragma once

using namespace std;

void PrintHex(const unsigned char *arr, unsigned int size);
void PrintHexCol(const unsigned char *arr, unsigned int size, unsigned int col_cnt);
void PrintKeySchedule(const unsigned char arr[11][16]);
void PrintState(const unsigned char st[4][4]);
void PrintByte(unsigned char * byte);