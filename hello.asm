section .data
    text db  "hello, world",0 
section .bss
section .text
    global main
main:
    ;mov rax, 1
    ;mov rdi, 1
    ;mov rsi, text 
    ;mov rdx, 13
    ;syscall
    call print_hello
    mov rax, 60
    mov rdi, 0
    syscall

print_hello:
    mov rax, 1
    mov rdi, 1
    mov rsi, text
    mov rdx, 13
    syscall
    ret

