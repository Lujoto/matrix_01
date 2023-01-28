 ; move.asm
%include "_pr.inc"

section .data
    bNum db 123
    wNum dw 12345
    dNum dd 1234567890
    qNum1 dq 1234567890123456789
    qNum2 dq 123456
    qNum3 dq 3.14

section .bss

rash resb 64

section .text
    global main
main:

push   rbp
mov    rbp, rsp ; these two steps happen prior to the breakpoint in main for some reason


mov rax, -1     ; fill rax with 1s
mov [rash], rax
mov rcx, rash

mov al, byte [bNum]
mov [rash], rax
mov rcx, rash 

xor rax, rax
mov al, byte [bNum]

mov rax, -1
mov eax, dword [dNum] ;this clears the upper 32 bits of rax, where the bNum does not.
xor rcx, rcx
mov [rash], rax
mov rcx, rash

exit

