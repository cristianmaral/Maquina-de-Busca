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
	    int termos_distintos;
	    int idDoc;
	    float relevancia;
            char nome_arquivo[50]; /* String utilizada para guardar o nome do arquivo */
        } arq;
    };
} TItem;

/* Estrutura de uma célula */
typedef struct Celula {
	union{
		char* palavra;
		TItem item;
	};
	struct Celula *prox;
} TCelula;

/* Estrutura da Lista Encadeada */
typedef struct {
    TCelula *primeiro; /* Ponteiro para a célula cabeça  */
    TCelula *ultimo; /* Ponteiro para a última célula da lista */
    int tamanho; /* Tamanho da lista */
} TLista;

void inicializaLista (TLista *Lista);
void insereLista (TLista *Lista, TItem *item);
void insereCelulaEmLista (TLista *Lista, TCelula *celula);
void imprimeLista(TLista *Lista);
void imprimeListaDePalavras (TLista *Lista);
#endif // LISTAENCADEADA_H_INCLUDED
