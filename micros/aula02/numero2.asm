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
    
    mov ax, 0ffffh
    mov bx, 1
    mov dx, 0
    
    call soma
            
    lea dx, pkey
    mov ah, 9
    int 21h        ; output string at ds:dx
    
    ; wait for any key....    
    mov ah, 1
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h      
    
    
    ;##########################################
    ; Name: soma
    ; Par: ax, bx
    ; out: ax
    ;##########################################
    
    soma proc
        add ax, bx
        jnc fim
          inc dx
        fim: ret
    soma endp 
ends

end start ; set entry point and stop the assembler.
