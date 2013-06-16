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
/*TABELA DE ESPALHAMENTO COM RESOLUÇÃO DE COLISÕES POR ENCADEAMENTO*/

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
/*Cria novo nó da tabela*/
static link NEW(Item_pal item, link next)
{
    link x = mallocSafe(sizeof *x);
    x->item = item;
    x->next = next;
    return x;
}
/*Numero de elementos na tabela*/
int st_pal_count()
{
    return N;
}

#define hash(v,M) (hash(v,M))

/*Inicia tabela com M primo pequeno e arbitrrio*/
void st_pal_init()
{
    int i;
    N = 0;
    M = 1021;
    heads = mallocSafe(M*sizeof(link));
    z = NEW(NULLitem_pal, NULL);
    for (i = 0; i < M; i++) heads[i] = z;
}

/*Procura chave na tabela*/
static Item_pal searchR(link t, Key_pal v)
{
    if (t == z) return NULLitem_pal;
    if (eq_pal(key_pal(t->item), v)) return t->item;
    return searchR(t->next, v);
}

/*Função envelope*/
Item_pal st_pal_search(Key_pal v)
{
    return searchR(heads[hash(v, M)], v);
}

/*Função que torna o hash dinamico.
   Dobra o tamanho da tabela e reinsere os elementos*/
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
/*Insere um item na tabela, se preciso, aumenta ela*/
void st_pal_insert(Item_pal item)
{
    int i;
    if(1.0*N/M > 0.5) reHash();
    i = hash(key_pal(item), M);
    heads[i] = NEW(item, heads[i]);
    N++;
}
/*Executa a função visit em cada item da tabela*/
void st_pal_dump(void (*visit)(Item_pal))
{
    int i;
    link t;

    for (i=0; i<M; i++)
        if (heads[i] != z)
            for (t = heads[i]; t != z; t = t->next)
                visit(t->item);
}
/*Executa a função visit em cada item, sendo que eles estão ordenados*/
void st_pal_sort(void (*visit)(Item_pal))
{
    int i, j;
    link t;
    Item_pal *v = mallocSafe(N*sizeof(Item_pal));

    for (j = 0, i = 0; i < M; i++)
        if (heads[i] != z)
            for (t = heads[i]; t != z; t = t->next)
                v[j++] = t->item;

    qsort(v, N, sizeof(Item_pal), pal_cmp);
    for(i = 0; i < N; i++)
        visit(v[i]);
    free(v);
}
/*Libera espaço ocupado pela tabela e por seus items*/
void st_pal_free()
{
    int i;
    link t;
    for (i = 0; i < M; i++)
        while ((t = heads[i]) != z)
        {
            heads[i] = heads[i]->next;
            item_pal_free(t->item);
            free(t);
        }
    free(z);
    free(heads);
    heads = NULL;
    z = NULL;
}

void st_pal_show_histogram()
{
    int i, j, no_per_list, max_list = -1;
    link t;

    for (i=0; i<M; i++) {
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
}
