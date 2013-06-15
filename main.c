/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/

#include <stdio.h>
#include <stdlib.h>
#include "t1.h"
#include "t2.h"
#include "getLine.h"

#define TAM_ENTRADA 100

void palavrasDistintas(Item_pal item);
int estaNaLista(char *token, Celula_pal *cab);
int sent_id_iguais(char* a, char* b);
void processaTexto(char* buffer);
FILE* abreArquivo(int argc, char** argv);

/*Variaveis das estatisticas do texto*/
int totPalDist, totSent, totToken, totPal;

int main(int argc, char* argv[])
{
    FILE *arq;
    char*buffer, *str, *token, *palavra;
    int e, a, ev, eV, av, aV, F, s, d, l, L, t,  i;
    Item_pal aux, NULLitem_pal;
    Item_lema aux2;
    NULLitem_pal = st_pal_get_NULLitem();

    /*Valor inicial das variaveis estatisticas*/
    totPalDist = totToken = totPal = totSent = 0;

    /*Deixa o arquivo passado pela linha de comando pronto para ser lido*/
    arq = abreArquivo(argc, argv);

    /*Carrega todo o texto na string buffer e poe um '\0' no final*/
    buffer = getLine(arq);

    /*Inicia T1 e T2*/
    st_pal_init();
    st_lema_init();

    /*Carrega T1 e T2*/
    processaTexto(buffer);
    /*==========================PRÉ-PROCESSAMENTO FEITO===========================================*/
    str = mallocSafe(TAM_ENTRADA*sizeof(*str));
    while(TRUE)
    {
        printf("Digite suas opções:\n");
        printf(">");
        palavra = NULL;
        /*Pega opçoes*/
        e = a = ev = eV = av = aV = F = s = d = l = L = t = FALSE;
        for(i = 0; i < TAM_ENTRADA; i++)str[i] = '-';/*Limpa str*/
        if(fgets(str, TAM_ENTRADA, stdin) == NULL)
        {
            printf("Um erro inesperado ocorreu =/ \n");
            exit(-1);
        }
        else
        {
            token = strtok(str, " -\n");
            while(token != NULL)
            {
                if(strcmp(token, "a") == 0)a = TRUE;
                else if(strcmp(token, "e") == 0)e = TRUE;
                else if(strcmp(token, "av") == 0)av = TRUE;
                else if(strcmp(token, "aV") == 0)aV = TRUE;
                else if(strcmp(token, "ev") == 0)ev = TRUE;
                else if(strcmp(token, "eV") == 0)eV = TRUE;
                else if(strcmp(token, "L") == 0)L = TRUE;
                else if(strcmp(token, "l") == 0)l = TRUE;
                else if(strcmp(token, "t") == 0)t = TRUE;
                else if(strcmp(token, "F") == 0)F = TRUE;
                else if(strcmp(token, "s") == 0)s = TRUE;
                else if(strcmp(token, "d") == 0)d = TRUE;

                token = strtok(NULL, " -\n");
                if(token != NULL)palavra = token;
            }

            if(L || l || t || s || d || F)
            {
                if(L)
                {
                    printf("Lista com todos os lemas que são palavras e suas respectivas palavras: \n");
                    st_lema_sort(visit_list_palavras);
                    printf("\n");
                }
                if(l)
                {
                    printf("Lista com todos os lemas que são palavras: \n");
                    st_lema_sort(visit_lema);
                }
                if(t)
                {
                    printf("Lista com todos os tokens: \n");
                    st_pal_sort(visit_tokens);
                }
                if(d)
                {
                    printf("Lista com todas as palavras: \n");
                    st_pal_sort(visit_palavras);
                }
                if(s)
                {
                    printf("\nNumero total de tokens: %d\n", totToken);
                    printf("Numero total de palavras: %d\n", totPal);
                    printf("Numero total de sentenças: %d\n", totSent);
                    printf("Numero de tokens distintos: %d\n", st_pal_count());
                    totPalDist = 0;
                    st_pal_dump(palavrasDistintas);
                    printf("Numero de palavras distintas: %d\n", totPalDist);
                    printf("Numero de lemas distintos: %d\n", st_lema_count());
                }
                if(F)/*Desaloca-se tudo para poder encerrar o programa*/
                {
                    st_pal_free();
                    st_lema_free();
                    free(buffer);
                    free(str);
                    fclose(arq);
                    return 0;
                }
            }
            else if(palavra == NULL)printf("Entrada invalida\n");
            else
            {
                /*Procura-se a palavra em T1*/
                aux = st_pal_search(palavra);
                if(aux.palavra == NULLitem_pal.palavra)printf("A palavra não ocorre no texto\n");
                else
                {
                    Celula_pal *p;
                    Celula_sent *q;
                    /*Procuramos o lema da palavra achada em T2*/
                    aux2 = st_lema_search(aux.lema);
                    for(p = aux2.cab->prox; p != NULL; p = p->prox)
                    {
                        /*Dependendo das opçoes, imprimimos ou nao todas as variantes*/
                        if(!(e || ev || eV) || eq_pal(p->pal,palavra))
                        {
                            /*Procuramos em T1 novamente as sentenças da palavra atual*/
                            aux = st_pal_search(p->pal);
                            for(q = aux.cab->prox; q != NULL; q = q->prox)
                            {
                                printf("\n");
                                if(av || ev || aV || eV)printSentID(q->sent.id);/*Imprime a ID da sentença*/
                                printf("\n");
                                printSent(q->sent.sent);/*Imprime a sentença em si*/
                                printf("\n");
                                if(aV || eV)printSentAnot(q->sent.anot);/*Imprime a sentença anotada*/
                                printf("\n");
                            }
                        }
                        else continue;
                    }
                }
            }
        }
    }
    return 0;
}
/*Função 'visit', que incrementa o contador de palavras distintas*/
void palavrasDistintas(Item_pal item)
{
    if(ePalavra(item.palavra))totPalDist++;
}

