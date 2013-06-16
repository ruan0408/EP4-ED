/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "t1.h"
#include "utils.h"

/*Estrutura pega do site do Yoshi. Levemente alterada*/
/*TABELA DE ESPALHAMENTO COM RESOLUÇÃO DE COLISÕES POR LINEAR PROBING*/

#define o ++n_probes
#define null(A) (st_pal[A].palavra == NULLitem_pal.palavra)
#define onull(A) (o, st_pal[A].palavra == NULLitem_pal.palavra)

static int N, M;
static long n_probes=0, n_probes_hit=0, n_probes_miss=0;
static Item_pal *st_pal;

Item_pal NULLitem_pal;

Item_pal st_pal_get_NULLitem()
{
    NULLitem_pal.palavra = NULL;
    NULLitem_pal.cab = NULL;
    NULLitem_pal.lema = NULL;
    return NULLitem_pal;
}

/*Inicia tabela com M primo pequeno e arbitrrio*/
void st_pal_init()
{
    int i;
    N = 0;
    M = 1021;
    st_pal = mallocSafe(M*sizeof(Item_pal));
    for (i = 0; i < M; i++) st_pal[i] = NULLitem_pal;
}

/*Numero de elementos na tabela*/
int st_pal_count()
{
    return N;
}

/*Função que torna o hash dinamico.
   Dobra o tamanho da tabela e reinsere os elementos*/
static void reHash()
{
    int K, i;
    Item_pal *aux;
    K = prime_m(2*M);
    aux = mallocSafe(K*sizeof(Item_pal));
    for (i = 0; i < K; i++) aux[i] = NULLitem_pal;

    for (i = 0; i < M; i++)
        if(!null(i))
        {
            int h = hash(key_pal(st_pal[i]), K);
            while (aux[h].palavra != NULLitem_pal.palavra) h = (h+1) % K;
            aux[h] = st_pal[i];
        }

    free(st_pal);
    st_pal = aux;
    aux = NULL;
    M = K;
}

/*Insere um item na tabela, se preciso, aumenta ela*/
void st_pal_insert(Item_pal item)
{
    Key_pal v;
    int i;
    if(1.0*N/M > 0.5) reHash();
    v = key_pal(item);
    i = hash(v, M);
    while (!null(i)) i = (i+1) % M;
    st_pal[i] = item;
    N++;
}

/*Procura chave na tabela*/
Item_pal st_pal_search(Key_pal v)
{
    int i = hash(v, M);
    int t = n_probes;
    while (!onull(i))
        if (eq_pal(v, key_pal(st_pal[i])))
        {
            n_probes_hit+=n_probes-t;
            return st_pal[i];
        }
        else i = (i+1) % M;
    n_probes_miss+=n_probes-t;
    return NULLitem_pal;
}

/*Deleta um item da tabela. É necessario reinserção.*/
void st_pal_delete(Item_pal item)
{
    int j, i = hash(key_pal(item), M);
    Item_pal v;
    while (!null(i))
        if (eq_pal(key_pal(item), key_pal(st_pal[i]))) break;
        else i = (i+1) % M;
    if (null(i)) return;
    st_pal[i] = NULLitem_pal;
    N--;
    for (j = i+1; !null(j); j = (j+1) % M, N--)
    {
        v = st_pal[j];
        st_pal[j] = NULLitem_pal;
        st_pal_insert(v);
    }
}

/*Executa a função visit em cada item da tabela*/
void st_pal_dump(void (*visit)(Item_pal))
{
    int i;
    for (i = 0; i < M; i++)
        if(!null(i)) visit(st_pal[i]);
}

/*Executa a função visit em cada item, sendo que eles estão ordenados*/
void st_pal_sort(void (*visit)(Item_pal))
{
    int i, j;
    Item_pal *v = mallocSafe(N*sizeof(Item_pal));

    for (j = 0, i = 0; i < M; i++)
        if (!null(i)) v[j++] = st_pal[i];

    qsort(v, N, sizeof(Item_pal), pal_cmp);
    for(i = 0; i < N; i++)
        visit(v[i]);
    free(v);
}

/*Libera espaço ocupado pela tabela e por seus items*/
void st_pal_free()
{
    int i;
    for (i = 0; i < M; i++)
        if(!null(i)) item_pal_free(st_pal[i]);

    free(st_pal);
    st_pal = NULL;
}
