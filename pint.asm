section .data

section .bss
    digitSpace resb 8 ;reserve 100 bytes for the actual digit(s)?
    digitSpacePos resb 8 ; reserve 8 bytes for the position
    digitTest resb 8 ; 
section .text
    global main
main:
    mov rax, 1234567
    call _printRAX
    call ep

_printRAX:
    mov rcx, digitSpace      ;move digitSpace into rcx (this changes the 7 digit value stored in rcx)
   ; after doing the above, we can now use x/##b $rcx to view the contents at
   ; rcx. 
   ; when we reserve 16 bytes, and examine 32b (x/32b) at $rcx, we see the 16 bytes of 
   ; digitSpace, and the next memory in sequence is the 8 bytes of 
   ; memory of digitSpacePos. 
   ; the resb command seems to reserve contiguous memory. 
   ;  
    mov rbx, 10             ; load 10 into rbx 
    mov [rcx], rbx           ;move rbx to the location of rcx 
    ;mov [rcx], 10  ; can't do this, throws "Operartion size not defined" 
    inc rcx                  ;rcx  +1
    ; this increment takes us 

    mov [digitSpacePos], rcx ;store rcx in the position memory
_printRAXLoop:
; divide rax by 10, acquire the remainder, store both. 
; push the result of rax / 10 to the stack. 
; remainder is stored in rdx, convert it to an integer character by adding 48

    mov rdx, 0               ; mov 0 into rdx, otherwise the rax + rdx will act as 128b
    mov rbx, 10              ; need to divide by 10 each time to acquire remainder
    div rbx                  ; do the division. rax / rbx = rax / 10 
    ;push rax                 ; push the result of the division (w/out remainder)
    add rdx, 48              ; convert the remainder to digit character
;  
    ;mov rcx, [digitSpacePos] ; safety mechanism? rcx is already the address of digit
                              ; space pos; behaves the same when ommited.
                              ; contents of position into rcx
    mov [rcx], dl             ; lower 8 bytes of rdx (the digit) into the address of rcx
    inc rcx                   ; increment rcx
    mov [digitSpacePos], rcx  ; mov the incremented contents of rcx to the contents
                              ; of pos   

    ;pop rax                  ; input the result of the division (top of stack) into rax
    cmp rax, 0               ; compare rax to 0
    jne _printRAXLoop        ; if compare flag? is 0, jump to beginning of this func
    
_printRAXLoop2:
; here, we handle the printing to the console. Put the address of the position space
; into rcx. rax 1, rdi 1 for write to stdout. 
; mov rcx to rsi. 
    ;mov rcx, [digitSpacePos] ; this must just be for safey like in _printRAXLoop
                                ; ommitting has no effect on ouput.
    mov rax, 1               ;
    mov rdi, 1               ;
    mov rsi, rcx             ;
    mov rdx, 1               ; 
    syscall                  ;

; here, we decrement the Position value. in order to do that, we must move the position
; value into a register (rcx), use the dec operation on rcx, then move that value back
; to the position address 
    mov rcx, [digitSpacePos] ; moving position address into rcx
    dec rcx                  ; decrementing that address
    mov [digitSpacePos], rcx ; moving that address to the position address

    cmp rcx, digitSpace      ;
    jge _printRAXLoop2       ;
    ret                      ;
    
ep:
    mov rax, 60              ;
    mov rdi, 0               ;
    syscall                  ;
    ret

; 123 / 10 = 12 R 3
    ; store 3
; 12 / 10 = 1 R 2
    ; store 2
; 1 / 10  = 0 R 1
    ; store 1