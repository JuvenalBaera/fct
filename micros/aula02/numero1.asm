; multi-segment executable file template.

data segment
    ; add your data here!
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
    
    mov ax, 3
    mov bx, 8
    
    call subtrair
            
    lea dx, pkey
    mov ah, 9
    int 21h        ; output string at ds:dx
    
    ; wait for any key....    
    mov ah, 1
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h      
    
    
    ;##########################################
    ; Name: subtrair
    ; Par: ax, bx
    ; out: ax
    ;##########################################
    
    subtrair proc
        sub ax, bx
        ret
    subtrair endp 
ends

end start ; set entry point and stop the assembler.
