#include <iostream>
#include <bitset>
#include <iomanip>
#include <cstdint>
#include <vector>
#include <fstream>
#include <sstream>

#include "sha256.h"
#include "print_utils.h"

using namespace std;

#define CCATBYTES(b0,b1,b2,b3) (b0 << 24 | b1 << 16 | b2 << 8 | b3);

using namespace std;

inline unsigned long Sha256::rrot32(unsigned long w, int a)
{
	return ((w >> a) | (w << (32 - a)));
}

inline unsigned long Sha256::lrot32(unsigned long w, int a)
{
	return ((w << a) | (w >> (32 - a)));
}

void Sha256::appendlen64(unsigned char *buff, int64_t len)
{
	unsigned char *p = (unsigned char *)&len;
	for (int i = 56; i < 64; ++i)
	{
		buff[i] = p[63 - i];
	}
}

void Sha256::padzero(unsigned char *buff, int start, int end)
{
	for (int i = start; i < end; ++i)
	{
		buff[i] = 0x00;
	}
}

string Sha256::hash(string filename)
{
	unsigned long w[64];
	unsigned long s0, s1;
	unsigned long S0, S1, temp1, temp2, ch, maj;
	unsigned long a, b, c, d, e, f, g, h;
	unsigned char buff[64];

	unsigned long h0 = 0x6a09e667;
	unsigned long h1 = 0xbb67ae85;
	unsigned long h2 = 0x3c6ef372;
	unsigned long h3 = 0xa54ff53a;
	unsigned long h4 = 0x510e527f;
	unsigned long h5 = 0x9b05688c;
	unsigned long h6 = 0x1f83d9ab;
	unsigned long h7 = 0x5be0cd19;


	int mlen;
	unsigned char msg[64];
	ifstream file(filename, ios::in | ios::binary | ios::ate);
	if (file.is_open())
	{
		mlen = file.tellg();
		file.seekg(0, ios::beg);

		int64_t lenbits = mlen * 8;
		int ppmlen = ((mlen + 8) / 64) * 64 + 64;
		int padlen = ppmlen - mlen;
		int left;

		for (int p = 0; p < ppmlen; p += 64)
		{
			// if the next processed chunk has to be padded
			if (p + 64 <= ppmlen - padlen)
			{
				file.read((char*)msg, 64);

				// copy chunk
				for (int i = 0; i < 16; ++i)
				{
					w[i] = CCATBYTES(msg[i * 4], msg[i * 4 + 1], msg[i * 4 + 2], msg[i * 4 + 3]);
				}
			}
			else
			{
				left = mlen - p;
				file.read((char*)msg, left);

				if (left > 0)
				{
					// pad message with 10000000 0 and length if space
					for (int i = 0; i < left; ++i)
					{
						buff[i] = msg[i];
					}
					if (64 - left >= 9)
					{
						buff[left] = 0x80;
						padzero(buff, left + 1, 56);
						appendlen64(buff, lenbits);
					}
					else
					{
						buff[left] = 0x80;
						padzero(buff, left + 1, 64);
					}
				}
				else if (left < 0)
				{
					// padd 0 end with length
					padzero(buff, 0, 56);
					appendlen64(buff, lenbits);
				}
				else
				{
					// pad 10000000 end with length
					buff[0] = 0x80;
					padzero(buff, 1, 56);
					appendlen64(buff, lenbits);
				}

				// copy padded chunk
				for (int i = 0; i < 16; ++i)
				{
					w[i] = CCATBYTES(buff[i * 4], buff[i * 4 + 1], buff[i * 4 + 2], buff[i * 4 + 3]);
				}
			}

			for (int i = 16; i < 64; ++i)
			{
				s0 = (rrot32(w[i - 15], 7) ^ rrot32(w[i - 15], 18) ^ (w[i - 15] >> 3));
				s1 = (rrot32(w[i - 2], 17) ^ rrot32(w[i - 2], 19) ^ (w[i - 2] >> 10));
				w[i] = w[i - 16] + s0 + w[i - 7] + s1;
			}

			a = h0;
			b = h1;
			c = h2;
			d = h3;
			e = h4;
			f = h5;
			g = h6;
			h = h7;

			for (int i = 0; i < 64; ++i)
			{
				S1 = rrot32(e, 6) ^ rrot32(e, 11) ^ rrot32(e, 25);
				ch = (e & f) ^ ((~e) & g);
				temp1 = h + S1 + ch + k[i] + w[i];
				S0 = rrot32(a, 2) ^ rrot32(a, 13) ^ rrot32(a, 22);
				maj = (a & b) ^ (a & c) ^ (b & c);
				temp2 = S0 + maj;

				h = g;
				g = f;
				f = e;
				e = d + temp1;
				d = c;
				c = b;
				b = a;
				a = temp1 + temp2;
			}

			h0 += a;
			h1 += b;
			h2 += c;
			h3 += d;
			h4 += e;
			h5 += f;
			h6 += g;
			h7 += h;
		}

		unsigned char *tp;
		unsigned long hash[8] = { h0, h1, h2, h3, h4, h5, h6, h7 };
		unsigned char digest[32];
		stringstream ss;


		for (int i = 0; i < 8; ++i)
		{
			tp = (unsigned char *)&hash[i];
			for (int j = 3; j >= 0; --j)
			{
				ss << hex << setw(2) << setfill('0') << (int)tp[j];
			}
		}
		return ss.str();
	}
}