
rc4.o:	file format Mach-O 64-bit x86-64

Disassembly of section __TEXT,__text:
_RC4:
       0:	55 	push	rbp
       1:	48 89 e5 	mov	rbp, rsp
       4:	48 81 ec 30 01 00 00 	sub	rsp, 304
       b:	48 8d 85 f0 fe ff ff 	lea	rax, [rbp - 272]
      12:	48 8b 0d 00 00 00 00 	mov	rcx, qword ptr [rip]
      19:	48 8b 09 	mov	rcx, qword ptr [rcx]
      1c:	48 89 4d f8 	mov	qword ptr [rbp - 8], rcx
      20:	48 89 bd e8 fe ff ff 	mov	qword ptr [rbp - 280], rdi
      27:	48 89 b5 e0 fe ff ff 	mov	qword ptr [rbp - 288], rsi
      2e:	89 95 dc fe ff ff 	mov	dword ptr [rbp - 292], edx
      34:	48 8b bd e8 fe ff ff 	mov	rdi, qword ptr [rbp - 280]
      3b:	48 89 c6 	mov	rsi, rax
      3e:	e8 00 00 00 00 	call	0 <_RC4+0x43>  

      43:	48 8d bd f0 fe ff ff 	lea	rdi, [rbp - 272]
      4a:	48 8b b5 e0 fe ff ff 	mov	rsi, qword ptr [rbp - 288]
      51:	8b 95 dc fe ff ff 	mov	edx, dword ptr [rbp - 292]
      57:	e8 00 00 00 00 	call	0 <_RC4+0x5c>

      5c:	48 8b 05 00 00 00 00 	mov	rax, qword ptr [rip]
      63:	48 8b 00 	mov	rax, qword ptr [rax]
      66:	48 8b 4d f8 	mov	rcx, qword ptr [rbp - 8]
      6a:	48 39 c8 	cmp	rax, rcx
      6d:	0f 85 09 00 00 00 	jne	9 <_RC4+0x7c>
      73:	48 81 c4 30 01 00 00 	add	rsp, 304
      7a:	5d 	pop	rbp
      7b:	c3 	ret
      7c:	e8 00 00 00 00 	call	0 <_RC4+0x81>
      81:	0f 0b 	ud2
      83:	66 2e 0f 1f 84 00 00 00 00 00 	nop	word ptr cs:[rax + rax]
      8d:	0f 1f 00 	nop	dword ptr [rax]

