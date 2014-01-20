from Tkinter import *
import tkFileDialog as filedialog
from secmail import *

class Application(Frame):

	def __init__(self, master=None, window_w=250, window_h=150):
		Frame.__init__(self, master)
		self.master = master
		self.window_w = window_w
		self.window_h = window_h
		self.init()
		self.centerWindow()

	def send(self):
		self.dialog.destroy()

		e = Email()
		e.frm = self.entry_from.get()
		e.to = self.entry_to.get()
		e.from_key = str(self.entry_from_key.get())
		e.from_cert = str(self.entry_from_cert.get())
		e.to_cert = self.entry_to_cert.get()
		e.subject = self.entry_subject.get()
		e.message = str(self.t1.get('1.0', END))
		send_secmail(e, self.username.get(), self.password.get(), self.check_encrypt.get(), self.check_sign.get())

		dialog = Toplevel()
		dialog.title("Secmail")
		w = 100
		h = 120
		sw = self.master.winfo_screenwidth()
		sh = self.master.winfo_screenheight()
		x = (sw - w)/2
		y = (sh - h)/2
		dialog.geometry('%dx%d+%d+%d' % (w, h, x, y))
		dialog.focus()


		f1 = Frame(dialog)
		l1 = Label(f1)
		l1["text"] = "Email sent."
		l1.pack(pady=(0, 20))

		b1 = Button(f1)
		b1["text"] = "OK"
		b1["command"] = dialog.destroy
		b1["width"] = 6
		b1.pack()

		f1.pack(padx=20, pady=20)


	def login(self):
		self.dialog = Toplevel(self)
		self.dialog.title("Log into Gmail")
		self.dialog.resizable(width=FALSE, height=FALSE)

		w = 300
		h = 200
		sw = self.master.winfo_screenwidth()
		sh = self.master.winfo_screenheight()
		x = (sw - w)/2
		y = (sh - h)/2
		self.dialog.geometry('%dx%d+%d+%d' % (w, h, x, y))
		self.dialog.focus()


		f1 = Frame(self.dialog)

		l1 = Label(f1)
		l1["text"] = "Username"
		l1.grid(row=0, column=0, pady=(0,5), sticky=W)

		self.username = StringVar()
		e1 = Entry(f1)
		e1["width"] = 30
		e1["textvariable"] = self.username
		e1.grid(row=1, column=0, pady=(0,15))

		l2 = Label(f1)
		l2["text"] = "Password"
		l2.grid(row=3, column=0, pady=(0,5), sticky=W)

		self.password = StringVar()
		e2 = Entry(f1)
		e2["width"] = 30
		e2["textvariable"] = self.password
		e2["show"] = "*"
		e2.grid(row=4, column=0, pady=(0,25))

		b1 = Button(f1)
		b1["text"] = "Log in"
		b1["width"] = 15
		b1["command"] = self.send
		b1.grid(row=5, column=0)

		f1.pack(padx=20, pady=20)

	def select_file(self, entry):
		f = filedialog.Open().show()
		entry.set(f)

	def checked_sign(self):
		if self.check_sign.get() == 1:
			self.b1["state"] = NORMAL
			self.e4["state"] = NORMAL
			self.b2["state"] = NORMAL
			self.e5["state"] = NORMAL
		else:
			self.b1["state"] = DISABLED
			self.e4["state"] = DISABLED
			self.b2["state"] = DISABLED
			self.e5["state"] = DISABLED

	def checked_encrypt(self):
		if self.check_encrypt.get() == 1:
			self.b3["state"] = NORMAL
			self.e6["state"] = NORMAL
		else:
			self.b3["state"] = DISABLED
			self.e6["state"] = DISABLED

	def init(self):
		self.master.title("Secmail")
		self.master.resizable(width=FALSE, height=FALSE)

		f1 = Frame(self)

		l1 = Label(f1)
		l1["text"] = "From"
		l1.grid(row=0, column=0, pady=(0,12), sticky=W)

		self.entry_from = StringVar()
		e1 = Entry(f1)
		e1["width"] = 65
		e1["textvariable"] = self.entry_from
		e1.grid(row=0, column=1, padx=(20,0), pady=(0,12))
		
		l2 = Label(f1)
		l2["text"] = "To"
		l2.grid(row=1, column=0, pady=(0,12), sticky=W)

		self.entry_to = StringVar()
		e2 = Entry(f1)
		e2["width"] = 65
		e2["textvariable"] = self.entry_to
		e2.grid(row=1, column=1, padx=(20,0), pady=(0,12))

		l3 = Label(f1)
		l3["text"] = "Subject"
		l3.grid(row=2, column=0, pady=(0,12), sticky=W)

		self.entry_subject = StringVar()
		e3 = Entry(f1)
		e3["width"] = 65
		e3["textvariable"] = self.entry_subject
		e3.grid(row=2, column=1, padx=(20,0), pady=(0,12))

		f1.grid(row=0, column=0)

		f2 = Frame(self)

		l3 = Label(f2)
		l3["text"] = "Message"
		l3.grid(row=0, column=0, pady=(0,5), sticky=W)

		self.t1 = Text(f2)
		self.t1["width"] = 57
		self.t1["height"] = 15
		self.t1.grid(row=1, column=0, pady=(0,12))

		f2.grid(row=1, column=0)

		f3 = Frame(self)


		self.check_sign = IntVar()
		c1 = Checkbutton(f3)
		c1["text"] = "Sign"
		c1["variable"] = self.check_sign
		c1["command"] = self.checked_sign
		c1.grid(row=0, column=0, pady=(0,12))

		self.check_encrypt = IntVar()
		c2 = Checkbutton(f3)
		c2["text"] = "Encrypt"
		c2["variable"] = self.check_encrypt
		c2["command"] = self.checked_encrypt
		c2.grid(row=0, column=1, pady=(0,12))

		f3.grid(row=2, column=0)

		f4 = Frame(self)

		l4 = Label(f4)
		l4["text"] = "Sender key"
		l4.grid(row=0, column=0, pady=(0,12), sticky=W)

		self.entry_from_key = StringVar()
		self.e4 = Entry(f4)
		self.e4["width"] = 48
		self.e4["textvariable"] = self.entry_from_key
		self.e4["state"] = DISABLED
		self.e4.grid(row=0, column=1, padx=(20,0), pady=(0,12))

		self.b1 = Button(f4)
		self.b1["text"] = "Browse"
		self.b1["state"] = DISABLED
		self.b1["command"] = lambda: self.select_file(self.entry_from_key)
		self.b1.grid(row=0, column=2, padx=(20,0), pady=(0,12))

		l5 = Label(f4)
		l5["text"] = "Sender cert"
		l5.grid(row=1, column=0, pady=(0,12), sticky=W)

		self.entry_from_cert = StringVar()
		self.e5 = Entry(f4)
		self.e5["width"] = 48
		self.e5["textvariable"] = self.entry_from_cert
		self.e5["state"] = DISABLED
		self.e5.grid(row=1, column=1, padx=(20,0), pady=(0,12))

		self.b2 = Button(f4)
		self.b2["text"] = "Browse"
		self.b2["state"] = DISABLED
		self.b2["command"] = lambda: self.select_file(self.entry_from_cert)
		self.b2.grid(row=1, column=2, padx=(20,0), pady=(0,12))

		l6 = Label(f4)
		l6["text"] = "Recipient cert"
		l6.grid(row=2, column=0, pady=(0,12), sticky=W)

		self.entry_to_cert = StringVar()
		self.e6 = Entry(f4)
		self.e6["width"] = 48
		self.e6["textvariable"] = self.entry_to_cert
		self.e6["state"] = DISABLED
		self.e6.grid(row=2, column=1, padx=(20,0), pady=(0,12))

		self.b3 = Button(f4)
		self.b3["text"] = "Browse"
		self.b3["state"] = DISABLED
		self.b3["command"] = lambda: self.select_file(self.entry_to_cert)
		self.b3.grid(row=2, column=2, padx=(20,0), pady=(0,12))

		f4.grid(row=3, column=0)

		f5 = Frame(self)

		b4 = Button(f5)
		b4["text"] = "Send"
		b4["width"] = 10
		b4["command"] = self.login
		b4.grid(row=2, column=2, padx=(0,0), pady=(5,0), sticky=W)

		f5.grid(row=4, column=0)

		self.pack(padx=(20,20), pady=(20,20))


	def centerWindow(self):
		w = self.window_w
		h = self.window_h
		sw = self.master.winfo_screenwidth()
		sh = self.master.winfo_screenheight()
		x = (sw - w)/2
		y = (sh - h)/2
		self.master.geometry('%dx%d+%d+%d' % (w, h, x, y))

def main():
	root = Tk()
	app = Application(root, 500, 610)
	root.mainloop()

if __name__ == '__main__':
    main()