:- dynamic instalacao/3.
:- dynamic ligacao/3.

% ############### FACTOS             ####################
instalacao(1, monofasico(6.9),  1022).
instalacao(2, monofasico(10.5), 890).
instalacao(3, trifasico(13.80), 1990).
instalacao(4, trifasico(20.70), 1229).

% Adicionar instala��o
ler_instalacao :- writeln("Digite seguintes informa��es:"),
    write("Id da instala��o: "), read(Id_ins), nl,
    write("Tipo da instala��o: "), read(Tipo_ins), nl,
    write("Consumo Energ�tico"), read(Consumo),nl.



% ############### COME�O DO PROGRAMA ###################

comecar :- nl, nl, writeln("##### LABWORK #2 DE MDE #####"), nl,
    menu_principal(Opcao), executar_opcao(Opcao).

menu_principal(Opcao) :- writeln("0 - Sair"),
    writeln("1  - Adicionar uma instala��o � rede."),
    writeln("2  - Adicionar dispositivos a uma instala��o."),
    writeln("3  - Adicionar liga��o entre duas instala��es."),
    writeln("4  - Adicionar consumo a um dispositivo de uma instala��o."),
    writeln("5  - Alterar uma instala��o da rede."),
    writeln("6  - Alterar um dispositivo de uma instala��o."),
    writeln("7  - Alterar liga��o entre duas instala��es."),
    writeln("8  - Alterar consumo de um dispositivo de uma instala��o."),
    writeln("9  - Remover instala��o da rede."),
    writeln("10 - Remover um dispositivo de uma instala��o."),
    writeln("11 - Remover liga��o entre duas instala��es."),
    writeln("12 - Remover consume de um dispositivo."), nl,
    ler_opcao(Opcao).


% L� opc��o a partir do teclado
ler_opcao(Opcao) :- read(Opcao), validar_opcao(Opcao), nl.
ler_opcao(Opcao) :- nl, writeln("ERRO: Opcao Invalida"), nl, ler_opcao(Opcao).

% Validar a op��o
validar_opcao(Opcao) :- Opcao >= 0 ; Opcao =< 12.


executar_opcao(0) :- nl, writeln("Muito Obrigado, at� a pr�xima").
executar_opcao(Opcao) :- executar(Opcao), nl, menu_principal(NOpcao), executar_opcao(NOpcao).


% Executa cada op��o lida
executar(1)  :- writeln("Adicionar uma instalacao").
executar(2)  :- writeln("Adicionar um dispositivo a uma instalacao").
executar(3)  :- writeln("Adicionar ligacao entre duas instala��es").
executar(4)  :- writeln("Adicionar consumo a um dispositivo de uma instala��o").
executar(5)  :- writeln("Alterar uma instala��o da rede").
executar(6)  :- writeln("Alterar um dispositivo de uma instal��o").
executar(7)  :- writeln("Alterar liga��o entre duas instala��es").
executar(8)  :- writeln("Alterar consumo de um dispositivo de um instal��o").
executar(9)  :- writeln("Remover instal��o da rede").
executar(10) :- writeln("Remover um diss...").
executar(11) :- writeln("Remover ....").
executar(12) :- writeln("Remover .....").




