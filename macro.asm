%macro exit 0
    mov rax, 60
    mov rdi, 0
    syscall
%endmacro



section .data
    msg db "hey",0,10

section .bss
section .text
   global main
main:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg
    mov rdx, 5   
    syscall

exit