#ifndef TST_H_INCLUDED
#define TST_H_INCLUDED
#include "ListaEncadeada.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXTAM 50 /* Tamanho m�ximo de letras que uma palavra pode conter */

/* N� da �rvore TST */
typedef struct No
{
    char caractere;
    unsigned fimString; /* Verdadeiro se esse caractere for o �ltimo caractere de uma das palavras */
    struct No *esq, *meio, *dir; /* Apontadores para o filho da esquerda, do meio e da direita, respectivamente */
} No;
/* Fun��es TST */
void inicializaTST (No **raiz);
No * novoNoTST (char data);
void insereTST (No** no, char *palavra);
void percorre (No* no, char* palavra, char* prefixo, int indice,TLista *retorno);
void percorreTST (No* raiz, char *prefixo,TLista *retorno);
int pesquisaTST (No *no, char *palavra);
/* Fun��o da Implementa��o AutoPreenchimento */
void AutoPreenchimentoTST(No *no, int indice, char *prefixo,TLista *retorno);

#endif // TST_H_INCLUDED
