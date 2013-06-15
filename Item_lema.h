/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#ifndef ITEM_LEMA_H_INCLUDED
#define ITEM_LEMA_H_INCLUDED

#include "Lista_pal.h"

/*Tipo das keys de T2*/
typedef char* Key_lema;

/*Item suportado por T2*/
typedef struct
{
    char *lema;
    Celula_pal *cab;
} Item_lema;

Key_lema key_lema(Item_lema item);
int less_lema(Key_lema a, Key_lema b);
int eq_lema(Key_lema a, Key_lema b);
void visit_list_palavras(Item_lema item);
void visit_lema(Item_lema item);
void item_lema_free(Item_lema item);

#endif /* ITEM_LEMA_H_INCLUDED*/
