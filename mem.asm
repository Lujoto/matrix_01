section .data

section .bss

    mem_1 resb 8
    mem_2 resb 16


section .text
    global main

main:

mov rax, 0
mov rdx, 0
mov rcx, mem_1
;mov rcx, [mem_1]; this causes rcx to hold 0, and be inaccessible
mov [mem_1], rcx
mov rcx, [mem_2] ; does this wipe the contents of mem_1 or mov the address of rcx? 
; [dereference]. this moves whatever mem_2 points to (contents) into the rcx register. 
; after this operation, rcx was inaccessible and 0x0 address.



call ep

ep:
mov rax, 60
mov rdi, 0
syscall
ret