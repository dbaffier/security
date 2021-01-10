from pwn import *

conn = remote('0', 9007)
conn.recvuntil('Ready? starting in 3 sec')
conn.recvline()
conn.recvline()
#conn.recv(10024)
# BINARY SEARCH
for _ in range(100):
        line = conn.recv(1024).decode('UTF-8').strip().split(' ')
        print(line)
        N = int(line[0].split('=')[1])
        C = int(line[1].split('=')[1])

        start = 0
        end = N

        for _ in range(C):
                guess = ' '.join(str(start) for start in range(start, int((start+end)/2)))
                conn.sendline(guess)
                output = int(conn.recv(1024).decode('UTF-8').strip())
                if (output % 10 == 0):
                        start = int((start + end) / 2)
                else:
                        end = int((start + end) /  2)
        conn.sendline(str(start))
        print(conn.recv(1024).decode('UTF-8'))
print(conn.recv(1024).decode('UTF-8'))
conn.close()
