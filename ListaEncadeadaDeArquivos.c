#include <stdio.h>
#include <stdlib.h>
#include "ListaEncadeadaDeArquivos.h"

/* Ordena a Lista de Arquivos de acordo com a relevância - decrescentemente */
void OrdenaListaArquivos (TLista *ListaArquivos) {
    TCelula *aux, *aux2;
    TItem item;

    aux = ListaArquivos->primeiro->prox;
    if(aux == NULL || aux->prox == NULL)
        return;

    while(aux != NULL) {
        aux2 = aux->prox;
        while(aux2 != NULL) {
            if(aux2->item.arq.relevancia > aux->item.arq.relevancia) {
                item = aux->item;
                aux->item = aux2->item;
                aux2->item = item;
            }
            aux2 = aux2->prox;
        }
        aux = aux->prox;
    }
}

/* Função utilizada reordenar a lista de arquivos por ordem de idDoc após uma busca */
void ReordenaListaArquivos (TLista *ListaArquivos) {
    TCelula *aux, *aux2;
    TItem item;

    aux = ListaArquivos->primeiro->prox;
    if(aux == NULL || aux->prox == NULL)
        return;

    while(aux != NULL) {
        aux2 = aux->prox;
        while(aux2 != NULL) {
            if(aux2->item.arq.idDoc < aux->item.arq.idDoc) {
                item = aux->item;
                aux->item = aux2->item;
                aux2->item = item;
            }
            aux2 = aux2->prox;
        }
        aux = aux->prox;
    }
}