_KSA:
      90:	55 	push	rbp
      91:	48 89 e5 	mov	rbp, rsp
      94:	48 83 ec 30 	sub	rsp, 48
      98:	48 89 7d f8 	mov	qword ptr [rbp - 8], rdi
      9c:	48 89 75 f0 	mov	qword ptr [rbp - 16], rsi
      a0:	48 8b 7d f8 	mov	rdi, qword ptr [rbp - 8]
      a4:	e8 00 00 00 00 	call	0 <_KSA+0x19>


      a9:	89 c1 	mov	ecx, eax
      ab:	89 4d e8 	mov	dword ptr [rbp - 24], ecx

      
      ae:	c7 45 e4 00 00 00 00 	mov	dword ptr [rbp - 28], 0
      b5:	81 7d e4 ff 00 00 00 	cmp	dword ptr [rbp - 28], 255
      bc:	0f 8d 1e 00 00 00 	jge	30 <_KSA+0x50>
      c2:	8b 45 e4 	mov	eax, dword ptr [rbp - 28]
      c5:	88 c1 	mov	cl, al
      c7:	48 8b 55 f0 	mov	rdx, qword ptr [rbp - 16]
      cb:	48 63 75 e4 	movsxd	rsi, dword ptr [rbp - 28]
      cf:	88 0c 32 	mov	byte ptr [rdx + rsi], cl
      d2:	8b 45 e4 	mov	eax, dword ptr [rbp - 28]
      d5:	83 c0 01 	add	eax, 1
      d8:	89 45 e4 	mov	dword ptr [rbp - 28], eax
      db:	e9 d5 ff ff ff 	jmp	-43 <_KSA+0x25>
      e0:	c7 45 ec 00 00 00 00 	mov	dword ptr [rbp - 20], 0
      e7:	c7 45 e0 00 00 00 00 	mov	dword ptr [rbp - 32], 0
      ee:	81 7d e0 ff 00 00 00 	cmp	dword ptr [rbp - 32], 255
      f5:	0f 8d 6e 00 00 00 	jge	110 <_KSA+0xd9>
      fb:	8b 45 ec 	mov	eax, dword ptr [rbp - 20]
      fe:	48 8b 4d f0 	mov	rcx, qword ptr [rbp - 16]
     102:	48 63 55 e0 	movsxd	rdx, dword ptr [rbp - 32]
     106:	0f b6 34 11 	movzx	esi, byte ptr [rcx + rdx]
     10a:	01 f0 	add	eax, esi
     10c:	48 8b 4d f8 	mov	rcx, qword ptr [rbp - 8]
     110:	8b 75 e0 	mov	esi, dword ptr [rbp - 32]
     113:	89 45 dc 	mov	dword ptr [rbp - 36], eax
     116:	89 f0 	mov	eax, esi
     118:	99 	cdq
     119:	f7 7d e8 	idiv	dword ptr [rbp - 24]
     11c:	48 63 fa 	movsxd	rdi, edx
     11f:	0f be 14 39 	movsx	edx, byte ptr [rcx + rdi]
     123:	8b 75 dc 	mov	esi, dword ptr [rbp - 36]
     126:	01 d6 	add	esi, edx
     128:	89 f0 	mov	eax, esi
     12a:	99 	cdq
     12b:	be ff 00 00 00 	mov	esi, 255
     130:	f7 fe 	idiv	esi
     132:	89 55 ec 	mov	dword ptr [rbp - 20], edx
     135:	48 8b 4d f0 	mov	rcx, qword ptr [rbp - 16]
     139:	48 63 7d e0 	movsxd	rdi, dword ptr [rbp - 32]
     13d:	48 01 f9 	add	rcx, rdi
     140:	48 8b 7d f0 	mov	rdi, qword ptr [rbp - 16]
     144:	4c 63 45 ec 	movsxd	r8, dword ptr [rbp - 20]
     148:	4c 01 c7 	add	rdi, r8
     14b:	48 89 7d d0 	mov	qword ptr [rbp - 48], rdi
     14f:	48 89 cf 	mov	rdi, rcx
     152:	48 8b 75 d0 	mov	rsi, qword ptr [rbp - 48]
     156:	e8 00 00 00 00 	call	0 <_KSA+0xcb>
     15b:	8b 45 e0 	mov	eax, dword ptr [rbp - 32]
     15e:	83 c0 01 	add	eax, 1
     161:	89 45 e0 	mov	dword ptr [rbp - 32], eax
     164:	e9 85 ff ff ff 	jmp	-123 <_KSA+0x5e>
     
     169:	48 83 c4 30 	add	rsp, 48
     16d:	5d 	pop	rbp
     16e:	c3 	ret
     16f:	90 	nop

