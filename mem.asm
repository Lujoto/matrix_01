extern printf

section .data
    bNum    db  123
    wNum    dw  12345
    warray  times   5 dw 0  ; array of 5 words. 

    dNum    dd      12345
    qNum1   dq      12345
    text1   db      "abc",0
    qNum2   dq      3.141592654
    text2   db      "cde",0

section .bss

    bvar    resb    1
    dvar    resd    1
    wvar    resw    10
    qvar    resq    3



section .text
    global main
main:
    push rbp
    mov rbp, rsp 

    lea  rax, [bNum] ; load address of bNum in rax
    mov  rax, bNum   ; this has the same result as the line above. 
    mov  rax, [bNum] ; load the contents of bNum to the 64bit register rax
  
    mov [bvar], rax  
    lea rax, [bvar]  
    lea rax, [wNum]
    mov rax, [wNum]
    lea rax, [text1]
    mov rax, text1
    mov rax, text1 + 1
    
    
    call ep

ep:
   mov rax, 60
   mov rdi, 0
   syscall