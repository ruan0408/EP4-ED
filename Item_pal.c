/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#include <stdio.h>
#include <string.h>
#include "Item_pal.h"

/*Retorna o key de um item de T1*/
Key_pal key_pal(Item_pal item)
{
    return item.palavra;
}

/*Verifica se a < b*/
int less_pal(Key_pal a, Key_pal b)
{
    int i = 0;
    while(a[i] != ' ' && b[i] != ' ' && a[i] != '\0' && b[i] != '\0' && a[i] == b[i])i++;
    if((a[i] == ' ' || a[i] == '\0') && (b[i] == ' ' || b[i] == '\0')) return FALSE;
    return a[i] < b[i];
}

/*Verifica se a == b*/
int eq_pal(Key_pal a, Key_pal b)
{
    int i = 0;
    while(a[i] != ' ' && b[i] != ' ' && a[i] != '\0' && b[i] != '\0' && a[i] == b[i])i++;
    if((a[i] == ' ' || a[i] == '\0') && (b[i] == ' ' || b[i] == '\0')) return TRUE;
    return FALSE;
}

/*Printa uma frase*/
void printSent(char* sent)
{
    int i;
    for(i = 0; sent[i] != '[' || sent[i+1] != 'T' || sent[i+2] != 'e' ||
            sent[i+3] != 'x' || sent[i+4] != 't' || sent[i+5] != '='; i++)
        putchar(sent[i]);
}
/*Printa o ID de uma sentença*/
void printSentID(char* id)
{
    int i;
    for(i = 0; id[i] != '\n' ; i++)
        putchar(id[i]);
}
/*Printa a sentença anotada*/
void printSentAnot(char* anot)
{
    int i;
    for(i = 0; anot[i] != ' ' || anot[i+1] != '\n' ; i++)
        putchar(anot[i]);
}
/*Printa o token de item*/
void visit_tokens(Item_pal item)
{
    printToken(item.palavra);
    printf("\n");
}
/*Printa palavras*/
void visit_palavras(Item_pal item)
{
    if(ePalavra(item.palavra))
    {
        printToken(item.palavra);
        printf("\n");
    }
}
/*Libera espaço ocupado por item*/
void item_pal_free(Item_pal item)
{
    free_lista_sent(item.cab);
}
