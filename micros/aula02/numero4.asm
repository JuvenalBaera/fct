; multi-segment executable file template.

data segment
    ; add your data here!
    num1 dw 4
    num2 dw 6
    quociente dw ?
    resto dw ?
    pkey db "press any key...$"
ends

stack segment
    dw   128  dup(0)
ends

code segment
start:
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax

    ; add your code here 
    
    mov ax, num1
    mov bx, num2
    
    call dividir
                    
                    
    lea dx, pkey
    mov ah, 9
    int 21h        ; output string at ds:dx
    
    ; wait for any key....    
    mov ah, 1
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h      
    
    ; #########################################
    ; soma
    ;
    ;##########################################
    subtrair proc
        sub ax, bx
        ret
    subtrair endp
                
                
    ;##########################################
    ; Name: multipliacr
    ;##########################################
    
    dividir proc
        cmp bx, 0           
        jz end_for          
        loop_for:
        cmp ax, bx
        jb end_for
            call subtrair
            inc quociente
            jmp loop_for
        end_for:
        mov resto, ax
    dividir endp 
ends

end start ; set entry point and stop the assembler.
