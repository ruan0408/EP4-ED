/****************************/
/** Nome: Ruan de Menezes Costa**/
/** Nº USP: 7990929                 **/
/**************************/
#ifndef GETLINE_H_INCLUDED
#define GETLINE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

/*
 * INITIAL_BUFF_SIZE -- Tamanho inicial para o buffer usado em getLine()
 */

#define INITIAL_BUFF_SIZE 100
char *getLine(FILE *stream);


#endif /* GETLINE_H_INCLUDED*/
