#include "TST.h"
#include <stdio.h>
#include <stdlib.h>

void inicializaTST (No **raiz) { /* Inicia a árvore */
    *raiz = NULL;
}

/* Função para criar um novo nó da TST */
No* novoNoTST(char caractere) {
    No* aux = (No*)malloc(sizeof(No));
    aux->caractere = caractere;
    aux->fimString = 0;
    aux->esq = aux->meio = aux->dir = NULL;
    return aux;
}

/* Função para inserir uma nova palavra na TST */
void insereTST(No** no, char *palavra)
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
void percorre (No* no, char* palavra,char *prefixo, int indice)
{
    if (no)
    {
        /* Primeiro percorre a subárvore à esquerda */
        percorre(no->esq, palavra, prefixo, indice);

        /* Guarda o caractere deste nó na string palavra*/
        palavra[indice] = no->caractere;
        if (no->fimString)
        {
            palavra[indice+1] = '\0';
            printf("%s%s\n",prefixo,palavra);
        }

        /* Percorre a subárvore usando o ponteiro do meio (subárvore do meio) */
        percorre(no->meio, palavra, prefixo, indice + 1);

        /* Finalmente percorre a subárvore à direita */
        percorre(no->dir, palavra, prefixo, indice);
    }
}

/* Função principal que encapsula a função transverseTSTUtil */
void percorreTST(No* no, char *prefixo)
{
    char palavra[MAXTAM]; // MAXTAM definido como 50
    percorre(no, palavra, prefixo, 0);
}

/* Função para pesquisar uma palavra na TST */
int pesquisaTST(No *no, char *palavra)
{
    if (!no) /* Palavra não encontrada na TST */
        return 0;

    /* Se o caractere atual da palavra for menor que o caractere do nó atual */
    if (*palavra < (no)->caractere)
        return pesquisaTST(no->esq, palavra);

    /* Se o caractere atual da palavra for maior que o caractere do nó atual */
    else if (*palavra > (no)->caractere)
        return pesquisaTST(no->dir, palavra);

    /* Se o caractere atual da palavra for igual ao caractere do nó atual */
    else
    {
        /* Se o próximo caractere da palavra for '\0', encontrou a palavra */
        if (*(palavra+1) == '\0'){
            return no->fimString;
        }
        /* Chama a função pesquisaTST para o filho do meio do nó atual e para o resto da palavra a partir do
           caractere atual */
        return pesquisaTST(no->meio, palavra+1);
    }
}
/* Função responsavel por encontrar posicao de possiveis palavras para o prefixo */
void AutoPreenchimentoTST(No *no, int indice, char *prefixo){
    if(!no) return;
    if (prefixo[indice] < (no)->caractere)
	AutoPreenchimentoTST(no->esq,indice,prefixo);

    else if (prefixo[indice] > (no)->caractere)
	AutoPreenchimentoTST(no->dir,indice,prefixo);
    else
    {
	if(prefixo[indice+1] == '\0'){
		percorreTST(no->meio,prefixo);
	}
	else
		AutoPreenchimentoTST(no->meio,indice+1,prefixo);
    }
}

