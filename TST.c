#include "TST.h"
#include <stdio.h>
#include <stdlib.h>

void inicializaTST (TipoTSTNo **raiz) { /* Inicia a �rvore */
    *raiz = NULL;
}

/* Fun��o para criar um novo n� da TST */
TipoTSTNo* novoNoTST(char caractere) {
    TipoTSTNo* aux = (TipoTSTNo*)malloc(sizeof(TipoTSTNo));
    aux->caractere = caractere;
    aux->fimString = 0;
    aux->esq = aux->meio = aux->dir = NULL;
    return aux;
}

/* Fun��o para inserir uma nova palavra na TST */
void insereTST(TipoTSTNo** no, char *palavra)
{
    /* Primeiro Caso: �rvore est� vazia */
    if (!(*no))
        *no = novoNoTST(*palavra); /* *palavra = caractere atual da palavra */

    /* Se o caractere atual da palavra for menor que o caractere do n� atual,
       ent�o insere esta palavra na sub�rvore esquerda do n� atual */
    if ((*palavra) < (*no)->caractere)
        insereTST(&( (*no)->esq ), palavra);

    /* Se o caractere atual da palavra for maior que o caractere do n� atual,
       ent�o insere esta palavra na sub�rvore direita do n� atual */
    else if ((*palavra) > (*no)->caractere)
        insereTST(&( (*no)->dir ), palavra);

    /* Se o caractere atual da palavra for igual ao caractere do n� atual */
    else {
        if (*(palavra+1))
            insereTST(&( (*no)->meio ), palavra+1);
        /* O �ltimo caractere da palavra */
        else
            (*no)->fimString = 1;
    }
}

/* Uma fun��o recursiva para percorrer a TST */
void percorre (TipoTSTNo* no, char* palavra,char *prefixo, int indice,TLista *retorno)
{
    TCelula *temp = (TCelula*)malloc(sizeof(TCelula));
    temp->prox = NULL;
    temp->item.palavra = (char*)malloc(sizeof(char)*40);
    if (no)
    {
        /* Primeiro percorre a sub�rvore � esquerda */
        percorre(no->esq, palavra, prefixo, indice, retorno);

        /* Guarda o caractere deste n� na string palavra*/
        palavra[indice] = no->caractere;
        if (no->fimString)
        {
            palavra[indice+1] = '\0';
	    sprintf(temp->item.palavra,"%s%s",prefixo,palavra);
	    insereCelulaEmLista(retorno,temp);
        }

        /* Percorre a sub�rvore usando o ponteiro do meio (sub�rvore do meio) */
        percorre(no->meio, palavra, prefixo, indice + 1,retorno);

        /* Finalmente percorre a sub�rvore � direita */
        percorre(no->dir, palavra, prefixo, indice, retorno);
    }
}

/* Fun��o principal que encapsula a fun��o transverseTSTUtil */
void percorreTST(TipoTSTNo* no, char *prefixo,TLista *retorno)
{
    char palavra[MAXTAM]; // MAXTAM definido como 50
    percorre(no, palavra, prefixo, 0, retorno);
}

/* Fun��o para pesquisar uma palavra na TST */
int pesquisaTST(TipoTSTNo *no, char *palavra)
{
    if (!no) /* Palavra n�o encontrada na TST */
        return 0;

    /* Se o caractere atual da palavra for menor que o caractere do n� atual */
    if (*palavra < (no)->caractere)
        return pesquisaTST(no->esq, palavra);

    /* Se o caractere atual da palavra for maior que o caractere do n� atual */
    else if (*palavra > (no)->caractere)
        return pesquisaTST(no->dir, palavra);

    /* Se o caractere atual da palavra for igual ao caractere do n� atual */
    else
    {
        /* Se o pr�ximo caractere da palavra for '\0', encontrou a palavra */
        if (*(palavra+1) == '\0'){
            return no->fimString;
        }
        /* Chama a fun��o pesquisaTST para o filho do meio do n� atual e para o resto da palavra a partir do
           caractere atual */
        return pesquisaTST(no->meio, palavra+1);
    }
}
/* Fun��o responsavel por encontrar posicao de possiveis palavras para o prefixo */
void AutoPreenchimentoTST(TipoTSTNo *no, int indice, char *prefixo, TLista *retorno){
    if(!no) return;
    if (prefixo[indice] < (no)->caractere)
	AutoPreenchimentoTST(no->esq,indice,prefixo,retorno);

    else if (prefixo[indice] > (no)->caractere)
	AutoPreenchimentoTST(no->dir,indice,prefixo,retorno);
    else
    {
	if(prefixo[indice+1] == '\0'){
		percorreTST(no->meio,prefixo,retorno);
	}
	else
		AutoPreenchimentoTST(no->meio,indice+1,prefixo,retorno);
    }
}

