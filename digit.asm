section .data
    digit db 0,10; digit is defined with 2 bytes: 0, 10
; since we only load the lower byte of the rax reg into digit, it only overwrites the
; first byte and does not affect the newline character. 
section .bss
section .text
    global main
main:
    push 4
    push 9
    push 3
    pop rax
    call _printRAXdigit
    pop rax
    call _printRAXdigit
    pop rax
    call _printRAXdigit

    call ep

_printRAXdigit:
    add rax, 48; 48 ascii: "0". if you change this to 49, you will print
    ; the ascii code for 1+what you pushed
    ; to the stack. So when you push "4", you're incrementing a register. 
    ; You have to tell the rax register where to start in the ascii table. 
    ; You aren't pushing "ints" to the stack. You're talking to the register using
    ; ascii codes. The integers 0-9 happen to be in the range 48-57 in the ascii table. 

    mov [digit], al; "al" is the low 8-bit regeister section of the rax register. 
    mov rax, 1
    mov rdi, 1
    mov rsi, digit
    mov rdx, 2; digit 0-9 + newline character = 2 bytes
    syscall
    ret

ep:
    mov rax, 60
    mov rdi, 0
    syscall
    ret

