#include "TST.h"
#include <stdio.h>
#include <stdlib.h>

void inicializaTST (TipoTSTNo **raiz) { /* Inicia a árvore */
    *raiz = NULL;
}

/* Função para criar um novo nó da TST */
TipoTSTNo* novoNoTST(char caractere) {
    TipoTSTNo* aux = (TipoTSTNo*)malloc(sizeof(TipoTSTNo));
    aux->caractere = caractere;
    aux->fimString = 0;
    aux->esq = aux->meio = aux->dir = NULL;
    return aux;
}

/* Função para inserir uma nova palavra na TST */
void insereTST(TipoTSTNo** no, char *palavra)
{
    /* Primeiro Caso: Árvore está vazia */
    if (!(*no))
        *no = novoNoTST(*palavra); /* *palavra = caractere atual da palavra */

    /* Se o caractere atual da palavra for menor que o caractere do nó atual,
       então insere esta palavra na subárvore esquerda do nó atual */
    if ((*palavra) < (*no)->caractere)
        insereTST(&( (*no)->esq ), palavra);

    /* Se o caractere atual da palavra for maior que o caractere do nó atual,
       então insere esta palavra na subárvore direita do nó atual */
    else if ((*palavra) > (*no)->caractere)
        insereTST(&( (*no)->dir ), palavra);

    /* Se o caractere atual da palavra for igual ao caractere do nó atual */
    else {
        if (*(palavra+1))
            insereTST(&( (*no)->meio ), palavra+1);
        /* O último caractere da palavra */
        else
            (*no)->fimString = 1;
    }
}

/* Uma função recursiva para percorrer a TST */
void percorre (TipoTSTNo* no, char* palavra,char *prefixo, int indice,TLista *retorno)
{
    TCelula *temp = (TCelula*)malloc(sizeof(TCelula));
    temp->prox = NULL;
    temp->item.palavra = (char*)malloc(sizeof(char)*40);
    if (no)
    {
        /* Primeiro percorre a subárvore à esquerda */
        percorre(no->esq, palavra, prefixo, indice, retorno);

        /* Guarda o caractere deste nó na string palavra*/
        palavra[indice] = no->caractere;
        if (no->fimString)
        {
            palavra[indice+1] = '\0';
	    sprintf(temp->item.palavra,"%s%s",prefixo,palavra);
	    insereCelulaEmLista(retorno,temp);
        }

        /* Percorre a subárvore usando o ponteiro do meio (subárvore do meio) */
        percorre(no->meio, palavra, prefixo, indice + 1,retorno);

        /* Finalmente percorre a subárvore à direita */
        percorre(no->dir, palavra, prefixo, indice, retorno);
    }
}

/* Função principal que encapsula a função transverseTSTUtil */
void percorreTST(TipoTSTNo* no, char *prefixo,TLista *retorno) {
    char palavra[MAXTAM]; // MAXTAM definido como 50
    percorre(no, palavra, prefixo, 0, retorno);
}