/* Verifica se token está na lista de palavras cuja cabeça é cab */
int estaNaLista(char *token, Celula_pal *cab)
{
    Celula_pal *p;
    for(p = cab->prox; p != NULL; p = p->prox)
        if(eq_pal(p->pal, token))return TRUE;
    return FALSE;
}

/*Verifica se o ID de duas sentenças sao iguais*/
int sent_id_iguais(char* id1, char* id2)
{
    int i;
    for(i = 0; id1[i] != '\n'; i++)
        if(id1[i] != id2[i]) return FALSE;
    return TRUE;
}
/*Função para a abertura do arquivo*/
FILE* abreArquivo(int argc, char** argv)
{
    int i;
    FILE *arq = NULL;

    for(i = 0; i < argc; i++)
        if(argv[i][0] == '-' && argv[i][1] == 'f')
            arq = fopen(argv[i]+2, "r");

    if(arq == NULL)
    {
        printf("Erro na leitura\n");
        exit(-1);
    }
    return arq;
}
/*Função que processa o texto armazenado em buffer, deixando as arvores T1 e T2 prontas para serem usadas*/
void processaTexto(char* buffer)
{
    int i;
    Item_pal novo_item_pal, aux, NULLitem_pal;
    Item_lema novo_item_lema, aux2, NULLitem_lema;
    Sentenca novaSent;
    char *palavra;

    NULLitem_pal = st_pal_get_NULLitem();
    NULLitem_lema = st_lema_get_NULLitem();
    for(i = 0; buffer[i] != '\0'; i++)
    {
        /*Guarda o endereço do inicio do ID da sentença*/
        novaSent.id = &buffer[i];

        /*Corre o texto até chegar na frase*/
        while(buffer[i] != '\n')i++;
        i++;

        /*Atualiza contador de sentenças e guarda endereço do inicio da frase*/
        totSent++;
        novaSent.sent = &buffer[i];

        /*Corre o texto até chegar na sentença anotada*/
        while(buffer[i] != '[' || buffer[i+1] != 'T' || buffer[i+2] != 'e' || buffer[i+3] != 'x' || buffer[i+4] != 't' || buffer[i+5] != '=')i++;

        /*Guarda endereço do inicio da sentença anotada*/
        novaSent.anot = &buffer[i];

        /*Análise léxica da sentença anotada*/
        for (; buffer[i] != '\n' && buffer[i] != '\0'; i++)
        {
            /*Estamos em '[', pulamos 6 casas para chegar no inicio do token*/
            i+=6;

            /*Guardamos o endereço do inicio do token
               e incrementamos o contador de tokens*/
            novo_item_pal.palavra = &buffer[i];
            palavra = &buffer[i];
            totToken++;

            /*Se o token for uma palavra, incrementamos o contador de palavras*/
            if(ePalavra(palavra))totPal++;

            /* Avançamos até 'L' de 'Lemma' e pulamos 6 casas, para chegar
                no inicio do lema */
            while(buffer[i] != 'L' || buffer[i-1] != ' ')i++;
            i+=6;

            /*Guardamos o endereço do inicio do lema*/
            novo_item_pal.lema = &buffer[i];
            novo_item_lema.lema = &buffer[i];

            /*Procuramos o token em T1 e o inserimos caso ele nao esteja lá,
                Junto com sua respectiva sentença*/
            aux = st_pal_search(key_pal(novo_item_pal));
            if(aux.palavra == NULLitem_pal.palavra)
            {
                Celula_sent *novaCel = cria_cel_sent(novaSent);
                novo_item_pal.cab = lista_sent_init();

                insere_cel_sent(novaCel, novo_item_pal.cab);
                st_pal_insert(novo_item_pal);
            }
            /* Caso o token ja esteja em T1, inserimos a sentença se, e somente se,
                ela já nao estiver la. */
            else
            {
                if(!sent_id_iguais(novaSent.id, aux.cab->prox->sent.id))
                {
                    Celula_sent *novaCel = cria_cel_sent(novaSent);
                    insere_cel_sent(novaCel, aux.cab);
                }
            }
            /*Inserimos o lema em T2 caso ele nao exista, e colocamos
               palavra em sua lista de palavras*/
            aux2 = st_lema_search(key_lema(novo_item_lema));
            if(aux2.lema == NULLitem_lema.lema)
            {
                Celula_pal *novaCel = cria_cel_pal(palavra);
                novo_item_lema.cab = lista_pal_init();

                insere_cel_pal(novaCel, novo_item_lema.cab);
                st_lema_insert(novo_item_lema);
            }
            /*Se o lema ja existir colocamos a palavra em sua lista, se
               e somente se, ela ainda nao esta na lista*/
            else
            {
                if(!estaNaLista(palavra, aux2.cab))
                {
                    Celula_pal *novaCel = cria_cel_pal(palavra);
                    insere_cel_pal(novaCel, aux2.cab);
                }
            }
            /*Avançamos até o ' ' depois de ']' */
            while(buffer[i] != ']' || buffer[i+1] != ' ')i++;
            i++;
        }
    }
}
