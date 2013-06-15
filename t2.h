/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#ifndef st_lema_H_INCLUDED
#define st_lema_H_INCLUDED
#include "Item_lema.h"

Item_lema st_lema_get_NULLitem();/*Retorna no NULLitem de T2*/
void st_lema_init();
int st_lema_count();
void st_lema_insert(Item_lema);
Item_lema st_lema_search(Key_lema);
void st_lema_sort(void (*visit)(Item_lema));
/*Item_lema st_lema_select(int);
void st_lema_show_histogram();*/
void st_lema_dump(void (*visit)(Item_lema));
void st_lema_free();

#endif /* st_lema_H_INCLUDED*/
