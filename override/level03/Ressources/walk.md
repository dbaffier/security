## WALKTHROUGH - LEVEL03

---

We have an executable who **asks for a password**.

The main gets it with scanf as an integer and sends to the function `test` with the number **322424845**.

The test function **substracts the password to the number**, stores the result and **compares it with 0x15 or 21**

```
 804874d:	8b 45 08             	mov    eax,DWORD PTR [ebp+0x8]
 8048750:	8b 55 0c             	mov    edx,DWORD PTR [ebp+0xc]
 8048753:	89 d1                	mov    ecx,edx
 8048755:	29 c1                	sub    ecx,eax
 8048757:	89 c8                	mov    eax,ecx
 8048759:	89 45 f4             	mov    DWORD PTR [ebp-0xc],eax
 804875c:	83 7d f4 15          	cmp    DWORD PTR [ebp-0xc],0x15
```

If the result is **superior to 21**, it calls the **decrypt** function with a **random number** as **parameter.**

If the result is **inferior or equal to 21**, it calls the **decrypt** function with the **result** as **parameter**.

The **decrypt** function then **takes the result** and uses it to **xor each byte** of the string **"Q}|u`sfg~sf{}|a3"**. It then compares it to **"Congratulations!"**, and **opens a shell if they match**.

We use the website http://xor.pw/ to **determine the value of the result needed** to make those strings the same, and **compares the first byte of each string**. It gives us a result of **18**.

We **substract 18 to the number** given in the main, and we get:

```gdb
(gdb) p 322424845-18
$10 = 322424827
```

And if we use it as the password, it opens a shell:

```
level03@OverRide:~$ ./level03 
***********************************
*		level03		**
***********************************
Password:322424827
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```
