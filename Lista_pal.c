/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#include<stdlib.h>
#include<stdio.h>
#include "Lista_pal.h"

/** =====================================================================================**/
/** =====================================================================================**/

/*Cria a cabeça de uma lista*/
Celula_pal *lista_pal_init()
{
    Celula_pal *cab = mallocSafe(sizeof(*cab));
    cab->prox = NULL;
    return cab;
}
/** =====================================================================================**/
/** =====================================================================================**/

/*Cria uma celula*/
Celula_pal *cria_cel_pal(char *pal)
{
    Celula_pal *nova = mallocSafe(sizeof(*nova));
    nova->pal = pal;
    nova->prox = NULL;
    return nova;
}
/** =====================================================================================**/
/** =====================================================================================**/

/*Remove cel->prox de sua lista e retorna seu endereço*/
Celula_pal *remove_cel_pal(Celula_pal *cel)
{
    Celula_pal *aux;
    aux = cel->prox;
    cel->prox = cel->prox->prox;
    return aux;
}
/** =====================================================================================**/
/** =====================================================================================**/

/*Verifica se a lista esta vazia*/
int lista_pal_vazia(Celula_pal *cabLista)
{
    if(cabLista->prox == NULL) return TRUE;
    return FALSE;
}
/** =====================================================================================**/
/** =====================================================================================**/

/*Adiciona cel à lista cabLista*/
void insere_cel_pal(Celula_pal *cel, Celula_pal *cabLista)
{
    cel->prox = cabLista->prox;
    cabLista->prox = cel;
}
/** =====================================================================================**/
/** =====================================================================================**/

/*Libera a memoria ocupada por uma lista*/
void free_lista_pal(Celula_pal *cab)
{
    while(!lista_pal_vazia(cab))
        free(remove_cel_pal(cab));

    free(cab);
    cab = NULL;
}