_PRGA:
     170:	55 	push	rbp
     171:	48 89 e5 	mov	rbp, rsp
     174:	48 83 ec 30 	sub	rsp, 48
     178:	48 89 7d f8 	mov	qword ptr [rbp - 8], rdi
     17c:	48 89 75 f0 	mov	qword ptr [rbp - 16], rsi
     180:	89 55 ec 	mov	dword ptr [rbp - 20], edx
     183:	c7 45 e8 00 00 00 00 	mov	dword ptr [rbp - 24], 0
     18a:	c7 45 e4 00 00 00 00 	mov	dword ptr [rbp - 28], 0
     191:	c7 45 e0 00 00 00 00 	mov	dword ptr [rbp - 32], 0
     198:	48 c7 45 d8 00 00 00 00 	mov	qword ptr [rbp - 40], 0
     1a0:	48 8b 45 d8 	mov	rax, qword ptr [rbp - 40]
     1a4:	8b 4d ec 	mov	ecx, dword ptr [rbp - 20]
     1a7:	89 ca 	mov	edx, ecx
     1a9:	48 39 d0 	cmp	rax, rdx
     1ac:	0f 83 b7 00 00 00 	jae	183 <_PRGA+0xf9>
     1b2:	8b 45 e8 	mov	eax, dword ptr [rbp - 24]
     1b5:	83 c0 01 	add	eax, 1
     1b8:	99 	cdq
     1b9:	b9 ff 00 00 00 	mov	ecx, 255
     1be:	f7 f9 	idiv	ecx
     1c0:	89 55 e8 	mov	dword ptr [rbp - 24], edx
     1c3:	8b 55 e4 	mov	edx, dword ptr [rbp - 28]
     1c6:	48 8b 75 f8 	mov	rsi, qword ptr [rbp - 8]
     1ca:	48 63 7d e8 	movsxd	rdi, dword ptr [rbp - 24]
     1ce:	44 0f b6 04 3e 	movzx	r8d, byte ptr [rsi + rdi]
     1d3:	44 01 c2 	add	edx, r8d
     1d6:	89 d0 	mov	eax, edx
     1d8:	99 	cdq
     1d9:	f7 f9 	idiv	ecx
     1db:	89 55 e4 	mov	dword ptr [rbp - 28], edx
     1de:	48 8b 75 f8 	mov	rsi, qword ptr [rbp - 8]
     1e2:	48 63 7d e8 	movsxd	rdi, dword ptr [rbp - 24]
     1e6:	48 01 fe 	add	rsi, rdi
     1e9:	48 8b 7d f8 	mov	rdi, qword ptr [rbp - 8]
     1ed:	4c 63 4d e4 	movsxd	r9, dword ptr [rbp - 28]
     1f1:	4c 01 cf 	add	rdi, r9
     1f4:	48 89 7d d0 	mov	qword ptr [rbp - 48], rdi
     1f8:	48 89 f7 	mov	rdi, rsi
     1fb:	48 8b 75 d0 	mov	rsi, qword ptr [rbp - 48]
     1ff:	e8 00 00 00 00 	call	0 <_PRGA+0x94>
     204:	48 8b 75 f8 	mov	rsi, qword ptr [rbp - 8]
     208:	48 8b 7d f8 	mov	rdi, qword ptr [rbp - 8]
     20c:	4c 63 4d e8 	movsxd	r9, dword ptr [rbp - 24]
     210:	42 0f b6 0c 0f 	movzx	ecx, byte ptr [rdi + r9]
     215:	48 8b 7d f8 	mov	rdi, qword ptr [rbp - 8]
     219:	4c 63 4d e4 	movsxd	r9, dword ptr [rbp - 28]
     21d:	42 0f b6 14 0f 	movzx	edx, byte ptr [rdi + r9]
     222:	01 d1 	add	ecx, edx
     224:	89 c8 	mov	eax, ecx
     226:	99 	cdq
     227:	b9 ff 00 00 00 	mov	ecx, 255
     22c:	f7 f9 	idiv	ecx
     22e:	48 63 fa 	movsxd	rdi, edx
     231:	0f b6 0c 3e 	movzx	ecx, byte ptr [rsi + rdi]
     235:	89 4d e0 	mov	dword ptr [rbp - 32], ecx
     238:	8b 4d e0 	mov	ecx, dword ptr [rbp - 32]
     23b:	48 8b 75 f0 	mov	rsi, qword ptr [rbp - 16]
     23f:	48 8b 7d d8 	mov	rdi, qword ptr [rbp - 40]
     243:	0f b6 14 3e 	movzx	edx, byte ptr [rsi + rdi]
     247:	31 d1 	xor	ecx, edx
     249:	41 88 ca 	mov	r10b, cl
     24c:	48 8b 75 f0 	mov	rsi, qword ptr [rbp - 16]
     250:	48 8b 7d d8 	mov	rdi, qword ptr [rbp - 40]
     254:	44 88 14 3e 	mov	byte ptr [rsi + rdi], r10b
     258:	48 8b 45 d8 	mov	rax, qword ptr [rbp - 40]
     25c:	48 83 c0 01 	add	rax, 1
     260:	48 89 45 d8 	mov	qword ptr [rbp - 40], rax
     264:	e9 37 ff ff ff 	jmp	-201 <_PRGA+0x30>
     269:	48 83 c4 30 	add	rsp, 48
     26d:	5d 	pop	rbp
     26e:	c3 	ret
     26f:	90 	nop

_swap:
     270:	55 	push	rbp
     271:	48 89 e5 	mov	rbp, rsp
     274:	48 89 7d f8 	mov	qword ptr [rbp - 8], rdi
     278:	48 89 75 f0 	mov	qword ptr [rbp - 16], rsi
     27c:	48 8b 75 f8 	mov	rsi, qword ptr [rbp - 8]
     280:	0f b6 06 	movzx	eax, byte ptr [rsi]
     283:	89 45 ec 	mov	dword ptr [rbp - 20], eax
     286:	48 8b 75 f8 	mov	rsi, qword ptr [rbp - 8]
     28a:	8a 0e 	mov	cl, byte ptr [rsi]
     28c:	48 8b 75 f0 	mov	rsi, qword ptr [rbp - 16]
     290:	88 0e 	mov	byte ptr [rsi], cl
     292:	8b 45 ec 	mov	eax, dword ptr [rbp - 20]
     295:	88 c1 	mov	cl, al
     297:	48 8b 75 f8 	mov	rsi, qword ptr [rbp - 8]
     29b:	88 0e 	mov	byte ptr [rsi], cl
     29d:	5d 	pop	rbp
     29e:	c3 	ret
