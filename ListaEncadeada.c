#include "ListaEncadeada.h"
#include <stdio.h>
#include <stdlib.h>

/* Inicializa uma lista - já alocando a célula cabeça */
void inicializaLista (TLista *Lista) {
    Lista->primeiro = Lista->ultimo = (TCelula *)malloc(sizeof(TCelula));
    Lista->primeiro->prox = NULL;
    Lista->tamanho = 0;
}

/* Insere uma celula na lista */
void insereCelulaEmLista (TLista *Lista, TCelula *celula) {
    Lista->ultimo->prox = celula;
    Lista->ultimo = celula;
    Lista->tamanho++;
}
/* Insere um item na lista */
void insereLista (TLista *Lista, TItem *item) {
    TCelula *aux;
    aux = (TCelula *)malloc(sizeof(TCelula));
    aux->item = *item;
    Lista->ultimo->prox = aux;
    Lista->ultimo = aux;
    Lista->tamanho++;
}

/* Imprime as palavras contidas na lista */
void imprimeListaDePalavras (TLista *Lista) {
    TCelula *aux;
    aux = Lista->primeiro->prox;

    while (aux != NULL) {
        if(aux == Lista->ultimo)
            printf("%s\n", aux->palavra);
        /* Imprime "->" no final do par ordenado */
        else
            printf("%s -> ", aux->palavra);

        aux = aux->prox;
    }
}
/* Imprime o par ordenado (qtde,idDoc) */
void imprimeLista (TLista *Lista) {
    TCelula *aux;
    aux = Lista->primeiro->prox;

    while (aux != NULL) {
        if(aux->prox == NULL)
            printf("<%d,%d>\n", aux->item.termo.qtde, aux->item.termo.idDoc);
        /* Imprime "->" no final do par ordenado */
        else
            printf("<%d,%d> -> ", aux->item.termo.qtde, aux->item.termo.idDoc);

        aux = aux->prox;
    }
}
