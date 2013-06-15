/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "t2.h"
#include "utils.h"

/*Estrutura pega do site do Yoshi. Levemente alterada*/

typedef struct st_lema_node *link;
struct st_lema_node
{
    Item_lema item;
    link next;
};

static link *heads, z;
static int N, M;

static Item_lema NULLitem_lema;

Item_lema st_lema_get_NULLitem()
{
    NULLitem_lema.cab = NULL;
    NULLitem_lema.lema = NULL;
    return NULLitem_lema;
}

static link NEW(Item_lema item, link next)
{
    link x = mallocSafe(sizeof *x);
    x->item = item;
    x->next = next;
    return x;
}

int st_lema_count()
{
    return N;
}

#define hash(v,M) (hash(v,M))

void st_lema_init(int max)
{
    int i;
    N = 0;
    M = 1021;
    heads = mallocSafe(M*sizeof(link));
    z = NEW(NULLitem_lema, NULL);
    for (i = 0; i < M; i++) heads[i] = z;
}

static Item_lema searchR(link t, Key_lema v)
{
    if (t == z) return NULLitem_lema;
    if (eq_lema(key_lema(t->item), v)) return t->item;
    return searchR(t->next, v);
}

Item_lema st_lema_search(Key_lema v)
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
            int h = hash(key_lema(t->item), K);
            heads[i] = heads[i]->next;
            t->next = aux[h];
            aux[h] = t;
        }
    free(heads);
    heads = aux;
    aux = NULL;
    M = K;
}

void st_lema_insert(Item_lema item)
{
    int i;
    if(1.0*N/M > 0.5) reHash();
    i = hash(key_lema(item), M);
    heads[i] = NEW(item, heads[i]);
    N++;
}

void st_lema_dump(void (*visit)(Item_lema))
{
    int i;
    link t;

    for (i=0; i<M; i++)
        if (heads[i] != z)
            for (t = heads[i]; t != z; t = t->next)
                visit(t->item);
}

void st_lema_sort(void (*visit)(Item_lema))
{
    int i,j;
    link t;
    Item_lema *v = mallocSafe(N*sizeof(Item_lema));

    for (j = 0, i = 0; i < M; i++)
        if (heads[i] != z)
            for (t = heads[i]; t != z; t = t->next)
                v[j++] = t->item;

    qsort(v, N, sizeof(Item_lema), lema_cmp);
    for(i = 0; i < N; i++)
        visit(v[i]);
}

void st_lema_free()
{
    int i;
    link t;
    for (i = 0; i < M; i++)
        while ((t = heads[i]) != z)
        {
            heads[i] = heads[i]->next;
            item_lema_free(t->item);
            free(t);
        }
    free(z);
    free(heads);
    heads = NULL;
    z = NULL;
}
/*void st_lema_show_histogram()
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

