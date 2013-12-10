void CopyArray(unsigned char *in, unsigned char *out, int size)
{
	for (int i = 0; i < size; ++i)
	{
		out[i] = in[i];
	}
}

void XorArray(unsigned char *arr1, unsigned char*arr2, int size)
{
	for (int i = 0; i < size; ++i)
	{
		arr1[i] ^= arr2[i];
	}
}