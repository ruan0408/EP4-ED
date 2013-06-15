/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#ifndef st_pal_H_INCLUDED
#define st_pal_H_INCLUDED
#include "Item_pal.h"

Item_pal st_pal_get_NULLitem();/*Retorna no NULLitem de T1*/
void st_pal_init();
int st_pal_count();
void st_pal_insert(Item_pal);
Item_pal st_pal_search(Key_pal);
/*void st_pal_sort(void (*visit)(Item_pal));
Item_pal st_pal_select(int);
void st_pal_show_histogram();*/
void st_pal_dump(void (*visit)(Item_pal));

#endif /* st_pal_H_INCLUDED*/
