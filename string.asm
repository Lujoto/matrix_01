; subroutine to calc the length of strings
section .data
    msg  db  "Hey",10,0
    msg2 db  "whats that noise",10,0

section .bss
section .text
    global main
main:

mov rax, msg
call _print
mov rax, msg2
call _print
call ep


    ;input: rax as pointer to string
    ;output: print string at rax
_print:
    push rax        ; since there is no "ret" statement at the end of _print, 
    mov rbx, 0      ; this function will continue into _printloop. 
                    ; use rbx to count the length of the string
                    ; 
_printloop:
    inc rax         ; increment rax to read next character
    inc rbx         ; increment rbx to account for the number of characters

    mov cl, [rax]  ; move into cl (8-bit equivalent of rcx) the contents? of rax
    cmp cl, 0
    jne _printloop ; if not equal, jump to _printloop
    
    mov rax, 1
    mov rdi, 1
    pop rsi
    mov rdx, rbx
    syscall
    ret

ep:
    mov rax, 60
    mov rdi, 0
    syscall
    ret

