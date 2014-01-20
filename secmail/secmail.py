from M2Crypto import BIO, Rand, SMIME, X509
import smtplib
from email.mime.text import MIMEText

class Email:
	def __init__(self, frm=None, to=None, from_key=None, from_cert=None, to_cert=None, subject=None, message=None):
		self.frm = frm
		self.to = to
		self.from_key = from_key
		self.from_cert = from_cert
		self.to_cert = to_cert
		self.subject = subject
		self.message = message

def send_secmail(email, username, password, encrypt, sign):
	msg_bio = BIO.MemoryBuffer(email.message)
	smime = SMIME.SMIME()

	if sign:
		smime.load_key(email.from_key, email.from_cert)
		if encrypt:
			flags=SMIME.PKCS7_TEXT
		else:
			flags=SMIME.PKCS7_TEXT|SMIME.PKCS7_DETACHED
		p7 = smime.sign(msg_bio, flags=flags)
		msg_bio = BIO.MemoryBuffer(email.message)

	if encrypt:
		cert_stack = X509.X509_Stack()
		cert = X509.load_cert(email.to_cert)
		cert_stack.push(cert)
		smime.set_x509_stack(cert_stack)
		smime.set_cipher(SMIME.Cipher('aes_128_cbc'))

		if sign:
			tmp = BIO.MemoryBuffer()
			smime.write(tmp, p7)
			p7 = smime.encrypt(tmp)
		else:
			p7 = smime.encrypt(msg_bio, SMIME.PKCS7_TEXT)
	
	out = BIO.MemoryBuffer()
	out.write("From: {}\r\n".format(email.frm))
	out.write("To: {}\r\n".format(email.to))
	out.write("Subject: {}\r\n".format(email.subject))

	if encrypt:
		smime.write(out, p7)
	else:
		if sign:
			smime.write(out, p7, msg_bio, SMIME.PKCS7_TEXT)
		else:
			out.write("Content-Type: text/plain; charset=\"utf-8\"; format=flowed\n")
			out.write("MIME-Version: 1.0\n")
			out.write("Content-Transfer-Encoding: 7bit\n")
			out.write(email.message)

	smtp = smtplib.SMTP('smtp.gmail.com', 587)
	smtp.ehlo()
	smtp.starttls()
	smtp.login(username, password)
	smtp.sendmail(email.frm, email.to, out.read())
	smtp.close()

#email = Email(frm="nileshop0@gmail.com", to="gregor.panic@gmail.com", from_key="sender-private.pem", from_cert="sender-public.pem", to_cert="gregor.crt", subject="testmail", message="aajajajaj")
#send_secmail(email, "nileshop0@gmail.com", "nileshop1", False, False)