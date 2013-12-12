#include <string>
#include <tuple>

using namespace std;

class Rc4
{
public:
	static void encrypt_file(string in, string out, unsigned char key[], int key_len);
	static void encrypt_file2(string in, string out, string key);
	static void create_key(string out);
	static void load_key(string in, unsigned char *out);
private:
	static const int buffer_size = 512;
	static void xor_array(unsigned char a1[], unsigned char a2[], int size);
	static void generate_key(unsigned int size, unsigned char *out);
	static void ksa(unsigned char s[], unsigned char key[], int key_len);
	static void prga(unsigned char s[], unsigned char out[], int out_cnt);
	static void iprga(unsigned char s[], unsigned char out[], int out_cnt, int &i, int &j);
};