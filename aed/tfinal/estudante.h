#ifndef ESTUDANTE_H_
#define ESTUDANTE_H_

typedef struct _estudante *estudante;

estudante criaEstudante(char *login, char *nome, int idade, char *local, char *uni);
void destroiEstudante(estudante e);
char* daLocalidadeEstudante(estudante e);
int daIdadeEstudante(estudante e);
int existeCandidaturaQuartoEstudante(estudante e, quarto q);
void adicionaCandidaturaEstudante(estudante e, quarto q);


#endif