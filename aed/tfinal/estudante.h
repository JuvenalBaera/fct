#ifndef ESTUDANTE_H_
#define ESTUDANTE_H_

typedef struct _estudante *estudante;

estudante criaEstudante(char *login, char *nome, int idade, char *local, char *uni);
void destroiEstudante(estudante e);
char* daLocal(estudante e);
int daIdade(estudante e);

#endif