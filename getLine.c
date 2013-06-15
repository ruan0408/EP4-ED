/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#include "getLine.h"

/*
 * GetLine(): le uma linha de stream (terminada por fim de
 * arquivo) e devolve um ponteiro para um string contendo a linha
 * lida.  Memoria é alocada dinamicamente para armazenar a linha lida.
 *
 * Obs.  Esta rotina foi copiada (com pequenas modificacoes) da pagina do prof Yoshi.
*/

char *getLine(FILE *stream)
{
    char *line, *nline;
    int n, ch, size;

    n = 0;
    size = INITIAL_BUFF_SIZE;
    line = (char *) mallocSafe(size + 1);

    while ((ch = fgetc(stream)) != EOF)
    {
        /*Quando o vetor enche, realoca-se ele*/
        if (n == size)
        {
            size *= 2;
            nline = (char *) mallocSafe(size + 1);

            strncpy(nline, line, n);
            free(line);
            line = nline;
        }
        line[n++] = ch;
    }
    if (n == 0 && ch == EOF)
    {
        free(line);
        return (NULL);
    }
    line[n] = '\0';
    nline = (char *) mallocSafe(n + 1);

    strcpy(nline, line);
    free(line);
    return nline;
}
