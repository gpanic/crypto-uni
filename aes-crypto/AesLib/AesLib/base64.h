#include <string>

std::string base64_encode(unsigned char const*, unsigned int len);
std::string base64_decode(std::string const& s);
std::string b64_enc(std::string s);
std::string b64_dec(std::string s);