section .data

section .bss
    digitSpace resb 100 ; reserve 100 bytes.
    digitSpacePos resb 8 ; reserve 8 bytes for the position

section .text
    global main
main:
mov rax, 123
call _printRAX
call ep
ep:
    mov rax, 60
    mov rdi, 0
    syscall
    ret
_printRAX:
    mov rcx, digitSpace ; move digitSpace into rcx
    mov rbx, 10 ; add a new line to rbx
    mov [rcx], rbx ; move rbx to the location of rcx 
    inc rcx ; rcx  +1
    mov [digitSpacePos], rcx ; store rcx in the position memory
_printRAXLoop:
    mov rdx, 0 ;
    mov rbx, 10 ; new line into rbx
    div rbx
    push rax
    add rax, 48 ;convert to digit character
    mov rcx, [digitSpacePos]
    ; adding comment
