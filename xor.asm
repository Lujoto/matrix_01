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

section .text
    global main
main:

push   rbp
mov    rbp, rsp

mov rax, -1     ; fill rax with 1s
mov al, byte [bNum]
xor rax, rax

exit

