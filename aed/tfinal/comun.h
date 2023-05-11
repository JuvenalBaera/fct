#ifndef _H_COMUM
#define _H_COMUM

typedef struct _comum *comum;

comum criaComum(char *login, char *nome, char *uni);
void destroiComum(comum com);
char* daLogin(comum com);
char* daNome(comum com);
char* daUniversidade(comum com);

#endif