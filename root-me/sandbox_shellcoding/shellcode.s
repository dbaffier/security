

section .text
	global _start

_start:
	jmp bypass

next:
	pop rdi
	;xor sil, sil
	xor dl, dl
	mov al, 2
	syscall
	push rax
	push rax
	pop rdi
	sub rsp, 256
	mov rdi, rax
	mov rsi, rsp
	mov dl, 128
	mov al, 217
	syscall
	pop rdi
	mov rsi, rsp
	mov rdx, 32
	mov al, 0
	syscall
	




bypass:
	call next
	db 'passwd'
