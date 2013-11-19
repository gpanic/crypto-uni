from utils import *
from copy import *
from operator import itemgetter

class AdfgvxCipher:
	def __init__(self, key_square, key_word):
		self.key_square = key_square
		self.key_word = key_word
		self.key_square_hash = {}
		self.adfgvx = ['A', 'D', 'F', 'G', 'V', 'X']
		self.adfgvx_hash = {'A' : 0, 'D' : 1, 'F' : 2, 'G' : 3, 'V' : 4, 'X' : 5}
		if self.is_key_valid():
			self.create_square_hash()
		else:
			self.key_square = None

	def encrypt(self, plain):
		if not self.key_square:
			return None
		plain = clean_data(plain)
		cipher_text = "".join([self.key_square_hash[x] for x in plain])
		word_columns = self.text_to_columns(cipher_text)
		word_columns = sorted(word_columns, key = itemgetter(0))
		cipher_text = "".join([c[1] for c in word_columns])
		return cipher_text
		

	def decrypt(self, cipher_text):
		if not self.key_square:
			return None
		cipher_text = clean_data(cipher_text)
		if self.is_cipher_text(cipher_text):
			count = self.column_char_count(len(cipher_text))
			word_columns = self.cipher_text_to_columns(count, cipher_text)
			word_columns = self.sort_by_keyword(word_columns)
			cipher_text = self.columns_to_text(word_columns)
			plain = self.cipher_to_plain(cipher_text)
			return plain
		else:
			return None

	def is_key_valid(self):
		all_chars = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']
		if sorted([i for j in adfgvx_key_square for i in j]) != all_chars:
			return False
		else:
			return True

	def is_cipher_text(self, cipher_text):
		if len(cipher_text) % 2 != 0:
			return False
		for c in cipher_text:
			if c not in self.adfgvx:
				return False
		return True

	def cipher_to_plain(self, cipher_text):
		plain = ""
		for x in range(0, len(cipher_text), 2):
			j = self.adfgvx_hash[cipher_text[x]]
			i =	self.adfgvx_hash[cipher_text[x + 1]]
			plain += self.key_square[j][i]
		return plain

	def columns_to_text(self, word_columns):
		cipher_text = ""
		counter = 0
		while len(word_columns) > 0:
			counter = 0
			for c in word_columns:
				if c[2] == '':
					counter += 1
				else:
					cipher_text += c[2][0]
					c[2] = c[2][1:]
			if counter == len(word_columns):
				break
		return cipher_text

	def sort_by_keyword(self, word_columns):
		key_word_copy = copy(self.key_word)
		repeated_chars = {}
		for c in word_columns:
			i = key_word_copy.index(c[0])
			key_word_copy = key_word_copy.replace(c[0], "_", 1)
			c.insert(0, i)
		return sorted(word_columns)

	def cipher_text_to_columns(self, count, cipher_text):
		word_columns = self.init_word_columns()
		word_columns = sorted(word_columns, key = itemgetter(0))
		for i, count in enumerate(count):
			word_columns[i][1] = cipher_text[0 : count[1]]
			cipher_text = cipher_text[count[1]:]
		return word_columns

	def column_char_count(self, ct_len):
		word_columns = self.init_word_columns(0)
		cnt = int(ct_len / len(self.key_word))

		word_columns = [[c[0], cnt] for c in word_columns]
		for c in range(0, ct_len % len(self.key_word)):
			word_columns[c][1] += 1
		return sorted(word_columns)

	def text_to_columns(self, cipher_text):
		word_columns = self.init_word_columns()
		for i, c in enumerate(cipher_text):
			word_columns[i % len(self.key_word)][1] += c
		return word_columns

	def init_word_columns(self, init = ""):
		word_columns = [[c, init] for c in self.key_word]
		return word_columns

	def word_columns_to_hash(self, word_columns):
		wc_hash = { c[0]: c[1] for c in word_columns }
		return wc_hash

	def create_square_hash(self):
		key_square_w = range(0, len(self.key_square[0]))
		key_square_h = range(0, len(self.key_square))
		self.key_square_hash = { self.key_square[j][i]: self.adfgvx[j] + self.adfgvx[i] for i in key_square_h for j in key_square_w }

'''
adfgvx_key_square = [
	  		     		['P', 'H', '0', 'Q', 'G', '6'],
		  		     	['4', 'M', 'E', 'A', '1', 'Y'],
		  		     	['L', '2', 'N', 'O', 'F', 'D'],
		  		     	['X', 'K', 'R', '3', 'C', 'V'],
		  		     	['S', '5', 'Z', 'W', '7', 'B'],
		  		     	['J', '9', 'U', 'T', 'I', '8']
			 		]
adfgvx_key_word = 'GERMAN'
ac = AdfgvxCipher(adfgvx_key_square, adfgvx_key_word)
enc = ac.encrypt("ATTACK")
print(enc)
unc = ac.decrypt(enc)
print(unc)
'''