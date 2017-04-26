#ifndef TST_H_INCLUDED
#define TST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define MAX 50 /* Tamanho máximo de letras que uma palavra pode conter */

/* Nó da Árvore TST */
typedef struct No
{
    char caractere;
    unsigned fimString; /* Verdadeiro se esse caractere for o último caractere de uma das palavras */
    struct No *esq, *meio, *dir; /* Apontadores para o filho da esquerda, do meio e da direita, respectivamente */
} No;

void inicializaTST (No **raiz);
No * novoNoTST (char data);
void insereTST (No** no, char *palavra);
void percorre (No* no, char* buffer, int indice);
void percorreTST (No* raiz);
int pesquisaTST (No *no, char *palavra);

#endif // TST_H_INCLUDED
