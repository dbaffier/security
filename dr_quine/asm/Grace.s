%macro grace 0
section .text
	extern _dprintf
	extern _open
	global _main
_main:
	push rbp
	mov rax, 0x2000004
	mov rdi, f
	mov rsi, 1538
	mov rdx, 420
	call _open
	mov rdi, rax
	mov rsi, c
	mov rdx, 10
	mov rcx, 9
	mov r8, 34
	mov r9, c
	call _dprintf
	pop rbp
	mov rax, 0
	ret
;;;
section .data
	c: db "%%macro grace 0%1$csection .text%1$c%2$cextern _dprintf%1$c%2$cextern _open%1$c%2$cglobal _main%1$c_main:%1$c%2$cpush rbp%1$c%2$cmov rax, 0x2000004%1$c%2$cmov rdi, f%1$c%2$cmov rsi, 1538%1$c%2$cmov rdx, 420%1$c%2$ccall _open%1$c%2$cmov rdi, rax%1$c%2$cmov rsi, c%1$c%2$cmov rdx, 10%1$c%2$cmov rcx, 9%1$c%2$cmov r8, 34%1$c%2$cmov r9, c%1$c%2$ccall _dprintf%1$c%2$cpop rbp%1$c%2$cmov rax, 0%1$c%2$cret%1$c;;;%1$csection .data%1$c%2$cc: db %3$c%4$s%3$c,0%1$c%2$cf: db %3$cGrace_kid.s%3$c, 0%1$c%%endmacro%1$c%%macro a 0%1$c%%endmacro%1$c%%macro b 0%1$c%%endmacro%1$c%1$cgrace%1$c",0
	f: db "Grace_kid.s", 0
%endmacro
%macro a 0
%endmacro
%macro b 0
%endmacro

grace
