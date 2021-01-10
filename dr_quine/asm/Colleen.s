section .text
	extern _printf
	global _main
;1
_main:
	push rbp
	mov rdi, c
	mov rsi, 10
	mov rdx, 9
	mov rcx, 34
	mov r8, c
	call _printf
	;2
	pop rbp
	mov rax, 0
	call random
random:
	ret

section .data
	c: db "section .text%1$c%2$cextern _printf%1$c%2$cglobal _main%1$c;1%1$c_main:%1$c%2$cpush rbp%1$c%2$cmov rdi, c%1$c%2$cmov rsi, 10%1$c%2$cmov rdx, 9%1$c%2$cmov rcx, 34%1$c%2$cmov r8, c%1$c%2$ccall _printf%1$c%2$c;2%1$c%2$cpop rbp%1$c%2$cmov rax, 0%1$c%2$ccall random%1$crandom:%1$c%2$cret%1$c%1$csection .data%1$c%2$cc: db %3$c%4$s%3$c,0%1$c",0
