; input.asm

section .data
    msg1        db     "Enter your name",0
    len1        equ    $-msg1-1
    aloc        equ      16
    NL          db      0xa ;ascii code for a new line

section .bss
    name        resb    aloc

section .text
    global main
main:
    call print_prompt
    call print_newline
    call get_name
    call print_name
    call ep

ep:
    mov rax, 60
    mov rdi, 0
    syscall
    ret

get_name:
    mov rax, 0 ;input
    mov rdi, 0 ;to std in
    mov rsi, name
    mov rdx, aloc
    syscall
    ret

print_name:
    mov rax, 1
    mov rdi, 1
    mov rsi, name
    mov rdx, aloc
    syscall
    ret

print_prompt:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg1
    mov rdx, len1
    syscall
    ret

print_newline:
    mov rax, 1
    mov rdi, 1
    mov rsi, NL
    mov rdx, 1
    syscall
    ret