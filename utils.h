/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#ifndef H_UTILS_DEFINED
#define H_UTILS_DEFINED

/* Macros práticas para todo programa */
#define TRUE  1
#define FALSE 0

/* Malloc que checa se o retorno é NULL */
void *mallocSafe(size_t n);
int prime_m(int m);
int hash(char *v, int M);
int ePalavra(char *token);
void printToken(char* pal);
void printLema(char* lema);

#endif
