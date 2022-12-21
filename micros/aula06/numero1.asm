; multi-segment executable file template.

data segment
    apresentation db "Bem vindo ao programa da aula 7!",0dh,0ah,"$"
    perguntainicial db "Deseja comparar as tabelas por string (opcao 1) ou por caracter (opcao 2): ","$"
    mensagemErro db 0dh,0ah,"Opcao invalida. Por favor tente novamente.",0dh,0ah,"$"
    writeTrue db "True",0dh,0ah,"$" 
    writeFalse db "False",0dh,0ah,"$" 
    presentResult db 0dh,0ah,"Results", 0dh,0ah, "$"
    Tabela1 db "cola      ","Golo      ","Futebol   "
    Tabela2 db "cola      ","Golo      ","Futeboa   "
    Resultado db dup 3 (0)
    opcaoescolhida db 0
    letraString db 0dh,0ah,"Escolha a letra que pretende verificar: ", "$"
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
    lea dx,apresentation
    mov ah, 9
    int 21h
    backtothebeggining:
    lea dx,perguntainicial
    mov ah, 9
    int 21h
    mov ah, 1
	int 21h
	cmp al, '1'
    je opcaostrings
    cmp al, '2'
    je opcaochar 
    jmp opcaoinvalida
    opcaostrings:
    
    mov cx, 1
    mov bx, offset Resultado
    mov SI, offset Tabela1
    mov DI, offset Tabela2
    call compararTabelasString
    lea dx, presentResult
    mov bx, offset Resultado
    mov cx, 0
    call apresentarResultado
    jmp finalizarprograma
    
    opcaochar:
    
    lea dx, letraString
    mov ah, 9
    int 21h
    mov ah, 1
	int 21h
    mov cx, 1
    mov bx, offset Resultado
    mov DI, offset Tabela2
    call compararTabelasChar
    lea dx, presentResult
    mov bx, offset Resultado
    mov cx, 0
    call apresentarResultado
    jmp finalizarprograma
    
    
    finalizarprograma:
    mov ax,4c00h ; terminate program
    int 21h
    
    opcaoinvalida:
    lea dx,mensagemErro
    mov ah, 9
    int 21h
    jmp backtothebeggining
    
;*******************************************************************
;stringsChar: ve se um caracter esta presente na string
;Descricao: indica se um dado caracter esta presente na string (1) ou nao (0) 
;In: CX= tamanho da string, DI=string, AL=caracter
;Out: DL=1 se o caracter existe, DL=0 se o caracter nao exise
;Registos alterados: CX, AL, SI e Dl                          
;******************************************************************* 
stringsChar proc
       cld
       xor dl, dl
       repne scasb
       jnz semCaracter
       mov dl, 1
       semCaracter: ret    
stringsChar endp
    
;*******************************************************************
;stringsIguais - ve se duas strings com o mesmo tamanho sao iguais
;Descricao: se duas strings sao iguais AL=1, se sao diferentes AL=0
;In: CX= tamanho das string, SI=uma string DI=outra string
;Out: AL=1 se iguais, AL=0 se diferentes
;Registos alterados: CX, AL, SI e DI                          
;******************************************************************* 
stringsIguais proc
       cld
       xor al, al
       repe cmpsb
       jnz stringsDiferentes
       mov al, 1
       stringsDiferentes: ret    
stringsIguais endp
;*******************************************************************
;compararTabelasString - compara duas tabelas de palavras de dimensao 10 
;Descricao: Retorna o offset da tabela de resultados
;In: CX= tamanho das string, SI=Tabela1 DI=Tabela2
;Out: AL=1 se iguais, AL=0 se diferentes
;Registos alterados: CX, BX, SI e DI                          
;*******************************************************************
compararTabelasString proc   
    
verifica_String:
    push cx     
    push SI  
    push DI
    mov cx, 10
    call stringsIguais
    pop DI
    pop SI
    pop cx
    
    mov [bx], al
    cmp cx, 3
    je fimStrings
    inc bx
    inc cx      
    add SI, 10
    add DI, 10
    jmp verifica_String
    fimStrings:
    ret

compararTabelasString endp 

;*******************************************************************
;compararTabelasChar - compara duas tabelas de palavras de dimensao 10 
;Descricao: Retorna o offset da tabela de resultados
;In: CX= tamanho das string, SI=Tabela1 DI=Tabela2
;Out: AL=1 se iguais, AL=0 se diferentes
;Registos alterados: CX, BX, SI e DI                          
;*******************************************************************
compararTabelasChar proc   
    
verifica_Char:
         push cx  
         push DI
         mov cx, 10
         call stringsChar 
         pop DI
         pop cx
         mov [bx], dl
         cmp cx, 3
         je fimChar
         inc bx
         inc cx      
         add DI, 10
         jmp verifica_Char
    fimChar:
    ret
compararTabelasChar endp


;*******************************************************************
;apresentarResultado - Apresenta no monitor a tabela de resultados 
;Descricao: Faz print da tabela de resultados
;In: CX= contador para string, BX=offset da tabela de resultado,
;    DX= offset para string "Results"
;Registos alterados: CX, BX                         
;*******************************************************************
apresentarResultado proc
    
    
    mov ah, 9
    int 21h       
    percorreResultados:
        cmp cx, 3
        je fimapresentacao
        cmp [bx], 1
        je escreveTrue
        
        ;escreve falso
        lea dx, writeFalse
        mov ah, 9
        int 21h   
        jmp incrementa
    
        escreveTrue:
        lea dx, writeTrue
        mov ah, 9
        int 21h 
        jmp incrementa
    
        incrementa:
        inc cx
        inc bx
        jmp percorreResultados    
    
    
    fimapresentacao:
    ret
    
apresentarResultado endp
;*******************************************************************
ends

end start ; set entry point and stop the assembler.
  
  
