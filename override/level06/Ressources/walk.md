=======
## WALKTHROUGH - LEVEL06

---

When we look at the binary, we can see there are **two functions**, **main** and **auth**. We can see that **if the function auth returns 0**, the main **opens a shell**:

```sh
08048879 <main>:
[...]
 8048941:	e8 02 fe ff ff       	call   8048748 <auth>
 8048946:	85 c0                	test   eax,eax
 8048948:	75 1f                	jne    8048969 <main+0xf0>
 804894a:	c7 04 24 52 8b 04 08 	mov    DWORD PTR [esp],0x8048b52 # "Authenticated!"
 8048951:	e8 3a fc ff ff       	call   8048590 <puts@plt>
 8048956:	c7 04 24 61 8b 04 08 	mov    DWORD PTR [esp],0x8048b61 # "/bin/sh"
 804895d:	e8 3e fc ff ff       	call   80485a0 <system@plt>
```

The program takes **two user inputs**, the first as **the username**, the second as the **serial**. Both are **sent to the auth function**. It then operates **mathematical operations** with some values of the **buffer**, and then **returns 0** if the **value** obtained is **equal to the serial number** given as input:

```gdb
08048748 <auth>:
[...]
 8048866:	3b 45 f0             	cmp    eax,DWORD PTR [ebp-0x10]
 8048869:	74 07                	je     8048872 <auth+0x12a>
 804886b:	b8 01 00 00 00       	mov    eax,0x1
 8048870:	eb 05                	jmp    8048877 <auth+0x12f>
 8048872:	b8 00 00 00 00       	mov    eax,0x0
 8048877:	c9                   	leave  
 8048878:	c3                   	ret  
```

---

We can also see that **the username** need to be of **more than 5 chars**, or the auth function returns an error. We use **gdb** to **read the result** of the mathematical operations on our username.  
We can also see that there is **a call to ptrace**, so we need to **bypass** it in order to have access to the rest of the function. So we **catch the syscall**, and **creates a command** that will **change** its **return value to 1**.
We then put a **breakpoint** on the **comparison** at the end of auth, and **read the value located at [ebp-0x10]**, which is where the result of the operations is stored.

```sh
(gdb) catch syscall ptrace
Catchpoint 1 (syscall 'ptrace' [26])
(gdb) commands 1
[...]
>set $eax = 1
>continue
>end
(gdb) b *0x8048869
Breakpoint 2 at 0x8048869
(gdb) commands 2 
[...]
>x/wx $ebp-0x10
>continue
>end
(gdb) run
Starting program: /home/users/level06/level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: aaaaaaa
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 4562

Catchpoint 1 (call to syscall ptrace), 0xf7fdb440 in __kernel_vsyscall ()

Catchpoint 1 (returned from syscall ptrace), 0xf7fdb440 in __kernel_vsyscall ()

Breakpoint 2, 0x08048869 in auth ()
0xffffd5a8:	0x005f1ae1
[Inferior 1 (process 3660) exited with code 01]
(gdb) p 0x005f1ae1
$1 = 6232801
```

We can see that with the **username** `aaaaaaa`, the **result** of the operations is `6232801`. So we use them as input, and get the flag:

```sh
level06@OverRide:~$ ./level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: aaaaaaa
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6232801
Authenticated!
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```
