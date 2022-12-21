; multi-segment executable file template.

data segment
    ; add your data here!
    
    strTitulo db 09h, 09h, "| . . . . . . . . . . . |", 0ah, 0dh, 09h, 09h, "|. . .GAME OF LIFE . . .|", 0ah, 0dh, 09h, 09h, "| . . . . . . . . . . . |$"  
    strMenu db 0ah, 0dh, 0ah, 0dh, 09h, 09h,"|", 09h, " Jogar  ", 09h,"|", 0ah, 0dh, 0ah, 0dh, 09h, 09h,"|",  09h, "Carregar", 09h,"|", 0ah, 0dh, 0ah, 0dh, 09h, 09h,"|", 09h, "Guardar ", 09h,"|", 0ah, 0dh, 0ah, 0dh, 09h, 09h,"|", 09h, " Top 5  ", 09h,"|", 0ah, 0dh, 0ah, 0dh, 09h, 09h,"|", 09h, "Creditos", 09h,"|", 0ah, 0dh, 0ah, 0dh, 09h, 09h,"|", 09h, "  Sair  ", 09h, "|$"
    
    strGeracao db "GERACAO: 000 ",0
    strCelulas db "CELULAS: 0000 ",0 
    totalGeracao dw 0
    totalCelulas dw 0
    
    strIniciar db "INICIAR ", 0
    strSair db "SAIR", 0dh, 0ah, 0
    linhas db "_", 0
    
    carregar db 09h, 09h,"Nome do Ficheiro: $"
    strGuardar db 0dh, 0ah, 09h, 09h, "Ficheiro Guardado $"
    creditos db 09h, 09h, "| . . . . . . . . . . . |", 0ah, 0dh, 09h, 09h, "|. . . .CREDITOS . . . .|", 0ah, 0dh, 09h, 09h, "| . . . . . . . . . . . |", 0ah, 0dh, 0ah, 0dh, 09h, 09h, "|  Juvenal Baera 64932  |", 0dh, 0ah, 0ah, 0dh, 09h, 09h, "|  Bernardo Costa 57910 |", 0dh, 0ah, 0ah, 0dh, 09h, 09h, "|  Goncalo Mimoso 58591 |$"
    boxLin dw 0
    boxCol dw 0
    tamBox equ 15
    segundos db 0
    strinput db 20 dup(?)
    nome db 20 dup("$")
    disPlayName db 09h, 09h, "| . . . . . . . . . . . |", 0ah, 0dh, 09h, 09h, "|. . .GAME OF LIFE . . .|", 0ah, 0dh, 09h, 09h, "| . . . . . . . . . . . |", 0ah, 0dh, 0ah, 0dh, 09h, 09h, "Digite nome: $",0
    strTop5 db 09h, 09h, "| . . . . . . . . . . . |", 0ah, 0dh, 09h, 09h, "|. . . . . TOP 5 . . . .|", 0ah, 0dh, 09h, 09h, "| . . . . . . . . . . . |", 0ah, 0dh, 0ah, 0dh, 09h, "GERACAO....CELULAS....JOGADOR....DATA....HORA$", 0ah, 0dh, 0
    
    
    handler dw ?
    buffer dw 50 dup(?)
    newLineFile db 0dh, 0ah
    strDate db "00/00/2000 00:00:00 $"
    dia db 0
    mes db 0
    ano dw 0
    
    corGrid db 0fh
    vivo db 0dh
    morto db 0h
    contVivo db 0

    geracaoMorta dw 200 dup(-1)
    geracaoViva dw 200 dup(-1)
    readLoad dw 0
    delay dw 0ffffh
    
    
    filename db 50 dup(?)
    fnGuardar db 40 dup(?)
    fnLog db "log.txt"
    strLog db 100 dup(0)
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
    
    lea dx, fnLog
    mov al, 2           ; para escrever (append)
    call fopen
    jnc _fExist
        lea dx, fnLog
        mov cx, 0
        call fcreate                    
    _fExist:          

    call mainMenuTexto       
        
    mov ax, 4C00h ; exit to operating system.
    int 21h
       
    
    ; /////////////////////////// AUXILIAR ///////////////////////////////
    ;####################################
    ; co - caracter ouput;
    ci proc
        mov ah, 7
        int 21h
        ret
    ci endp   
    
    
    ; /////////////////////////// AUXILIAR ///////////////////////////////
    ;####################################
    ; co - caracter ouput
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
   
   
    ;#######################################
    ; newLine - Salta para linha seguinte
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
    
    
    ;#####################################
    ; scanf  
    ;input: si- string a ser guardada(offset)
    ;       ax- tamanho a ler
    ;output:
    scanf proc
        push ax
        mov cx, ax
        readC:
            call ci
            call co     
            cmp al, 0dh ; se for ENTER sai
            jz endRead  
                mov byte ptr si, al
                inc si
                dec cx
                cmp cx, 0
                jnz readC
        endRead:
            mov byte ptr si, "$"
        pop ax
    ret
    scanf endp
    
    
    ;#######################################
    ; strOutD - string output terminado em $
    strOutD proc
        mov ah, 9
        int 21h
        ret
    strOutD endp
                                
                                
    ;################################
    ; funcao que le uma string e copia para nome
    lerNome proc
        mov cx, 20
        lea si, nome
        call scanf
    lerNome endp
    
    ;################################
    ; input: si - offset str
    ; output: bx - size
    strLen proc
        xor bx, bx
        lcomp:
            cmp byte ptr si, "$"
            jz endLen
            inc si
            inc bx
            jmp lcomp
        endLen:
        ret
    strLen endp
    
    ;################################
    getSisDate proc
        mov ah, 2Ah
        int 21h
        ret
    getSisDate endp
    
    ;################################
    getSisTime proc
        mov ah, 2ch
        int 21h
        ret   
    getSisTime endp 
    
    
    ;########################## FILE HANDLE ########################
    
       
    ;###################################
    ; cfile - create file
    ; par   - dx: offset of filename
    ;       - cx: type
    fcreate proc
        push ax 
        xor cx, cx
        mov ah, 3ch
        int 21h    
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
            pop ax      
            ;call fcreate
            jmp _endFile
        _openSucc:
            mov handler, ax
            mov bx, ax          ; handler do arquivo
            pop ax
            cmp al, 3
            jnz _endFile 
                xor dx, dx
                xor cx, cx      ; offset
                mov al, 2       ; SEEK END of file
                call fseek           
        _endFile: ret
    fopen endp 
                                        
     
                                        
    ; ##################################
    ; fclose - close a file    
    fclose proc 
        push ax
        push dx
        mov	bx, handler
		mov	ah, 3eh
		int	21h
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
        ret
    fread endp
     
    
    ;######################################
    ; mudar para o modo grafico
    setModoVideo proc
        mov al, 13h
        mov ah, 0
        int 10h
        call mostrarRato
        ret
    setModoVideo endp
                               
                               
    ;######################################
    ; mudar para o modo texto
    setModoTexto proc
        mov al, 3
        mov ah, 0
        int 10h
        call mostrarRato
        ret
    setModoTexto endp 
     
    ;######################################
    ; iniciar rato
    iniRato proc
        xor ax, ax
        int 33h      
        ret
    iniRato endp 
    
    ;######################################
    ;mostrar rato
    mostrarRato proc
        mov ax, 1
        int 33h
        ret
    mostrarRato endp
    
    ;######################################
    ;esconder o rato
    hideRato proc
        mov ax, 1
        int 33h
        ret
    hideRato endp
    
    
    ;######################################
    ; Status do cursor (posicao e clicado)
    ; output: cx - linha
    ;         dx - coluna
    ;         bx - 1 = left btn, 2 = right, 3 = both
    getPosicaoRato proc
        mov ax, 3
        int 33h
        ret
    getPosicaoRato endp
    
    
    ; #####################################
    ; Manda o cursor para uma dada posicao
    ; input: DH = linha
    ;        DL = coluna
    setPosRato proc
        mov ah, 2
        int 10h
        ret             
    setPosRato endp
    
    ;######################################           
    ; input: DH = linha
    ;        DL = coluna
    printRow proc
        call setPosRato ; mandar cursor para linha linha abaixo   
        mov cx, 28h     ; escreve uma linha
        lea si, linhas  
        mov bl, 0fh     
        call imprimirStrGraph
        ret
    printRow endp

    ;######################################           
    ;imprime linhas verticais
    printCol proc
        mov cx, 0   
        mov segundos, 20;20
        lcol1:
            mov bx, 200;200
            mov dx, 24
            lcol2:
                call setPosRato ; mandar cursor para linha linha abaixo   
                mov ah, 0ch
                mov al, 0fh
                int 10h
                inc dx
                dec bx
                cmp bx, 0
            jnz lcol2 
        dec  segundos
        add cx, 16
        cmp segundos, 0
        jnz lcol1
        ret
    printCol endp
    
    ;######################################           
    ;desenha a grelha de jogo
    grid proc
        mov bl, 0ch ; cor
        mov segundos, 12  ; para loop
        mov dh, 0
        
        lg1:                  
            mov dl, 0       ; start
            add dh, 2 ;inc dh          ; next line
            call printRow
            dec segundos
            cmp segundos, 0
        jnz lg1
        
        call printCol
        ret
    grid endp
    
    ;######################################  
    ;avalia a cor do pixel         
    ;input: cx,dx- posicao para avaliar a cor
    ;output: al- cor do pixel da posicao
    getPixelColor proc
        mov al, 0
        mov ah, 0dh
        int 10h
        ret
    getPixelColor endp

    ;###################################### 
    ;procura o vertice do quardrado          
    ;input: cx,dx- posicao do quadrado selecionado
    ;output: cx,dx- posicao inicial para comecar a pintar
    procurarPixel proc
        cprocP:  
           dec cx
           call getPixelColor
           cmp al, corGrid; 0fh ; cor do pixel  
        jnz cprocP
        inc cx
        
        dprocP:  
           dec dx            
           call getPixelColor
           cmp al, corGrid ; cor do pixel   
        jnz dprocP       
        inc dx
        
        ret
    procurarPixel endp
    
    ;############################################### 
    ;   pinta um quadrado 15x15
    ;   input:  cx - linha
    ;           dx - coluna
    ;           al - cor
    pintarQuad proc         
        mov boxLin, tamBox
        mov boxCol, tamBox
        add boxLin, cx      ; boxLin = 15 + cx
        add boxCol, dx      ; boxCol = 15 + dx
        mov bx, cx          ; guardar coluna onde comeca o quadrado
        pintQ1:
        push dx
            pintQ2:
            mov ah, 0ch     ; pintar um pixel
            int 10h
            inc cx
            cmp cx, boxLin 
            jnz pintQ2
        mov cx, bx          ; restore a linha para pintar do principio
         
        mov dh, dl          ; linha
        mov dl, cl          ; coluna
        call setPosRato     ; cursor para linha seguinte e coluna em cl
        pop dx
        inc dx  
        cmp dx, boxCol 
        jnz pintQ1      
        ret
    pintarQuad endp
    
                   
    
    ; ######################################
    ; Imprimi string (0) no modo grafico
    ; input: si - offset
    imprimirStrGraph proc
        printVideo:        
            mov al, byte ptr si
            or al, al
            jz fimImpStrGr
                mov ah, 09h
                int 10h
                inc dl
                mov ah, 2
                int 10h
                inc si 
            jmp printVideo
        fimImpStrGr:
        ret
    imprimirStrGraph endp              
    
    ; ######################################
    ;imprime o menu dojogo    
    menuVideo proc
        mov bh, 0   ; pagina 0
        mov bl, 0ah ; cor
        mov cx, 1   ; # char a imprimir
        
        mov dx, 0
        mov ah, 2
        int 10h
        mov si, offset strGeracao
        call imprimirStrGraph
        mov si, offset strCelulas
        call imprimirStrGraph
        mov si, offset strIniciar
        call imprimirStrGraph
        mov si, offset strSair 
        call imprimirStrGraph
        ret
    menuVideo endp
    
                                             
    ;########################################
    ; janela 
    ; al - text/grafico   
    mainMenuVideo proc 
        
        call setModoVideo              
        
        call menuVideo 
        call grid                                 
        call iniRato                
        lea si, geracaoViva
        cmp word ptr si, -1
        jnz _loadPrevGame                       ;abrir jogo guardado 
        _mostrarMenu:           
            call mostrarRato
            call getPosicaoRato
            call hideRato
            cmp dx, 07h
            jg _jogar                           ;verifica se o rato esta na opcao iniciar ou sair
                cmp cx, 01a8h
                jb _nIniciarVideo                
                cmp cx, 0224h                    
                jg _nIniciarVideo
                    cmp bx, 1
                    jnz _jogar                  ;verifica se clicou em iniciar
                        _maestro:
                        mov cx, 3
                        mov dx, 26
                        mov dia, 20             ;auxiliar para as linhas (loop)
                        mov mes, 11             ;auxiliar para as colunas (loop)
   
                        lverViz1:               
                            lverViz2:
                                push cx
                                push dx
                                push bx
                                
                                call getPosicaoRato
                                call mostrarRato
                                cmp cx, 0225h
                                jb _nSairJogo
                                cmp cx, 0276h
                                jg _nSairJogo                  ; for quit
                                    cmp bx, 1
                                    jnz _nSairJogo
                                        pop bx
                                        pop dx
                                        pop cx            
                                    ret
                                _nSairJogo:
                                pop bx
                                pop dx
                                pop cx
                                
                                call vizinho                    ;contar quantos vizinhos vivos
                                cmp contVivo, 3                 
                                jnz _mortoVivo
                                    lea si, geracaoViva                                        
                                    call inserirVetor                                       
                                    jmp _nvivoger 
                                _mortoVivo:
                                call getPixelColor              
                                cmp al, vivo                    ;verifica se celula esta viva
                                jnz _nvivoger                   ;if is live ceil                                   
                                    cmp contVivo, 2             
                                    jnz _matar1        
                                        lea si, geracaoViva                                        
                                        call inserirVetor                                       
                                        jmp _nvivoger
                                    _matar1:                    ;mata celula              
                                    lea si, geracaoMorta                                    
                                    call inserirVetor           ;inserir a posicao do vetor das celula morta
                                    dec cx
                                    dec dx
                                    lea si, geracaoViva
                                    call removerVetor           ;apaga a posicao do vetor das celula vivas
                                    inc dx
                                    inc cx
                                _nvivoger:  
                                inc cx
                                add cx, tamBox
                                dec dia  
                                cmp dia, 0
                                jnz lverViz2                    ;verifica se chegou ao fim da linha
                            mov dia, 20
                            mov cx, 3
                            inc dx
                            add dx, tamBox
                            dec mes
                            cmp mes, 0                          ;verifica se chegou ao fim da coluna
                            jnz lverViz1
                            
                            mov di, offset geracaoViva
                            call pintarCelulasViva
                            
                            mov di, offset geracaoMorta
                            call matarCelulasViva
                                                      
                            call addGeracao
                            call menuVideo      
                            
                            
                            lea si, geracaoMorta
                            call reset
                            lea si, geracaoViva 
                            call reset
                                                       
                            jmp _maestro                                                            
                _nIniciarVideo:  
                cmp cx, 0225h
                jb _nRangeVideo
                cmp cx, 0276h
                jg _nRangeVideo                  ; for quit
                    cmp bx, 1
                    jnz _nRangeVideo             
                    ret
            _nRangeVideo:
            jmp _mostrarMenu       
            _jogar:
                cmp bx, 1
                jnz _mostrarMenu
                shr cx, 1                       ; dividir por 2
                call getPixelColor
                cmp al, morto
                jnz _pintaMorto                                                       
                    call addCelula              ;pinta nova celula                         
                    jmp _menuUpdate
                _pintaMorto:
                    cmp al, vivo
                    jnz _mostrarMenu
                        call subCelula          ;apaga nova celula
               _menuUpdate:
               call menuVideo
        jmp _mostrarMenu
        
        _loadPrevGame:                          ;vai carregar o jogo
            lea di, geracaoViva
            call pintarCelulasViva
            jmp _mostrarMenu
        ret
    mainMenuVideo endp 
    
    ;########################################
    ;vai pintar as celulas do vetor di
    ; input: di - offset do vetor a reviver
    pintarCelulasViva proc
        _viverTodos:                       
            mov cx, word ptr di        
            cmp cx, -1
            jz _fviverTodos
            cmp cx, 0
            jz _nAzero1
                add di, 2
                mov dx, word ptr di
                call getPixelColor
                cmp al, vivo
                jz _npvi
                    cmp al, 0fh
                    jnz _addcd
                       inc cx
                       inc dx
                    _addcd:
                    call addCelula 
                _npvi:
                push dx
                call menuVideo
                pop dx
                add di, 2
                jmp _viverTodos
            _nAzero1:
                add di, 4
            jmp _viverTodos                                          
        _fviverTodos:         
        ret
    pintarCelulasViva endp
    
    ;########################################
    ;vai apagar as celulas do vetor di
    ; input: di - offset do vetor onde matar
    matarCelulasViva proc
        _apagarTodos:                       
            mov cx, word ptr di        
            cmp cx, -1
            jz _fapagarTodos
            cmp cx, 0
            jz _nAzero2
                add di, 2
                mov dx, word ptr di
                call subCelula
                push dx
                call menuVideo
                pop dx
                add di, 2
                jmp _apagarTodos
            _nAzero2:
                add di, 4                                   
            jmp _apagarTodos
        _fapagarTodos:
        ret                 
    matarCelulasViva endp  
    
    ;########################################
    ;limpa o vetor(-1)
    reset proc
        mov cx, 200
        _resetMorto:
            cmp w. si, -1
            jz _frest
                mov w. si, -1
                add si, 2    
        loop _resetMorto
        _frest:
    ret
    reset endp
    
    ;########################################
    ;inserir a coordenada(cx,dx) em di
    inserirVetor proc
        _lins:
            mov bx, word ptr si
            cmp bx, -1
            jz _fins
            cmp bx, 0
            jz _fins
            add si, 4
            jmp _lins
        _fins:       
        mov w. si, cx
        add si, 2
        mov w. si, dx
        ret
    inserirVetor endp
    
    ;########################################
    ;remover a coordenada(cx,dx) em di
    removerVetor proc
        _lrem:
            mov bx, word ptr si
            cmp bx, -1          ; fim da str
            jz _frem            
            cmp bx, cx          ; se for cx
            jne _strig1         ; para dx
               add si, 2
               mov bx, w. si
               cmp bx, dx       ; se for dx
               je _frem1
            _strig1:
            add si, 4
            jmp _lrem
        _frem1:       
        mov w. si, 0
        sub si, 2
        mov w. si, 0
        _frem:
        ret
    removerVetor endp
    
    ;########################################
    ;incrementa o valor celula e pinta celula    
    addCelula proc

        call procurarPixel
        mov si, offset geracaoViva
        call inserirVetor 
        xor ah, ah
        mov al, vivo        
        
        call pintarQuad
        inc totalCelulas
        inc strCelulas[12]
        cmp strCelulas[12], "9"
        jbe _nUpC
            inc strCelulas[11]
            mov strCelulas[12], "0"
            cmp strCelulas[11], "9"
            jbe _nUpC
                inc strCelulas[10]
                mov strCelulas[11], "0"
                cmp strCelulas[10], "9"
                jne _nUpC
                    inc strCelulas[9]
                    mov strCelulas[10], "0"
        _nUpC:
        ret
    addCelula endp
    
    ;########################################
    ;decrementa o valor celula e apaga celula
    subCelula proc       
        call procurarPixel
        mov al, morto        
        
        call pintarQuad
        dec totalCelulas                       
        dec strCelulas[12]
        cmp strCelulas[12], "0"
        jge _nDowC
            dec strCelulas[11]
            mov strCelulas[12], "9"
            cmp strCelulas[11], "0"
            jge _nDowC
                dec strCelulas[10]
                mov strCelulas[11], "9"
                cmp strCelulas[10], "0"
                jne _nDowC
                    dec strCelulas[9]
                    mov strCelulas[10], "9"
        _nDowC:
        ;call 
        ret   
    subCelula endp 
    
    ;########################################    
    ;incrementa o valor geracao
    addGeracao proc
        inc strGeracao[11]
        cmp strGeracao[11], "9"
        jbe _nUpG
            inc strGeracao[10]
            mov strGeracao[11], "0"
            cmp strGeracao[10], "9"
            jbe _nUpG
                inc strGeracao[9]
                mov strGeracao[10], "0"       
        _nUpG:
        ret   
    addGeracao endp
    
    ;########################################    
    ;imprime o menu    
    menuInicial proc
        mov bl, 1111_1010b
        lea dx, strTitulo
        call strOutD                        
        lea dx, strMenu
        call strOutD       
        ret
    menuInicial endp 
    
    ;########################################    
    ;nao esta completa
    ftop5 proc
        call setModoTexto
        lea dx, strTop5
        call strOutD
        call stopScreen         
        ret
    ftop5 endp 
    
    ;#######################
    ;Menu inicial em modo de texto  
    mainMenuTexto proc
        call setModoTexto                     
        call iniRato                     ; Para usar cursor
        call menuInicial
        
        loopTexto_:        
        call getPosicaoRato       
        cmp cx, 0147h
        jg naoRange
        cmp cx, 80h
        jb naoRange
        cmp dx, 20h
        jb naoRange
            cmp dx, 28h      
            jg naoJogar                 ;clicou em jogar
                cmp bx, 1
                jnz naoJogar
                
                call resetDate          ;                      
                call resetCelulas       ;
                call resetGeracao       ;reinicia as variaveis
                
                lea si, geracaoMorta    ;reinicia(-1) o vetor de morte
                call reset
                lea si, geracaoViva     ;reinicia(-1) o vetor vida
                call reset                   
                call setDateTime
                                
                call setModoTexto
                lea dx, displayName
                call strOutD                   
                call lerNome                        

                call mainMenuVideo 
                call setModoTexto
                call mostrarRato
                
                mov bl, 1111_1010b
                call menuInicial
                jmp naoRange
            naoJogar:
            
            cmp dx, 38h
            jg naoCarregar              ;clicou em carregar
            cmp dx, 30h
            jb naoCarregar
            cmp bx, 1
                jnz naoCarregar
                call load        
                
                call mainMenuVideo 
                call setModoTexto
                mov bl, 1111_1010b
                call menuInicial
                jmp naoRange
            naoCarregar:
            
            cmp dx, 48h
            jg naoGuardar               ;clicou em guardar
            cmp dx, 40h
            jb naoGuardar
                cmp bx, 1
                jnz naoGuardar           
                call guardar
                call setModoTexto
                lea dx, strTitulo
                call strOutD
                call newLine
                lea dx, strGuardar
                call strOutD
                call stopScreen
                call setModoTexto
                call menuInicial               
                jmp naoRange
            naoGuardar:
            
            cmp dx, 58h
            jg naoTop5                  ;clicou top5
            cmp dx, 50h
            jb naoTop5
                cmp bx, 1
                jnz naoTop5
                call newLine
                call ftop5
                call setModoTexto
                call menuInicial
                jmp naoRange
            naoTop5:
            
            cmp dx, 68h
            jg naoCreditos              ;clicou em creditos
            cmp dx, 60h
            jb naoCreditos
                cmp bx, 1
                jnz naoCreditos
                call mostrarCreditos
                call setModoTexto
                call menuInicial
                jmp naoRange
            naoCreditos:
            
            cmp dx, 78h
            jg naoRange                 ;nenhuma opcao foi selecionada
            cmp dx, 70h
            jb naoRange
                cmp bx, 1
                jnz naoRange
                
                ;aaaammdd:hhmmss:nome:geracao:celulas
                mov al, 3                       ;abrir ficheiro para fazer append
                mov dx, offset fnLog
                call fopen
                
                lea di, strLog               
                mov al, strDate[6]
                mov byte ptr di, al  ; ano
                inc di             
                mov al, strDate[7]
                mov byte ptr di, al  ; ano                
                inc di
                mov al, strDate[8]   ; ano
                mov byte ptr di, al
                inc di             
                mov al, strDate[9]   ; ano
                mov byte ptr di, al
                inc di  
                         
                mov al, strDate[3]
                mov byte ptr di, al  ; mes
                inc di             
                mov al, strDate[4]
                mov byte ptr di, al  ; mes
                
                inc di             
                mov al, strDate[0]   ; dia
                mov byte ptr di, al
                inc di             
                mov al, strDate[1]   ; dia
                mov byte ptr di, al
                inc di             
                mov byte ptr di, ":"
                inc di             
                mov al, strDate[11]  ; hora
                mov byte ptr di, al
                
                inc di             
                mov al, strDate[12]  ; hora
                mov byte ptr di, al
                inc di             
                mov al, strDate[14]  ; min
                mov byte ptr di, al
                inc di             
                mov al, strDate[15]  ; min
                mov byte ptr di, al
                inc di             
                mov al, strDate[17]  ; sec
                mov byte ptr di, al
                inc di             
                mov al, strDate[18]  ; sec
                mov byte ptr di, al
                
                inc di
                mov byte ptr di, ":"
                inc di
                mov si, offset nome
                call strLen
                mov cx, bx
                mov si, offset nome   
                rep movsb   ; copy nome to fnguardar
                
                ;inc di
                mov byte ptr di, ":"      
                
                inc di
                mov al, strGeracao[9]
                mov byte ptr di, al
                inc di
                mov al, strGeracao[10]
                mov byte ptr di, al  
                inc di
                mov al, strGeracao[11]
                mov byte ptr di, al
                
                inc di
                mov byte ptr di, ":" 
                
                inc di
                mov al, strCelulas[9]
                mov byte ptr di, al
                
                inc di
                mov al, strCelulas[10]
                mov byte ptr di, al
                
                inc di
                mov al, strCelulas[11]
                mov byte ptr di, al  
                
                inc di
                mov al, strCelulas[12]
                mov byte ptr di, al
                
                
                mov cx, 25
                mov si, offset nome
                call strLen
                add cx, bx
                
                mov bx, handler                
                 
                lea dx, strLog                
                call fwrite
                
                lea dx, newLineFile
                mov cx, 2
                mov bx, handler
                call fwrite
                call fclose                
                              
                mov ax, 4c00h                    ; Sair do programa
                int 21h
        naoRange:
        jmp loopTexto_                           ; Em caso de nao aceitar o cursor
        ret
    mainMenuTexto endp                  
    
    ;###################################
    ;coloca celulas a zero
    resetCelulas proc
        mov strCelulas[12], "0"
        mov strCelulas[11], "0"
        mov strCelulas[10], "0"
        mov strCelulas[9],  "0"
        ret   
    resetCelulas endp

    ;###################################
    ;coloca geracao a zero    
    resetGeracao proc
        mov strGeracao[11], "0"
        mov strGeracao[10], "0"         
        mov strGeracao[9], "0"
        ret   
    resetGeracao endp

    ;###################################
    ;coloca data a zero    
    resetDate proc
        mov strDate[0], "0"
        mov strDate[1], "0"
        mov strDate[3], "0"
        mov strDate[4], "0"
        mov strDate[8], "0"
        mov strDate[9], "0"               
        mov strDate[11], "0"
        mov strDate[12], "0"
        mov strDate[14], "0"
        mov strDate[15], "0"
        mov strDate[17], "0"
        mov strDate[18], "0"
        ret   
    resetDate endp
    
    ;###################################
    ;monta a data
    setDateTime proc    
        call getSisDate
        mov dia, dl
        mov mes, dh
        mov ano, cx
        
        _ldia:
           inc strDate[1]
           cmp strDate[1], "9"
           jbe _nUpDia
               inc strDate[0]
               mov strDate[1], "0"
           _nUpdia:  
           dec dia          
           cmp dia, 0
        jnz _ldia                 
        
        _lmes:
           inc strDate[4]
           cmp strDate[4], "9"
           jbe _nUpMes
               inc strDate[3]
               mov strDate[4], "0"
           _nUpMes:  
           dec mes          ; 10
           cmp mes, 0
        jnz _lmes
        
        mov bx, 2000
        mov dx, 0   
        mov ax, ano
        div bx
        mov ano, dx
        
        _lano:
           inc strDate[9]
           cmp strDate[9], "9"
           jbe _nUpAno
               inc strDate[8]
               mov strDate[9], "0"
           _nUpAno:  
           dec ano          ; 10
           cmp ano, 0
        jnz _lano
    
        call getSisTime
        mov dia, ch ; hor
        mov mes, cl ; min
        mov dl, dh
        xor dh, dh
        mov ano, dx ; sec
        
        _lhora:
           cmp dia, 0
           jbe _lhoraF:
           inc strDate[12]
           cmp strDate[12], "9"
           jbe _nUpH
               inc strDate[11]
               mov strDate[12], "0"
           _nUpH:  
           dec dia          
        jmp _lhora 
        _lhoraF:
        
        _lmin:
           cmp mes, 0
           jbe _lminF
           inc strDate[15]
           cmp strDate[15], "9"
           jbe _nUpM
               inc strDate[14]
               mov strDate[15], "0"
           _nUpM:  
           dec mes         
        jmp _lmin
        _lminF:
        
        _lsec:
           cmp ano, 0
           jbe _lsecF
           inc strDate[18]
           cmp strDate[18], "9"
           jbe _nUpS
               inc strDate[17]
               mov strDate[18], "0"
           _nUpS:  
           dec ano  
        jmp _lsec
        _lsecF:
        ret   
    setDateTime endp
      
    ;###################################
    ;para o cpu por 0.5 segundos    
    pararSegundo proc
        push cx
        push dx
        push bx
        mov cx, 07h
        mov dx, 0A120h
        mov ah, 86h
        int 15h
        pop bx
        pop dx
        pop cx
        ret
    pararSegundo endp
    
    ;###################################
    ;para o ecra por 10 segundos   
    stopScreen proc
        mov segundos, 0
        tempo:
        call pararSegundo
        inc segundos
        cmp segundos, 20
        jz sair
        
        mov dl, 255
        mov ah, 6
        int 21h  
        cmp al, 0
        jng tempo
        sair:
        ret
    stopScreen endp
    
    ;###################################
    ;mostra os creditos    
    mostrarCreditos proc
        call setModoTexto
        lea dx, creditos
        call strOutD
        call stopScreen       
        ret 
    mostrarCreditos endp
    
    
    ; ########################### MAESTRO ########################
    ;##################
    ;conta os vizinhos vivos da celula
    ;input:cx,dx- celula para verificar 
    ;output: contVivo- quantidade de vizinhos vivos 
    
    vizinho proc       
        mov contVivo, 0      
        
        mov boxLin, cx
        mov boxCol, dx
        
        add cx, tamBox              ; direita 
        call getPixelColor
        cmp al, vivo
        jnz _morto1
            inc contVivo       ; +1
        _morto1:
        
        mov cx, boxLin
        sub cx, tamBox              ; esquerda
        call getPixelColor
        cmp al, vivo
        jnz _morto2
            inc contVivo       ; +1
        _morto2:
        mov cx, boxLin
        
        add dx, tamBox              ; baixo
        call getPixelColor
        cmp al, vivo
        jnz _morto3
            inc contVivo       ; +1
        _morto3:
        
        mov dx, boxCol
        sub dx, tamBox              ; cima
        call getPixelColor
        cmp al, vivo
        jnz _morto4
            inc contVivo       ; +1
        _morto4:
        
        mov dx, boxCol
        mov cx, boxLin
        add cx, tamBox
        add dx, tamBox              ; baixo -> direita
        call getPixelColor
        cmp al, vivo
        jnz _morto5
            inc contVivo       ; +1
        _morto5:
                                
        mov dx, boxCol
        mov cx, boxLin
        add cx, tamBox
        sub dx, tamBox              ; cima -> direita
        call getPixelColor
        cmp al, vivo
        jnz _morto6
            inc contVivo       ; +1
        _morto6:
        
        mov dx, boxCol
        mov cx, boxLin
        sub cx, tamBox
        sub dx, tamBox              ; cima -> esquerda
        call getPixelColor
        cmp al, vivo
        jnz _morto7
            inc contVivo       ; +1
        _morto7:
        
        mov dx, boxCol
        mov cx, boxLin
        sub cx, tamBox
        add dx, tamBox              ; baixo -> esquerda
        call getPixelColor
        cmp al, vivo
        jnz _morto8
            inc contVivo       ; +1
        _morto8:
        
        mov cx, boxLin
        mov dx, boxCol       
        ret
    vizinho endp
    
    ;###################################
    ;gera o nome do ficheiro .GAM (nomeaammddhhmmss.GAM)   
    generateFNameSave proc
        push ax
        push bx
        push si
        push di
        
        mov si, offset nome
        call strLen
        mov cx, bx
        mov si, offset nome
        mov di, offset fnGuardar   
        rep movsb   ; copy nome to fnguardar
        
        lea si, nome
        
        lea si, fnGuardar
         
        add si, bx
        mov al, strDate[8]
        mov byte ptr si, al  ; ano
        inc si             
        mov al, strDate[9]
        mov byte ptr si, al  ; ano
        
        inc si
        mov al, strDate[3]   ; mes
        mov byte ptr si, al
        inc si             
        mov al, strDate[4]   ; mes
        mov byte ptr si, al
        inc si           
        mov al, strDate[0]
        mov byte ptr si, al  ; dia
        inc si             
        mov al, strDate[1]
        mov byte ptr si, al  ; dia
        
        inc si             
        mov al, strDate[11]  ; hora
        mov byte ptr si, al
        inc si             
        mov al, strDate[12]  ; hora
        mov byte ptr si, al
        
        inc si             
        mov al, strDate[14]  ; min
        mov byte ptr si, al
        inc si             
        mov al, strDate[15]  ; min
        mov byte ptr si, al
        
        inc si             
        mov al, strDate[17]  ; sec
        mov byte ptr si, al
        inc si             
        mov al, strDate[18]  ; sec
        mov byte ptr si, al
        
        inc si
        mov byte ptr si, "."       
        inc si
        mov byte ptr si, "G"        
        inc si
        mov byte ptr si, "A"        
        inc si
        mov byte ptr si, "M"
        
        pop di
        pop si
        pop bx
        pop ax
        
        ret
    generateFNameSave endp

    ;##########################
    ;carrega o jogo guardado no ficheiro
    load proc
        
        lea si, geracaoMorta
        call reset
        lea si, geracaoViva 
        call reset
        
        call setModoTexto
        lea dx, strTitulo
        call strOutD
        call newLine
        call newLine
        lea dx, carregar
        call strOutD
        lea si, filename
        call scanf
        lea si, filename
        call strlen
        mov b. si, 0
        
        lea dx, filename
        mov al, 0       ; abrir ficheiro para ler
        call fopen   
        mov bx, handler
        lea dx, geracaoViva
        mov cx, 200
        call fread
        ret
    load endp
    
    ;###################################
    ;guarda o jogo num ficheiro 
    guardar proc 
        lea si, geracaoViva       
        cmp w. si, -1
        jz _nSave            
            call generateFNameSave
            lea dx, fnGuardar
            call fcreate
            mov ah, 1
            call fopen
            lea dx, geracaoViva
            mov bx, handler     
            _lGuardar:
            push dx 
            mov cx, 2
            call fwrite
            pop dx
            add dx, 2
            add si, 2
            cmp word ptr si, -1
            jnz _lGuardar
            call fclose
        _nSave:
        ret   
    guardar endp
ends

end start ; set entry point and stop the assembler.

