section .data
    msg db "first",0,10
    msg1 db "secon",0,10
    msg2 db "third",0,10

section .bss
section .text
    global main
main:

mov rax, msg
call _ps
call ep

_ps:
    push rax
    mov rax, 1
    mov rdi, 1
    pop rsi
    syscall
    ret
ep:
    mov rax, 60
    mov rdi, 0
    syscall
    ret

; NOTES about this program. This is why you must mov a length value into rdx
; or loop to find null terminations. 
; 
; in the .data section, three contiguous addresses are used to store msg, msg1,
; and msg2. 
;
; when we use "mov rax, msg" and then call _ps, which immediately pushes rax to 
; the stack, I found that it moved not only msg, but also the subsequent two 
; strings declared in .data to rax.
;
; when popping the stack, rsi was loaded with all three strings, and the 
; subsequent syscall indeed printed all three strings.
;
; you must use rdx to tell the system how many (characters?) to load into rsi