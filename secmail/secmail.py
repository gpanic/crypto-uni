from M2Crypto import BIO, Rand, SMIME
import smtplib

def mkbuff(text):
	return BIO.MemoryBuffer(text)

buff = mkbuff("we send this text")
Rand.load_file('randpool.dat', -1)
s = SMIME.SMIME()
s.load_key('signer_private.pem', 'signer_public.pem')
p7 = s.sign(buff)

out = BIO.MemoryBuffer();
out.write('From: %s\r\n' % "vision810@gmail.com")
out.write('To: %s\r\n' % "gregor.panic@gmail.com")
out.write('Subject: %s\r\n'% "test mail") 
s.write(out, p7)
out.close()

smtp = smtplib.SMTP('smtp.gmail.com', 587)
smtp.ehlo()
smtp.starttls()
smtp.login("nileshop0@gmail.com", "nileshop1")
smtp.sendmail("nileshop0@gmail.com", "gregor.panic@gmail.com", out.read())
smtp.close()