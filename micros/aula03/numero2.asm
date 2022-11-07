; multi-segment executable file template.

data segment
    ; add your data here!
    strola db "Digite uma string: ", 0dh, 0ah, 0
    strpri db "String digitado: ", 0dh, 0ah, 0
    strinput db 20 dup(?)
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
    
    mov si, offset strola
    call print
    
    mov ax, 20
    xor di, di
    call scanf
    
    call newLine
    
    mov si, offset strpri
    call print
    
    mov si, offset strinput
    call print
    
    
    mov ax, 4c00h ; exit to operating system.
    int 21h
    
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
                                         
    ;####################################
    ; name: print (string output)
    ;
    print proc
        L1:
        mov al, byte ptr[si]
        or al, al
        jz fimptrstr
            call co
            inc si
            jmp L1
        fimptrstr:    
    ret
    print endp
    
    ;#####################################
    ; scanf
    ;
    scanf proc
        push ax
        mov cx, ax
        readC:
            mov ah, 07h ; ler char
            int 21h
            call co
            
            cmp al, 0dh ; se for ENTER sai
            jz endRead
                mov strinput[di], al
                inc di
                dec cx
                cmp cx, 0
                jnz readC
        endRead:
        pop ax
    ret
    scanf endp
ends

end start ; set entry point and stop the assembler.
