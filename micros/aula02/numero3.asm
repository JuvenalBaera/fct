; multi-segment executable file template.

data segment
    ; add your data here!
    num1 dw 0ffffh
    num2 dw 02h
    res1 dw ?
    res2 dw ?
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
    
    mov ax, 0
    mov dx, 0
    mov bx, num1
    mov cx, num2
    
    call multiplicar
                    
                    
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
    soma proc
        add ax, bx
        jnc fim
            inc dx
        fim: ret
    soma endp
                
                
    ;##########################################
    ; Name: multipliacr
    ;##########################################
    
    multiplicar proc
        cmp cx, bx
        jna loop_for
            mov cx, bx
            mov bx, num1
        loop_for:
        cmp cx, 0
        je end_for
            call soma
            dec cx
            jmp loop_for
        end_for:
        mov res1, dx
        mov res2, ax
    multiplicar endp 
ends

end start ; set entry point and stop the assembler.
