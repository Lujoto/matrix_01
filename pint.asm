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

_printRAX:
    mov rcx, digitSpace      ;move digitSpace into rcx
    mov rbx, 10              ;add a new line to rbx
    mov [rcx], rbx           ;move rbx to the location of rcx 
    inc rcx                  ;rcx  +1
    mov [digitSpacePos], rcx ;store rcx in the position memory
_printRAXLoop:
    mov rdx, 0 ;
    mov rbx, 10 ; new line into rbx
    div rbx
    push rax
    add rdx, 48 ;convert to digit character
    mov rcx, [digitSpacePos]
    mov [rcx], dl ; lower 8 bytes of rdX
    inc rcx
    mov [digitSpacePos], rcx

    pop rax
    cmp rax, 0
    jne _printRAXLoop
    
_printRAXLoop2:
    mov rcx, [digitSpacePos]
    mov rax, 1
    mov rdi, 1
    mov rsi, rcx
    mov rdx, 1
    syscall
    
    mov rcx, [digitSpacePos]
    dec rcx
    mov [digitSpacePos], rcx

    cmp rcx, digitSpace
    jge _printRAXLoop2
    ret
    
ep:
    mov rax, 60
    mov rdi, 0
    syscall
    ret

; 123 / 10 = 12 R 3
    ; store 3
; 12 / 10 = 1 R 2
    ; store 2
; 1 / 10  = 0 R 1
    ; store 1