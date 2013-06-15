/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#include<stdlib.h>
#include<stdio.h>
#include "Lista_sent.h"

/** =====================================================================================**/
/** =====================================================================================**/

/*Cria a cabeça de uma lista*/
Celula_sent *lista_sent_init()
{
    Celula_sent *cab = mallocSafe(sizeof(*cab));
    cab->prox = NULL;
    return cab;
}
/** =====================================================================================**/
/** =====================================================================================**/

/*Cria uma celula*/
Celula_sent *cria_cel_sent(Sentenca sent)
{
    Celula_sent *nova = mallocSafe(sizeof(*nova));
    nova->sent = sent;
    nova->prox = NULL;
    return nova;
}
/** =====================================================================================**/
/** =====================================================================================**/

/*Remove cel->prox de sua lista e retorna seu endereço*/
Celula_sent *remove_cel_sent(Celula_sent *cel)
{
    Celula_sent *aux;
    aux = cel->prox;
    cel->prox = cel->prox->prox;
    return aux;
}
/** =====================================================================================**/
/** =====================================================================================**/

/*Verifica se a lista esta vazia*/
int lista_sent_vazia(Celula_sent *cabLista)
{
    if(cabLista->prox == NULL) return TRUE;
    return FALSE;
}
/** =====================================================================================**/
/** =====================================================================================**/

/*Adiciona cel à lista cabLista*/
void insere_cel_sent(Celula_sent *cel, Celula_sent *cabLista)
{
    cel->prox = cabLista->prox;
    cabLista->prox = cel;
}
/** =====================================================================================**/
/** =====================================================================================**/

/*Libera a memoria ocupada por uma lista*/
void free_lista_sent(Celula_sent *cab)
{
    while(!lista_sent_vazia(cab))
        free(remove_cel_sent(cab));

    free(cab);
    cab = NULL;
}

