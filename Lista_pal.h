/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#ifndef LISTA_PAL_H_INCLUDED
#define LISTA_PAL_H_INCLUDED
#include "utils.h"

/*Lista encadeada de palavras (tokens)*/

typedef struct celula_pal
{
    char *pal;
    struct celula_pal *prox;
} Celula_pal;

Celula_pal *lista_pal_init();
Celula_pal *cria_cel_pal();
Celula_pal *remove_cel_pal(Celula_pal *cel);
int lista_pal_vazia(Celula_pal *cabLista);
void insere_cel_pal(Celula_pal *cel, Celula_pal *cabLista);
void free_lista_pal(Celula_pal *cab);


#endif /* LISTA_PAL_H_INCLUDED*/
