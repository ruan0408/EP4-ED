/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"

static int p[] =
{
    251,
    509,
    1021,
    2039,
    4093,
    8191,
    16381,
    32749,
    65521,
    131071,
    262139,
    524287,
    1048573,
    2097143,
    4194301,
    8388593,
    16777213,
    33554393,
    67108859,
    134217689,
    268435399,
    536870909,
    1073741789,
    2147483647
};

void *mallocSafe(size_t n)
{
    void *pt;
    pt = malloc(n);
    if (pt == NULL)
    {
        printf("ERRO na alocacao de memoria.\n\n");
        exit(-1);
    }
    return pt;
}

int prime_m(int m)
{
    int x;
    x = log(m)/log(2.0) + 1;
    if (x < 8)
        return p[0];
    else
        return p[x - 8];
}

int hash(char *v, int M)
{
    int h = 0, a = 127;
    for (; *v != '\0' && *v != ']' && *v != ' '; v++)
        h = (a*h + *v) % M;
    return h;
}

/*Verifica se token é uma palavra*/
int ePalavra(char *token)
{
    int i;
    for(i = 0; token[i] != ' ' && token[i] != ']'; i++)
        if(token[i] < 'A' || (token[i] > 'Z' && token[i] < 'a') || token[i] > 'z')return FALSE;
    return TRUE;
}
/*Printa token*/
void printToken(char* tok)
{
    int i;
    for(i = 0; tok[i] != ' '; i++)
        putchar(tok[i]);
}
/*Printa lema*/
void printLema(char* lema)
{
    int i;
    for(i = 0; lema[i] != ']'; i++)
        putchar(lema[i]);
}

int str_cmp(char *v1, char *v2)
{
    int flag1, flag2;
    int i = 0;
    while(v1[i] != ' ' && v2[i] != ' ' && v1[i] != '\0' && v2[i] != '\0'  && v1[i] != ']' && v2[i] != ']' && v1[i] == v2[i])i++;
    flag1 = (v1[i] == ' ' || v1[i] == '\0' || v1[i] == ']');
    flag2 = (v2[i] == ' ' || v2[i] == '\0' || v2[i] == ']');

    if(flag1 && flag2) return 0;
    if(flag1 && !flag2) return -1;
    if(!flag1 && flag2) return 1;
    if(v1[i] < v2[i]) return -1;
    return 1;
}

