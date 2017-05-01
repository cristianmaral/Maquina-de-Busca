#ifndef PATRICIA_H_INCLUDED
#define PATRICIA_H_INCLUDED

#include "ListaEncadeada.h"

#define TRUE 1
#define FALSE 0

typedef enum {
  Interno, Externo
} TipoNo;

/* Estrutura de um nó da árvore Patricia */
typedef struct TipoPatNo {
    TipoNo nt; /* Interno ou Externo */
    union {
        /* Estrutura de um nó interno */
        struct {
            short Index;
            char Caractere;
            struct TipoPatNo *Esq, *Dir; /* Apontadores para o filho à esquerda e o filho à direita, respectivamente */
        } NInterno;
        char Chave[50]; /* Palavra do nó externo */
    } NO;
    /* Cada nó externo possui uma lista encadeada */
    struct {
        TLista Lista;
        int tamanho;
    } NoLista;
} TipoPatNo;

void inicializaPatricia (TipoPatNo **raiz);
char Caractere (short i, char *k);
unsigned int MenorIgual (char a, char b);
unsigned int ConfereTipoNo (TipoPatNo *no);
/* Funções para criação de nós da árvore Patricia */
TipoPatNo* CriaNoInt (short i, TipoPatNo **Esq,  TipoPatNo **Dir, char Caractere);
TipoPatNo* CriaNoExt (char *k, int idDoc);
/* Função de pesquisa */
void pesquisaPatricia (char *k, TipoPatNo *t, int idDoc);

/* Funções para inserir uma palavra na árvore Patricia */
TipoPatNo* InsereEntre (char *k, TipoPatNo **t, short i, int idDoc);
TipoPatNo* InserePatricia (char *k, TipoPatNo **t, int idDoc); /* A função Insere encapsula a função InsereEntre */

void imprimePatricia (TipoPatNo *no);

#endif // PATRICIA_H_INCLUDED

