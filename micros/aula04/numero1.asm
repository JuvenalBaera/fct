; multi-segment executable file template.

data segment
    ; add your data here!
    strinput db 20 dup(?)
    num1 db 0
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
    mov bx, 1
    xor di, di        
    
    call scanf
                
    mov num1, bl
    
    call newline
    
    mov ax, 01h
    mov si, offset num1
    call print
    
;    mov si, offset numinput
;    mov ah, 09h
;    int 21h
;    call print
    
    
    mov ax, 4c00h ; exit to operating system.
    int 21h
    
    
    
    
    
    ;#######################################
    ; newLine - Salta para linha seguinte
    ;
    newLine proc
        push ax
        push dx
        mov ah, 02h
        mov dl, 0dh
        int 21h    
        mov dl, 0ah
        int 21h
        pop dx
        pop ax
    ret
    newLine endp
    
    
    ;####################################
    ; co - caracter ouput
    ;
    co proc
        push ax
        push dx
        mov ah, 02h
        mov dl, al
        int 21h
        pop dx
        pop ax
    ret
    co endp            
    
    
    ;##################################
    ; ci - char input
    ;
    ci proc      
        mov ah, 07h
        int 21h
        mov ah, 0
    ret
    ci endp
    
    
    ;#####################################
    ; scanf
    ;
    scanf proc  
       push ax
       mov cx, ax ; for loop
       
       cmp bx, 0
       jnz scanN
            readC:
                call ci
                call co
                
                cmp al, 0dh ; se for ENTER sai
                jz fim
                    mov strinput[di], al
                    inc di
                    dec cx
                    cmp cx, 0
                    jnz readC 
       scanN:                   ; for scan number (0 - 255)
       cmp bx, 01h
       jnz fim
       xor bx, bx
       readN:  
       xor ax, ax
       cmp cx, 0
       jz fim   
            call ci
            call co
            
            cmp al, '0'
            jb nNum
            cmp al, '9'
            jg nNum       
               sub al, '0'
               push ax       ; guardar ax
               mov al, bl    ; mandar em ax o que já estava em bl
               mov bl, 10
               mul bl        ; multiplicar al por 10 ou ((al=bl) x 10)
               
               mov bl, al    ; copiar para bl a multiplcacao anterior
               pop ax        ; restore ax
               jc nNum
               add bl, al    ; adiciona bl com o valor digitado
               jc nNum
                    dec cx
                    inc di
                    jmp readN
       nNum:
            mov bx, -1
       fim:           
       pop ax  
    ret
    scanf endp
    
    
    ;####################################
    ; name: print (string output)
    ;
    print proc
        xor bh, bh
        push bx   
        
        cmp ax, 0
        jnz p1
            L1:
            mov al, byte ptr[si]
            or al, al
            jz fimptrstr
            cmp bl, 0
                jz fim1
            cmp bl, 01h
            jnz if1
                cmp al, 'a'
                jnae fim
                cmp al, 'z'
                jnb fim1      
                sub al, 20h
            if1:
            cmp bl, 02h
            jnz fim
                cmp al, 'A'
                jnae fim1
                cmp al, 'Z'
                jnb fim1
                add al, 20h
            fim1:
                call co
                inc si
                jmp L1
            fimptrstr:
            pop bx
            cmp bx, 04h
                jnz fim1
                call newLine
            fim2:
            jmp fimP
        p1:
        cmp ax, 01h
        jnz fim
        
        fimP:         
            mov dx, 0
            mov al, byte ptr[si]
            L2:
            or al, al
            jz fimNumP
                mov bx, 10
                div bx
                
                push ax
                mov ax, dx
                add al, '0'
                
                call co
                pop ax
                ;mov ax, dx
                jmp L2
            fimNumP:
    ret
    print endp
ends

end start ; set entry point and stop the assembler.
