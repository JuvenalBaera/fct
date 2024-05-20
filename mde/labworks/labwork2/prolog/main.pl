:- dynamic instalacao/5.
:- dynamic ligacao/5.
:- dynamic dispositivo/3.


%dispositivo(1, )

% ############### FACTOS             ####################
/*
instalacao(1, monofasico(6.9),  1022).
instalacao(2, monofasico(10.5), 890).
instalacao(3, trifasico(13.80), 1990).
instalacao(4, trifasico(20.70), 1229).
*/

% ########## DISPOSITIVO ########
adicionar_dispositivo :- writeln("Digite as seguintes info:"),
    write("Id"), read(Id),
    write("Tipo"), read(Tipo),
    assertz(dispositivo(Id, Tipo, 0)).

adicionar_consumo_dispositivo :- write("Digite id do dispositivo"), read(Id),
    (dispositivo(Id,Tipo,_)
    ->  T = Tipo,
        write("Digite nivel de consumo"), read(Cons),
        retract(dispositivo(Id,_,_)),
        assertz(dispositivo(Id, T, Cons))
    ); writeln("Dispositivo Inexistente").


remover_dispositivo :- write("Digite id do dispositivo"), read(Id),
    (dispositivo(Id,_,_)
    ->  retract(dispositivo(Id,_,_)),
        writeln("Dispositivo removido")
    ); (writeln("Dispositivo inexistente")).


% ########## INSTALACAO ###########
adicionar_instalacao :- writeln("Digite seguintes informacoes:"),
    write("Id"), read(Id_ins),
    write("Tipo (tri, mono)"), read(Tipo_ins),
    write("Potencia"), read(Pot),
    assertz(instalacao(Id_ins, Pot, Tipo_ins, 0, [0])),
    writeln("Instalacao Adicionada").

remover_instalacao :- write("Digite Id da instalacao: "), read(Id),
    (instalacao(Id,_,_,_,_)
    -> retract(instalacao(Id,_,_,_,_)),
       writeln("Instalacao removida")
    ); (writeln("Instalacao nao existe")).



% ########### LIGACAO ##########
adicionar_condutor(Cond) :- writeln("ADICIONAR CONDUTOR"),
    write("Tipo"), read(Tipo),
    write("Material"), read(Mat),
    write("Isolamento"), read(Iso),
    Cond = condutor(Tipo, Mat, Iso).

adicionar_ligacao :- writeln("DADOS DA LIGACAO"),
    write("Id Inst. Origem"), read(Ori),
    write("Id Inst. Destino"), read(Des),
    adicionar_condutor(Con),
    write("Comprimento"), read(Comp),
    write("Perdas"), read(Perd),
    assertz(ligacao(Ori, Des, Con, Comp, Perd)).

remover_ligacao :- write("Digite Id Origem"), read(O),
    write("Digite Id Destino"), read(D),
    (ligacao(O, D,_,_,_)
    ->  retract(ligacao(O, D,_,_,_)),
        writeln("Ligacao removida")
    ); (writeln("Ligacao inexistente")).


% ############### COME�O DO PROGRAMA ###################

comecar :- nl, nl, writeln("##### LABWORK #2 DE MDE #####"), nl,
    menu_principal(Opcao), executar_opcao(Opcao).

menu_principal(Opcao) :- writeln("0 - Sair"),
    writeln("1  - Adicionar uma instalacao na rede."),
    writeln("2  - Adicionar dispositivo a uma instalacao."),
    writeln("3  - Adicionar ligacao entre duas instalacoes."),
    writeln("4  - Adicionar consumo a um dispositivo de uma instalacao."),
    writeln("5  - Alterar uma instalacoes da rede."),
    writeln("6  - Alterar um dispositivo de uma instalacao."),
    writeln("7  - Alterar ligacao entre duas instalacoes."),
    writeln("8  - Alterar consumo de um dispositivo de uma instalacao."),
    writeln("9  - Remover instalacao da rede."),
    writeln("10 - Remover um dispositivo de uma instalacao."),
    writeln("11 - Remover ligacao entre duas instalacoes."),
    writeln("12 - Remover consumo de um dispositivo."), nl,
    ler_opcao(Opcao).


% L� opc��o a partir do teclado
ler_opcao(Opcao) :- read(Opcao), validar_opcao(Opcao), nl.
ler_opcao(Opcao) :- nl, writeln("ERRO: Opcao Invalida"), nl, ler_opcao(Opcao).

% Validar a op��o
validar_opcao(Opcao) :- Opcao >= 0 ; Opcao =< 12.


executar_opcao(0) :- nl, writeln("Muito Obrigado, at� a pr�xima").
executar_opcao(Opcao) :- executar(Opcao), nl, menu_principal(NOpcao), executar_opcao(NOpcao).


% Executa cada op��o lida
executar(1)  :- adicionar_instalacao.
executar(2)  :- adicionar_dispositivo.
executar(3)  :- adicionar_ligacao.
executar(4)  :- adicionar_consumo_dispositivo.
executar(5)  :- writeln("Alterar uma instala��o da rede").
executar(6)  :- writeln("Alterar um dispositivo de uma instal��o").
executar(7)  :- writeln("Alterar liga��o entre duas instala��es").
executar(8)  :- writeln("Alterar consumo de um dispositivo de um instal��o").
executar(9)  :- remover_instalacao.
executar(10) :- remover_dispositivo. % NAO
executar(11) :- remover_ligacao.
executar(12) :- writeln("Remover .....").




