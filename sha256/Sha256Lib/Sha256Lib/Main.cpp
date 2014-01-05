#include <iostream>
#include <string>

#include "sha256.h"
#include "print_utils.h"

using namespace std;

int main()
{
	unsigned char msg[] = "The quick brown fox jumps over the lazy dog";
	unsigned char digest[32];
	Sha256::hash(msg, sizeof(msg) - 1, digest);
	PrintHexCol(digest, 32, 16);
	cin.get();
}