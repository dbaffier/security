section .text
	extern _access
	extern _dprintf
	extern _open
	extern _sprintf
	extern _system
	extern _close
	extern _memset
	global _main
_main:
	push rbp
	mov rbp, rsp
	sub rsp, 128
	mov eax, dword [rel i]
	mov dword [rsp + 16], eax
	cmp eax, 0
	je finish
	lea rdi, [rel d]
	mov rsi, 4
	call _access
	cmp rax, -1
	jne decr

back:
	lea rdi, [rsp]
	lea rsi, [rel fmt]
	mov edx, dword [rsp + 16]
	call _sprintf
	mov rax, 0x2000004
	lea rdi, [rsp]
	mov rsi, 1537
	mov rdx, 420
	call _open
	mov dword [rsp + 20], eax
	mov edi, dword [rsp + 20]
	lea rsi, [rel a]
	mov rdx, 10
	mov rcx, 9
	mov r8, 34
	mov r9d, dword [rsp + 16]
	lea rax, [rel a]
	mov [rsp], rax
	call _dprintf
	mov edi, dword [rsp + 20]
	call _close
	lea rdi, [rsp + 24]
	lea rsi, [rel fmtt]
	mov edx, dword [rsp + 16]
	call _sprintf
	lea rdi, [rsp + 24]
	call _system
	lea rdi, [rsp + 24]
	mov rsi, 0
	mov rdx, 25
	call _memset
	lea rdi, [rsp + 24]
	lea rsi, [rel fmttt]
	mov edx, dword [rsp + 16]
	call _sprintf
	cmp dword [rsp + 16], 0
	jg exec

finish:
	mov rax, 0
	add rsp, 128
	pop rbp
	ret

exec:
	lea rdi, [rsp + 24]
	call _system
	jmp finish

decr:
	mov eax, dword [rsp + 16]
	dec eax
	mov dword [rsp + 16], eax
	jmp back

section .data
	d db "Sully_5.s", 0
	fmt db "Sully_%d.s", 0
	fmtt db "nasm -f macho64 Sully_%1$d.s && gcc -o Sully_%1$d Sully_%1$d.o && rm Sully_%1$d.o", 0
	fmttt db "./Sully_%1$d", 0
	a db "section .text%1$c%2$cextern _access%1$c%2$cextern _dprintf%1$c%2$cextern _open%1$c%2$cextern _sprintf%1$c%2$cextern _system%1$c%2$cextern _close%1$c%2$cextern _memset%1$c%2$cglobal _main%1$c_main:%1$c%2$cpush rbp%1$c%2$cmov rbp, rsp%1$c%2$csub rsp, 128%1$c%2$cmov eax, dword [rel i]%1$c%2$cmov dword [rsp + 16], eax%1$c%2$ccmp eax, 0%1$c%2$cje finish%1$c%2$clea rdi, [rel d]%1$c%2$cmov rsi, 4%1$c%2$ccall _access%1$c%2$ccmp rax, -1%1$c%2$cjne decr%1$c%1$cback:%1$c%2$clea rdi, [rsp]%1$c%2$clea rsi, [rel fmt]%1$c%2$cmov edx, dword [rsp + 16]%1$c%2$ccall _sprintf%1$c%2$cmov rax, 0x2000004%1$c%2$clea rdi, [rsp]%1$c%2$cmov rsi, 1537%1$c%2$cmov rdx, 420%1$c%2$ccall _open%1$c%2$cmov dword [rsp + 20], eax%1$c%2$cmov edi, dword [rsp + 20]%1$c%2$clea rsi, [rel a]%1$c%2$cmov rdx, 10%1$c%2$cmov rcx, 9%1$c%2$cmov r8, 34%1$c%2$cmov r9d, dword [rsp + 16]%1$c%2$clea rax, [rel a]%1$c%2$cmov [rsp], rax%1$c%2$ccall _dprintf%1$c%2$cmov edi, dword [rsp + 20]%1$c%2$ccall _close%1$c%2$clea rdi, [rsp + 24]%1$c%2$clea rsi, [rel fmtt]%1$c%2$cmov edx, dword [rsp + 16]%1$c%2$ccall _sprintf%1$c%2$clea rdi, [rsp + 24]%1$c%2$ccall _system%1$c%2$clea rdi, [rsp + 24]%1$c%2$cmov rsi, 0%1$c%2$cmov rdx, 25%1$c%2$ccall _memset%1$c%2$clea rdi, [rsp + 24]%1$c%2$clea rsi, [rel fmttt]%1$c%2$cmov edx, dword [rsp + 16]%1$c%2$ccall _sprintf%1$c%2$ccmp dword [rsp + 16], 0%1$c%2$cjg exec%1$c%1$cfinish:%1$c%2$cmov rax, 0%1$c%2$cadd rsp, 128%1$c%2$cpop rbp%1$c%2$cret%1$c%1$cexec:%1$c%2$clea rdi, [rsp + 24]%1$c%2$ccall _system%1$c%2$cjmp finish%1$c%1$cdecr:%1$c%2$cmov eax, dword [rsp + 16]%1$c%2$cdec eax%1$c%2$cmov dword [rsp + 16], eax%1$c%2$cjmp back%1$c%1$csection .data%1$c%2$cd db %3$cSully_5.s%3$c, 0%1$c%2$cfmt db %3$cSully_%%d.s%3$c, 0%1$c%2$cfmtt db %3$cnasm -f macho64 Sully_%%1$d.s && gcc -o Sully_%%1$d Sully_%%1$d.o && rm Sully_%%1$d.o%3$c, 0%1$c%2$cfmttt db %3$c./Sully_%%1$d%3$c, 0%1$c%2$ca db %3$c%5$s%3$c, 0%1$c%2$ci dd %4$d%1$c", 0
	i dd 5
