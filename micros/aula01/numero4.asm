; multi-segment executable file template.

data segment
    ; add your data here!
    elements equ 15            
    array db 1,2,3,4,5,85,7,8,109,8,7,6,5,23,128
    Res db ?
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
            
    lea dx, pkey
    mov ah, 9
    int 21h        ; output string at ds:dx
            
    mov si, 0
    mov al, array[0]
    
    for:
        cmp si, elements       
        jz end_for               ; fim do array?
        cmp al, array[si]        
        ja if                    
            mov al, array[si]    ; em caso de for maior
            mov bx, si
        if:
        inc si
        jmp for
    end_for: 
    mov Res, bl       
    
    ; wait for any key....    
    mov ah, 1
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
ends

end start ; set entry point and stop the assembler.
