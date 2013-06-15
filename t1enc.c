/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "t1.h"
#include "utils.h"

/*Estrutura pega do site do Yoshi. Levemente alterada*/

typedef struct st_pal_node *link;
struct st_pal_node
{
    Item_pal item;
    link next;
};

static link *heads, z;
static int N, M;

static Item_pal NULLitem_pal;

Item_pal st_pal_get_NULLitem()
{
    NULLitem_pal.palavra = NULL;
    NULLitem_pal.cab = NULL;
    NULLitem_pal.lema = NULL;
    return NULLitem_pal;
}

static link NEW(Item_pal item, link next)
{
    link x = mallocSafe(sizeof *x);
    x->item = item;
    x->next = next;
    return x;
}

int st_pal_count()
{
    return N;
}

#define hash(v,M) (hash(v,M))

void st_pal_init(int max)
{
    int i;
    N = 0;
    M = 1021;
    heads = mallocSafe(M*sizeof(link));
    z = NEW(NULLitem_pal, NULL);
    for (i = 0; i < M; i++) heads[i] = z;
}

static Item_pal searchR(link t, Key_pal v)
{
    if (t == z) return NULLitem_pal;
    if (eq_pal(key_pal(t->item), v)) return t->item;
    return searchR(t->next, v);
}

Item_pal st_pal_search(Key_pal v)
{
    return searchR(heads[hash(v, M)], v);
}

static void reHash()
{
    int K, i;
    link *aux, t;
    K = prime_m(2*M);
    aux = mallocSafe(K*sizeof(link));
    for (i = 0; i < K; i++) aux[i] = z;

    for (i = 0; i < M; i++)
        while ((t = heads[i]) != z)
        {
            int h = hash(key_pal(t->item), K);
            heads[i] = heads[i]->next;
            t->next = aux[h];
            aux[h] = t;
        }
    free(heads);
    heads = aux;
    aux = NULL;
    M = K;
 }

void st_pal_insert(Item_pal item)
{
    int i;
    if(1.0*N/M > 0.5) reHash();
    i = hash(key_pal(item), M);
    heads[i] = NEW(item, heads[i]);
    N++;
}

void st_pal_dump(void (*visit)(Item_pal))
{
    int i;
    link t;

    for (i=0; i<M; i++)
        if (heads[i] != z)
            for (t = heads[i]; t != z; t = t->next)
                visit(t->item);
}

/*void st_pal_show_histogram()
{
    int i, j, no_per_list, max_list = -1;
    link t;

    for (i=0; i<M; i++)
    {
        printf("\n+ list %d: ", i);
        for (no_per_list=0, t = heads[i]; t != z; no_per_list++, t = t->next);
        printf("[%d] ", no_per_list);
        j = no_per_list;
        while (j-- > 0)
            printf("*");
        if (no_per_list>max_list) max_list=no_per_list;
    }

    printf("\nMax no. of items in the lists: %d\n", max_list);
    printf("Average no. of items in the lists: %g\n\n", (double)N/M);
}*/
