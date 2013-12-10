#pragma once

class AesStatics
{
public:
	static const unsigned char rcon[];
	static const unsigned char sbox[];
	static const unsigned char sbox_inv[];
	static const int mix_mat[];
	static const int mix_mat_inv[];
	static const unsigned char gmul2[];
	static const unsigned char gmul3[];
	static const unsigned char gmul9[];
	static const unsigned char gmul11[];
	static const unsigned char gmul13[];
	static const unsigned char gmul14[];
};