#ifndef LISTAENCADEADA_H_INCLUDED
#define LISTAENCADEADA_H_INCLUDED

#include <stdio.h>

/* Estrutura de um item - Utilizamos union para diferenciar um item da árvore Patricia de um item da Lista de Arquivos */
typedef struct {
    union {
        /* Estrutura de um item - Nó externo Patricia */
        struct {
            int qtde; /* Quantidade de ocorrências de um termo */
            int idDoc; /* Identificação do documento */
            float peso; /* Peso do termo */
        } termo;

        /* Estrutura de um item - Lista de Arquivos */
        struct {
            /* Variáveis quando estamos tratando de uma Lista de Arquivos */
            FILE *entrada; /* Variável utilizada apenas quando estamos tratando de uma Lista de Arquivos */
            char nome_arquivo[50]; /* String utilizada para guardar o nome do arquivo */
            int termos_distintos;
            int idDoc;
            float relevancia; /* Relevancia do documento de acordo com uma busca */
        } arq;
    };
} TItem;

/* Estrutura de uma célula */
typedef struct Celula {
    TItem item; /* Um item */
    struct Celula *prox; /* Ponteiro para a próxima célula */
} TCelula;

/* Estrutura da Lista Encadeada */
typedef struct {
    TCelula *primeiro; /* Ponteiro para a célula cabeça  */
    TCelula *ultimo; /* Ponteiro para a última célula da lista */
    int tamanho; /* Tamanho da lista */
} TLista;

void inicializaLista (TLista *Lista);
void insereLista (TLista *Lista, TItem *item);
void imprimeLista(TLista *Lista);

#endif // LISTAENCADEADA_H_INCLUDED
