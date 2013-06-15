/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#include <stdio.h>
#include <string.h>
#include "Item_lema.h"

/*Retorna key_lema de item*/
Key_lema key_lema(Item_lema item)
{
    return item.lema;
}

/*Verifica se a < b*/
int less_lema(Key_lema a, Key_lema b)
{
    int i = 0;
    while(a[i] != ']' && b[i] != ']' && a[i] == b[i])i++;
    if(a[i] == ']' && b[i] != ']') return TRUE;
    if(a[i] != ']' && b[i] == ']') return FALSE;
    return a[i]<b[i];
}

/*Verifica se a == b*/
int eq_lema(Key_lema a, Key_lema b)
{
    int i = 0;
    while(a[i] != ']' && b[i] != ']' && a[i] == b[i])i++;
    if(a[i] == ']' && b[i] == ']') return TRUE;
    return FALSE;
}

int lema_cmp(const void* item1,const void* item2)
{
    return str_cmp((*(Item_lema*)(item1)).lema, (*(Item_lema*)(item2)).lema);
}

/*Printa a lista de palavras de item*/
void visit_list_palavras(Item_lema item)
{
    if(ePalavra(item.lema))
    {
        Celula_pal *p;
        printf("\n");
        printLema(item.lema);
        printf(": ");
        for(p = item.cab->prox; p != NULL; p = p->prox)
        {
            printf(" ");
            printToken(p->pal);
        }
    }

}
/*Printa lemas que são palavras*/
void visit_lema(Item_lema item)
{
    if(ePalavra(item.lema))
    {
        printLema(item.lema);
        printf("\n");
    }
}
/*Libera o espaço ocupado por item*/
void item_lema_free(Item_lema item)
{
    free_lista_pal(item.cab);
}
