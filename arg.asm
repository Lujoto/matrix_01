;%include "linux64.inc"
%include "_syscodes.inc"
%include "_pr.inc"



section .data
    newline db 10,0
    buf     db "===================",0
    string1 db "this 0is a string",0
    number1 db 49
section .text
    global main 
main:
    
    
    _print buf 
    _print newline


    exit