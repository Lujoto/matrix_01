extern printf

section .data
    number dq 12
    fmt     db "the sum from 0 to %ld is %ld",10,0
section .bss
section .text
    global main
main:
    push rbp
    mov  rbp, rsp

    mov rax, 0
    mov rbx, 0 ; rbx will be the counter




loopf:
    add rax, rbx
    inc rbx
    cmp rbx, [number]
    jle loopf

    mov rdi, fmt
    mov rsi, [number]
    mov rdx, rax 
    mov rax, 0
    call printf

   
    mov rsp, rbp 
    pop rbp
   
    mov rax, 60
    mov rdi, 0
    syscall
    ret