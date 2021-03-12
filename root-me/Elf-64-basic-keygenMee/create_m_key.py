# root-me.org 
#114 111 111 116 45 109 101 46 111 114 103

file = open(".m.key", "w")
keye = open("key", "w")

a = 0

 #   input[i]  -  i + 0x14 == input2[i]
for i in ['r', 'o', 'o', 't', '-', 'm', 'e', '.', 'o', 'r', 'g']:
    print((ord(i) + 20  - a) % 20)
    file.write(chr(ord(i) + 20 - a))
    a += 1


for i in ['r', 'o', 'o', 't', '-', 'm', 'e', '.', 'o', 'r', 'g']:
    keye.write(i)

