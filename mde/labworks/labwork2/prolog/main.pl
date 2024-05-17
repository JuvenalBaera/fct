:- dynamic instalacao/3.
:- dynamic ligacao/3.

% ############### FACTOS             ####################
instalacao(1, monofasico(6.9),  1022).
instalacao(2, monofasico(10.5), 890).
instalacao(3, trifasico(13.80), 1990).
instalacao(4, trifasico(20.70), 1229).

% Adicionar instalação
ler_instalacao :- writeln("Digite seguintes informações:"),
    write("Id da instalação: "), read(Id_ins), nl,
    write("Tipo da instalação: "), read(Tipo_ins), nl,
    write("Consumo Energético"), read(Consumo),nl.



% ############### COMEÇO DO PROGRAMA ###################

comecar :- nl, nl, writeln("##### LABWORK #2 DE MDE #####"), nl,
    menu_principal(Opcao), executar_opcao(Opcao).

menu_principal(Opcao) :- writeln("0 - Sair"),
    writeln("1  - Adicionar uma instalação à rede."),
    writeln("2  - Adicionar dispositivos a uma instalação."),
    writeln("3  - Adicionar ligação entre duas instalações."),
    writeln("4  - Adicionar consumo a um dispositivo de uma instalação."),
    writeln("5  - Alterar uma instalação da rede."),
    writeln("6  - Alterar um dispositivo de uma instalação."),
    writeln("7  - Alterar ligação entre duas instalações."),
    writeln("8  - Alterar consumo de um dispositivo de uma instalação."),
    writeln("9  - Remover instalação da rede."),
    writeln("10 - Remover um dispositivo de uma instalação."),
    writeln("11 - Remover ligação entre duas instalações."),
    writeln("12 - Remover consume de um dispositivo."), nl,
    ler_opcao(Opcao).


% Lê opcção a partir do teclado
ler_opcao(Opcao) :- read(Opcao), validar_opcao(Opcao), nl.
ler_opcao(Opcao) :- nl, writeln("ERRO: Opcao Invalida"), nl, ler_opcao(Opcao).

% Validar a opção
validar_opcao(Opcao) :- Opcao >= 0 ; Opcao =< 12.


executar_opcao(0) :- nl, writeln("Muito Obrigado, até a próxima").
executar_opcao(Opcao) :- executar(Opcao), nl, menu_principal(NOpcao), executar_opcao(NOpcao).


% Executa cada opção lida
executar(1)  :- writeln("Adicionar uma instalacao").
executar(2)  :- writeln("Adicionar um dispositivo a uma instalacao").
executar(3)  :- writeln("Adicionar ligacao entre duas instalações").
executar(4)  :- writeln("Adicionar consumo a um dispositivo de uma instalação").
executar(5)  :- writeln("Alterar uma instalação da rede").
executar(6)  :- writeln("Alterar um dispositivo de uma instalção").
executar(7)  :- writeln("Alterar ligação entre duas instalações").
executar(8)  :- writeln("Alterar consumo de um dispositivo de um instalção").
executar(9)  :- writeln("Remover instalção da rede").
executar(10) :- writeln("Remover um diss...").
executar(11) :- writeln("Remover ....").
executar(12) :- writeln("Remover .....").




