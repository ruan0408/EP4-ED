/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#ifndef LISTA_SENT_H_INCLUDED
#define LISTA_SENT_H_INCLUDED
#include "utils.h"

/*Lista encadeada de Sentencas*/
typedef struct
{
    char *id, *sent, *anot;
} Sentenca;

typedef struct celula_sent
{
    Sentenca sent;
    struct celula_sent *prox;
} Celula_sent;

Celula_sent *lista_sent_init();
Celula_sent *cria_cel_sent();
Celula_sent *remove_cel_sent(Celula_sent *cel);
int lista_sent_vazia(Celula_sent *cabLista);
void insere_cel_sent(Celula_sent *cel, Celula_sent *cabLista);
void free_lista_sent(Celula_sent *cab);

#endif /* LISTA_SENT_H_INCLUDED*/
