from hill_cipher import HillCipher
from adfgvx_cipher import AdfgvxCipher
from numpy import *
from numpy.linalg import *
from utils import *

from tkinter import *
from tkinter import filedialog

# Keys ----------------------------------------
hill_key = matrix("2 4 5; 9 2 1; 3 17 7")
adfgvx_key_square = [
		  		     	['P', 'H', '0', 'Q', 'G', '6'],
		  		     	['4', 'M', 'E', 'A', '1', 'Y'],
		  		     	['L', '2', 'N', 'O', 'F', 'D'],
		  		     	['X', 'K', 'R', '3', 'C', 'V'],
		  		     	['S', '5', 'Z', 'W', '7', 'B'],
		  		     	['J', '9', 'U', 'T', 'I', '8']
					]
adfgvx_key_word = 'GERMAN'
# ---------------------------------------------

class Application(Frame):

	def __init__(self, master=None):
		Frame.__init__(self, master)
		self.f_in_name = ""
		self.f_out_name = ""
		self.createWidgets()
		self.hill_cipher = HillCipher(hill_key)
		self.adfgvx_cipher = AdfgvxCipher(adfgvx_key_square, adfgvx_key_word)
		self.current_cipher = self.hill_cipher

	def load_in_file(self):
		self.f_in_name = filedialog.askopenfilename(filetypes = [('Text files', '.txt')])
		if self.f_in_name != '':
			self.e_file_in.delete(0, END)
			self.e_file_in.insert(0, self.f_in_name)
			self.t_view.delete(1.0, END)
			self.t_view.insert(INSERT, clean_data(open(self.f_in_name).read()))

	def load_out_file(self):
		self.f_out_name = filedialog.asksaveasfilename(filetypes = [('Text files', '.txt')])
		if self.f_out_name != '':
			self.e_file_out.delete(0, END)
			self.e_file_out.insert(0, self.f_out_name)

	def method_update(self, *args):
		if self.var_mode.get() == "Encryption":
			self.b_encrypt["text"] = "Encrypt"
		else:
			self.b_encrypt["text"] = "Decrypt"

	def cipher_update(self, *args):
		if self.var_cipher.get() == "Hill":
			self.current_cipher = self.hill_cipher
		else:
			self.current_cipher = self.adfgvx_cipher

	def top_message(self, message):
		top = Toplevel()
		top.title("test")
		w = root.winfo_screenwidth() / 2 - 80
		h = root.winfo_screenheight() / 2 - 100
		top.geometry("+{}+{}".format(round(w), round(h)))

		top["padx"] = 10
		top["pady"] = 10

		msg = Message(top)
		msg["text"] = message
		msg.pack(pady=(0, 10))

		button = Button(top)
		button["text"] = "OK"
		button["command"] = top.destroy
		button.pack()

	def preview(self):
		if self.f_in_name:
			data = open(self.f_in_name).read()
			self.t_preview.delete(1.0, END)
			if self.var_mode.get() == "Encryption":
				self.t_preview.insert(INSERT, self.current_cipher.encrypt(data))
			else:
				dec = self.current_cipher.decrypt(data)
				if dec:
					self.t_preview.insert(INSERT, dec)
				else:
					self.top_message("The file is not a valid ciphertext.")
		else:
			self.top_message("Please select a file to encrypt.")
	
	def save(self):
		if self.f_in_name:
			if self.f_out_name:
				data = open(self.f_in_name).read()
				if self.var_mode.get() == "Encryption":
					self.save_file(self.current_cipher.encrypt(data))
				else:
					dec = self.current_cipher.decrypt(data)
					if dec:
						self.save_file(self.current_cipher.decrypt(data))
				self.top_message("File saved.")
			else:
				self.top_message("Please select an output file.")
		else:
			self.top_message("Please select a file to encrypt.")		

	def save_file(self, text):
		f = open(self.f_out_name, "w")
		f.write(text)
		f.close()

	def createWidgets(self):
		f1 = Frame(self)

		l_cipher = Label(f1)
		l_cipher["text"] = "Cipher:"
		l_cipher.grid(row = 0, column = 0, padx = (0, 15))

		self.var_cipher = StringVar(f1)
		self.var_cipher.set("Hill")
		self.var_cipher.trace("w", self.cipher_update)

		om_cipher = OptionMenu(f1, self.var_cipher, "Hill", "ADVGFX")
		om_cipher["width"] = 10
		om_cipher.grid(row = 0, column = 1, padx = (0, 10))

		self.var_mode = StringVar(f1)
		self.var_mode.set("Encryption")

		om_mode = OptionMenu(f1, self.var_mode, "Encryption", "Decryption")
		om_mode["width"] = 10
		om_mode.grid(row = 0, column = 2)

		f1.grid(row = 0, column = 0, pady = (0, 10), sticky = W)

		f2 = Frame(self)

		l_file_in = Label(f2)
		l_file_in["text"] = "File to encrypt:"
		l_file_in.grid(row = 0, column = 0, sticky = W)

		self.e_file_in = Entry(f2)
		self.e_file_in["width"] = 52
		self.e_file_in.grid(row = 1, column = 0, padx = (0, 15))

		b_open_file = Button(f2)
		b_open_file["text"] = "Browse"
		b_open_file["command"] = self.load_in_file
		b_open_file.grid(row = 1, column = 1)

		l_file_out = Label(f2)
		l_file_out["text"] = "Save file to:"
		l_file_out.grid(row = 2, column = 0, sticky = W)

		self.e_file_out = Entry(f2)
		self.e_file_out["width"] = 52
		self.e_file_out.grid(row = 3, column = 0, padx = (0, 15))

		b_save_file = Button(f2)
		b_save_file["text"] = "Browse"
		b_save_file["command"] = self.load_out_file
		b_save_file.grid(row = 3, column = 1)

		f2.grid(row = 2, column = 0, pady = (0, 10))

		f5 = Frame(self)

		l_view = Label(f5)
		l_view["text"] = "Original"
		l_view.grid(row = 0, column = 0, sticky = W)

		self.t_view = Text(f5)
		self.t_view["width"] = 45
		self.t_view["height"] = 8
		s_view = Scrollbar(f5, command = self.t_view.yview)
		self.t_view.config(yscrollcommand = s_view.set)
		
		self.t_view.grid(row = 1, column = 0)
		s_view.grid(row = 1, column = 1, sticky='ns')

		f5.grid(row = 3, column = 0, pady = (0, 10))

		f4 = Frame(self)

		l_preview = Label(f4)
		l_preview["text"] = "Preview"
		l_preview.grid(row = 0, column = 0, sticky = W)

		self.t_preview = Text(f4)
		self.t_preview["width"] = 45
		self.t_preview["height"] = 8
		s_preview = Scrollbar(f4, command = self.t_preview.yview)
		self.t_preview.config(yscrollcommand = s_preview.set)
		
		self.t_preview.grid(row = 1, column = 0)
		s_preview.grid(row = 1, column = 1, sticky='ns')

		f4.grid(row = 4, column = 0, pady = (0, 15))

		f3 = Frame(self)

		b_preview = Button(f3)
		b_preview["text"] = "Preview"
		b_preview["command"] = self.preview
		b_preview.grid(row = 0, column = 0, padx = (0, 15))

		self.b_encrypt = Button(f3)
		self.b_encrypt["text"] = "Encrypt"
		self.b_encrypt["command"] = self.save
		self.b_encrypt.grid(row = 0, column = 1)
		self.var_mode.trace("w", self.method_update)

		f3.grid(row = 5, column = 0, pady = (0, 10), sticky = W)


root = Tk()
root.title("Classic Ciphers")
root.resizable(width=FALSE, height=FALSE)

w = root.winfo_screenwidth() / 2 - 220
h = root.winfo_screenheight() / 2 - 295
root.geometry("+{}+{}".format(round(w), round(h)))

app = Application(master = root)
app["padx"] = 20
app["pady"] = 20
app.pack()
root.mainloop()