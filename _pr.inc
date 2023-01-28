; I guess I can reserve memory in the .inc files
section .bss
    digitSpace resb 100
    digitSpacePos resb 8
    printSpace resb 8

; exit
%macro exit 0
    mov rax, 60
    mov rdi, 0
    syscall
%endmacro

;print
%macro _print 1
    mov rax, %1                 ; rax 0xnothing -> 0x40402a %1
    mov [printSpace], rax       ; print space holds the 3 byte address of rax
    mov rbx, 0                  ; set rbx to 0 to stop the loop
%%_printloop:
    mov cl, [rax]               ; move contents of rax to the lower byte of rcx
    cmp cl, 0                   ; compare that byte with 0
    je %%endPrintLoop
    inc rbx                     ;using rbx as our char count
    inc rax                     ;rax points to next character.   
    jmp %%_printloop
%%endPrintLoop:
    mov rax, 1
    mov rdi, 1
    mov rsi, [printSpace]
    mov rdx, rbx
    syscall
%endmacro

;print1
