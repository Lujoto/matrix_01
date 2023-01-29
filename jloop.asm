;jump loop
extern printf
section .data
    number  dq      67
    fmt     db  "the sum from 0 to %ld is %ld",10,0

section .bss
section .text
    global main
main:
    push rbp
    mov  rbp, rsp 

    mov rax, 0
    mov rbx, 0
    

jloop:
    add rax, rbx
    inc rbx
    cmp rbx, [number]
    jle jloop

; printf pulls 3 arguments from rdi, rsi, and rcx, in that order. first the format string
; then each argument in sequence. It was way too difficult to find the order in which
; printf pulls from registers. 


    mov rdi, fmt
    mov rsi, [number]
    mov rdx, rax
    mov rax, 0
    call printf
    
    mov rsp, rbp
    pop rbp
    call ep   
    ret



ep:
    mov rax, 60
    mov rdi, 0
    syscall
    ret