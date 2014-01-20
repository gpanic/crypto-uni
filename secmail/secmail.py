from M2Crypto import BIO, Rand, SMIME
import smtplib
from email.mime.text import MIMEText

def mkbuff(text):
	return BIO.MemoryBuffer(text)


msg = "we send this text"
msg_mime = MIMEText(msg)

buff = mkbuff(msg)
Rand.load_file('randpool.dat', -1)
s = SMIME.SMIME()
s.load_key('sender-private.pem', 'sender-public.pem')
p7 = s.sign(buff)

out = BIO.MemoryBuffer();
out.write('From: %s\r\n' % "vision810@gmail.com")
out.write('To: %s\r\n' % "gregor.panic@gmail.com")
out.write('Subject: %s\r\n'% "test mail")
out.write(msg_mime.as_string())
s.write(out, p7)
out.close()

smtp = smtplib.SMTP('smtp.gmail.com', 587)
smtp.ehlo()
smtp.starttls()
smtp.login("nileshop0@gmail.com", "nileshop1")
smtp.sendmail("nileshop0@gmail.com", "gregor.panic@gmail.com", out.read())
smtp.close()