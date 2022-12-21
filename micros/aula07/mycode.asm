; multi-segment executable file template.

data segment
    ; add your data here!
    
    handle dw ?
    buffer dw 100 dup(?)
    data_write db "Hello",0dh,0ah, "World"
    
    folder db "c:\micros", 0
    filename db "c:\micros\myfile.txt", 0     
    
    erro_create_dir db "Folder already exists$"
    erro_remove_dir db "Folder does not exist$"
    erro_create_file db "Error on creating a file$"
    erro_del_file db "Error on deleting a file$"
   
    erro_open db "Error on open file$"
    erro_fseek db "Error on SEEK file$"      
    erro_read db "Error on read file$"
    erro_close db "Error on close file$"
    erro_write db "Error on write file$"
    
    
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
    
    
    xor ax, ax   
    lea dx, filename  
    mov al, 1
    call fopen
    
    mov bx, handle
    mov dx, offset data_write 
    mov cx, 12
    call fwrite
    call fclose

    ;mov cx, 11
    ;call fread
    ;call fclose
    
    
    mov ax, 4c00h ; exit to operating system.
    int 21h
            
    
      
            
            
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
     
    
    
    ; ##################################
    ; newLine - go to next line
    newLine proc
        mov al, 0dh
        call co    
        mov al, 0ah
        call co
    ret
    newLine endp   
           
                   
                   
    ;##################################
    ; printf - print a string
    printf proc
        mov ah, 9
        int 21h
        ret
    printf endp
                                                         
                   
                   
    ;###################################
    ; cfile - create file
    ; par   - dx: offset of filename
    ;       - cx: type
    ; 
    
    fcreate proc
        push ax
        mov ah, 3ch
        int 21h    
         
        jnc _fileCr
            mov dx, offset erro_create_file
            call printf
        _fileCr:
        pop ax
        ret
    fcreate endp
    
    
    
    ;####################################
    ; fseek - set cursor to a specific position in file
    ; input - bx    : handler
    ;         cx:dx : offset
    ;         al    : 0 - start, 1 - current, 2 - end
    fseek proc
        mov ah, 42h
        int 21h
        jnc _endSeek
            lea dx, erro_fseek
            call printf
        _endSeek:
        ret
    fseek endp
    
     
     
    ;####################################
    ; fopen  - open file
    ; input  - al: 0 - read, 1 - write, 2 - read/write, 3 - append
    ;          dx: filename
    ; output - fileHandle (handle)
    
    fopen proc 
        push ax
        cmp al, 3
        jnz _append
           dec al
        _append:
        mov ah, 3dh
        int 21h
        jnc _openSucc
            mov handle, 0
            lea dx, erro_open
            call printf
            pop ax
            jmp _endFile
     
        _openSucc:
            mov handle, ax
            mov bx, ax          ; handler do arquivo
            pop ax
            cmp al, 3
            jnz _endFile 
                xor dx, dx
                xor cx, cx
                mov al, 2       ; SEEK end of file
                call fseek           
        _endFile: 
        ret
    fopen endp 
                                        
     
                                        
    ; ##################################
    ; fclose - close a file
    
    fclose proc 
        push ax
        push dx
        mov	bx, handle
		mov	ah, 3eh
		int	21h
		jnc _endClose      
		    lea dx, erro_close
		    call printf
		_endClose: 
		
		pop dx
		pop ax
        ret
    fclose endp
      
      
         
    ;##################################
    ; fwrite    
    ; input - cx: size (byte)
    ;         dx: content to write  
         
    fwrite proc        
            mov ah, 40h
            int 21h
            jnc _endWrite
                lea dx, erro_write
                call printf
            _endWrite: 
        ret
    fwrite endp
    
    
    
    ; ##################################
    ; fread - read from a file to a buffer
    ; input - dx: filename
    ;         cx: size (byte) 
    ;         bx: handle
    ; out   - dx: contain
    
    fread proc
        mov ah, 3fh
        int 21h  
        jnc _readSucc
            lea dx, erro_read
            call printf
            jmp _endRead
        _readSucc:
            mov buffer, dx
        _endRead:
        ret
    fread endp
      
    
    
    ;#############################
    ; makedir - create a directory
    ; par     - dx
    ; out     - none
    
    makedir proc
        push ax
        
        mov ah, 39h
        int 21h   
        cmp al, 0
        jz _endMk
            lea dx, erro_create_dir
            int 21h   
            call printf
            call newLine
        _endMk:
        pop ax       
        ret
    makedir endp
    
     
    
    ;##################################
    ; removedir - remove a directory
    ; par       - dx
    
    removedir proc
        push ax
        mov ah, 3ah
        int 21h
            
        jnc _endRm
            lea dx, erro_remove_dir
            call printf 
            call newLine
        _endRm:
        pop ax       
        ret
    removedir endp
    
    
    
    ;####################################
    ; delfile  
    ; par   - dx: filename
    
    delfile proc
        push ax
        mov ah, 41h
        int 21h
                   
        jnc _endDel
            mov dx, offset erro_del_file
            call printf
            call newLine
        _endDel:
        pop ax
        ret
    delfile endp
    
    
ends

end start ; set entry point and stop the assembler.

