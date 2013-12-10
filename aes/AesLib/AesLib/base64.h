#pragma once
#include <string>

using namespace std;

string base64_encode(unsigned char const* in, unsigned int len);
string base64_decode(string const& s);
string b64_enc(string s);
string b64_dec(string s);