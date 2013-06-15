/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#ifndef ITEM_PAL_H_INCLUDED
#define ITEM_PAL_H_INCLUDED
#include <string.h>
#include "Lista_sent.h"

/*Tipo das keys de T1*/
typedef char* Key_pal;

/*Item carregado por T1*/
typedef struct
{
    char *palavra;
    char *lema;
    Celula_sent *cab;
} Item_pal;

Key_pal key_pal(Item_pal item);
int less_pal(Key_pal a, Key_pal b);
int eq_pal(Key_pal a, Key_pal b);
void printSent(char* sent);
void printSentID(char* id);
void printSentAnot(char* anot);
void visit_tokens(Item_pal item);
void visit_palavras(Item_pal item);
void item_pal_free(Item_pal item);

#endif /* ITEM_PAL_H_INCLUDED*/
