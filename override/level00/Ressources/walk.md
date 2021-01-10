## WALKTHROUGH - LEVEL00

---

When we execute the program level00, we can see that it is **waiting for a password** to authenticate the user.

When we look at the binary, we can see that the program uses **scanf** to get the user input, compares it to **0x149c** or **5276**, and **opens a shell** if the input matches:

So we can use 5276 as the input, and get the password for level01:

```sh
level00@OverRide:~$ ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```