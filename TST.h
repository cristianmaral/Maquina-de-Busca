#ifndef TST_H_INCLUDED
#define TST_H_INCLUDED
#include "ListaEncadeada.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXTAM 50 /* Tamanho m�ximo de letras que uma palavra pode conter */

/* N� da �rvore TST */
typedef struct TipoTSTNo
{
    char caractere;
    unsigned fimString; /* Verdadeiro se esse caractere for o �ltimo caractere de uma das palavras */
    struct TipoTSTNo *esq, *meio, *dir; /* Apontadores para o filho da esquerda, do meio e da direita, respectivamente */
} TipoTSTNo;
/* Fun��es TST */
void inicializaTST (TipoTSTNo **raiz);
TipoTSTNo * novoNoTST (char data);
void insereTST (TipoTSTNo** no, char *palavra);
void percorre (TipoTSTNo* no, char* palavra, char* prefixo, int indice,TLista *retorno);
void percorreTST (TipoTSTNo* raiz, char *prefixo,TLista *retorno);
int pesquisaTST (TipoTSTNo *no, char *palavra);
/* Fun��o da Implementa��o AutoPreenchimento */
void AutoPreenchimentoTST(TipoTSTNo *no, int indice, char *prefixo,TLista *retorno);

#endif // TST_H_INCLUDED
