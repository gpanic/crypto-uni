from numpy import *
from numpy.linalg import *
from utils import *
import matrix_utils

class HillCipher:
	def __init__(self, key):
		self.key = key
		self.key_len = len(key)

	def hill_encrypt(self, key, plain):
		plain = clean_data(plain)
		plain_len = len(plain)
		plain_buffer = empty([self.key_len, 1])
		enc_str = ""
		for i in range(0, plain_len, self.key_len):
			plain_chunk = list(plain[i : i + self.key_len])
			plain_chunk = [ord(x) - 65  for x in plain_chunk]
			plain_chunk_len = len(plain_chunk)
			if plain_chunk_len < self.key_len:
				plain_chunk += [0] * (self.key_len - plain_chunk_len)
			plain_buffer[0 : self.key_len, 0] = plain_chunk
			enc = (key * plain_buffer) % 26
			enc_str += self.mat_to_str(enc)
		return enc_str

	def encrypt(self, plain):
		return self.hill_encrypt(self.key, plain)
		

	def decrypt(self, plain):
		return self.hill_encrypt(matrix_utils.modular_inverse(self.key, 26), plain)

	def mat_to_str(self, mat):
		s = mat.tolist()
		s = [chr(int(x[0] + 65)) for x in mat]
		return "".join(s)

'''
hill_key = matrix("2 4 5; 9 2 1; 3 17 7")
hc = HillCipher(hill_key)
enc = hc.encrypt("ATTACK")
print(enc)
dec = hc.decrypt(enc)
print(dec)
'''