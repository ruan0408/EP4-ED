/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "t2.h"
#include "utils.h"

/*Estrutura pega do site do Yoshi. Levemente alterada*/
/*TABELA DE ESPALHAMENTO COM RESOLUÇÃO DE COLISÕES POR LINEAR PROBING*/

#define o ++n_probes
#define null(A) (st_lema[A].lema == NULLitem_lema.lema)
#define onull(A) (o, st_lema[A].lema == NULLitem_lema.lema)

static int N, M;
static long n_probes=0, n_probes_hit=0, n_probes_miss=0;
static Item_lema *st_lema;

Item_lema NULLitem_lema;

Item_lema st_lema_get_NULLitem()
{
    NULLitem_lema.cab = NULL;
    NULLitem_lema.lema = NULL;
    return NULLitem_lema;
}

/*Inicia tabela com M primo pequeno e arbitrrio*/
void st_lema_init()
{
    int i;
    N = 0;
    M = 1021;
    st_lema = mallocSafe(M*sizeof(Item_lema));
    for (i = 0; i < M; i++) st_lema[i] = NULLitem_lema;
}

/*Numero de elementos na tabela*/
int st_lema_count()
{
    return N;
}

/*Função que torna o hash dinamico.
   Dobra o tamanho da tabela e reinsere os elementos*/
static void reHash()
{
    int K, i;
    Item_lema *aux;
    K = prime_m(2*M);
    aux = mallocSafe(K*sizeof(Item_lema));
    for (i = 0; i < K; i++) aux[i] = NULLitem_lema;

    for (i = 0; i < M; i++)
        if(!null(i))
        {
            int h = hash(key_lema(st_lema[i]), K);
            while (aux[h].lema != NULLitem_lema.lema) h = (h+1) % K;
            aux[h] = st_lema[i];
        }

    free(st_lema);
    st_lema = aux;
    aux = NULL;
    M = K;
}

/*Insere um item na tabela, se preciso, aumenta ela*/
void st_lema_insert(Item_lema item)
{
    Key_lema v;
    int i;
    if(1.0*N/M > 0.5) reHash();
    v = key_lema(item);
    i = hash(v, M);
    while (!null(i)) i = (i+1) % M;
    st_lema[i] = item;
    N++;
}

/*Procura chave na tabela*/
Item_lema st_lema_search(Key_lema v)
{
    int i = hash(v, M);
    int t = n_probes;
    while (!onull(i))
        if (eq_lema(v, key_lema(st_lema[i])))
        {
            n_probes_hit+=n_probes-t;
            return st_lema[i];
        }
        else i = (i+1) % M;
    n_probes_miss+=n_probes-t;
    return NULLitem_lema;
}
/*Deleta um item da tabela. É necessario reinserção.*/
void st_lema_delete(Item_lema item)
{
    int j, i = hash(key_lema(item), M);
    Item_lema v;
    while (!null(i))
        if (eq_lema(key_lema(item), key_lema(st_lema[i]))) break;
        else i = (i+1) % M;
    if (null(i)) return;
    st_lema[i] = NULLitem_lema;
    N--;
    for (j = i+1; !null(j); j = (j+1) % M, N--)
    {
        v = st_lema[j];
        st_lema[j] = NULLitem_lema;
        st_lema_insert(v);
    }
}

/*Executa a função visit em cada item da tabela*/
void st_lema_dump(void (*visit)(Item_lema))
{
    int i;
    for (i = 0; i < M; i++)
        if(!null(i)) visit(st_lema[i]);
}

/*Executa a função visit em cada item, sendo que eles estão ordenados*/
void st_lema_sort(void (*visit)(Item_lema))
{
    int i, j;
    Item_lema *v = mallocSafe(N*sizeof(Item_lema));

    for (j = 0, i = 0; i < M; i++)
        if (!null(i)) v[j++] = st_lema[i];

    qsort(v, N, sizeof(Item_lema), lema_cmp);
    for(i = 0; i < N; i++)
        visit(v[i]);
    free(v);
}

/*Libera espaço ocupado pela tabela e por seus items*/
void st_lema_free()
{
    int i;
    for (i = 0; i < M; i++)
        if(!null(i)) item_lema_free(st_lema[i]);

    free(st_lema);
    st_lema = NULL;
}
