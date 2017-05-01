#include "Patricia.h"
#include "ListaEncadeada.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Função para inicializar a árvore Patricia como NULL */
void inicializaPatricia (TipoPatNo **raiz) {
    *raiz = NULL;
}

/* Função para retornar o i-esimo caractere da chave k a partir da esquerda */
char Caractere (short i, char *k) {
    return k[i];
}

/* Função que compara qual caractere é menor/maior */
unsigned int MenorIgual(char a, char b)
{
    return (a <= b) ? TRUE:FALSE;
}

/* Função para conferir se o nó passado como parâmetro é interno ou externo */
unsigned int ConfereTipoNo (TipoPatNo *no) {
    return (no->nt == Externo) ? TRUE:FALSE; /* Retorna 1 se for externo e retorna 0 se for interno */
}

/* Função para criar um nó interno da árvore Patricia */
TipoPatNo* CriaNoInt (short i, TipoPatNo **Esq,  TipoPatNo **Dir, char Caractere) {
    TipoPatNo *no;
    no = (TipoPatNo *)malloc(sizeof(TipoPatNo));
    no->nt = Interno;
    no->NO.NInterno.Esq = *Esq;
    no->NO.NInterno.Dir = *Dir;
    no->NO.NInterno.Index = i;
    no->NO.NInterno.Caractere = Caractere;
    return no;
}

/* Função para criar um nó externo da árvore Patricia */
TipoPatNo * CriaNoExt (char *k, int idDoc) {
    TipoPatNo *no;
    TItem item;

    item.qtde = 1;
    item.idDoc = idDoc;
    item.relevancia = 0;

    no = (TipoPatNo *)malloc(sizeof(TipoPatNo));
    no->nt = Externo;
    strcpy(no->NO.Chave, k);

    inicializaLista(&(no->NoLista.Lista));
    insereLista(&(no->NoLista.Lista), &item);
    no->NoLista.tamanho = 1;
    return no;
}

/* Função para pesquisar se uma palavra k se encontra na árvore com seu respectivo idDoc */
void pesquisaPatricia (char *k, TipoPatNo *t, int idDoc) {
    TCelula *celula; /* Célula auxiliar para percorrer a lista do nó externo encontrado */

    if (ConfereTipoNo(t)) /* Se o nó for externo */
    {
        celula = t->NoLista.Lista.primeiro->prox; /* Passa a apontar para a primeira célula da lista */
        if (strcmp(k, t->NO.Chave) == 0){ /* Se a palavra k procurada for igual à palavra do nó externo */
            while(celula != NULL){
                if(celula->item.idDoc == idDoc) {/* Confere se a palavra se encontra no idDoc procurado */
                    printf("A palavra %s, cujo idDoc eh %d se encontra na arvore\n", t->NO.Chave, celula->item.idDoc); /* Achou a palavra k no dado idDoc */
                    return;
                }
                else
                    celula = celula->prox; /* Procura na próxima célula da lista */
            }
            if(celula == NULL) { /* Chegou na última célula e não encontrou a palavra com o dado idDoc */
                printf("A palavra %s nao se encontra no idDoc procurado\n", k);
                return;
            }
        }
        else { /* Não encontrou a palavra na árvore */
            printf("A palavra %s nao se encontra na arvore\n", k);
            return;
        }
    }
    /* Se k[t->NO.NInterno.Index] for <= ao caractere do nó interno atual, chama recursivamente para o nó à esquerda */
    if (MenorIgual(Caractere(t->NO.NInterno.Index, k), t->NO.NInterno.Caractere))
        pesquisaPatricia(k, t->NO.NInterno.Esq, idDoc);
    /* Caso contrário, chama recursivamente para o nó à direita */
    else
        pesquisaPatricia(k, t->NO.NInterno.Dir, idDoc);

}

TipoPatNo * InsereEntre (char *k, TipoPatNo **t, short i, int idDoc) {
    TipoPatNo *p;
    char caractere;

    if (ConfereTipoNo(*t) || i < (*t)->NO.NInterno.Index) {
        if(ConfereTipoNo(*t)) { /* Se for nó externo */
            caractere = Caractere(i, (*t)->NO.Chave);
        }
        else { /* Se for nó interno */
            caractere = (*t)->NO.NInterno.Caractere;
        }
        /* Cria um novo nó externo */
        p = CriaNoExt(k, idDoc);
        if (MenorIgual(Caractere(i, k), caractere)){
            printf("\nEntrou aqui\n");
            return (CriaNoInt(i, &p, t, Caractere(i, k)));
        }
        else {
            printf("\nEntrou aqui 2\n");
            return (CriaNoInt(i, t, &p, caractere));
        }
    }
    else {
        /* Se k[(*t)->NO.NInterno.Index] for <= ao caractere do nó interno atual, chama recursivamente para o nó à esquerda */
        if (MenorIgual(Caractere((*t)->NO.NInterno.Index, k), (*t)->NO.NInterno.Caractere))
            (*t)->NO.NInterno.Esq = InsereEntre(k, &(*t)->NO.NInterno.Esq, i, idDoc);
        /* Caso contrário, chama recursivamente para o nó à direita */
        else
            (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i, idDoc);

        return (*t);
    }
}

TipoPatNo * InserePatricia (char *k, TipoPatNo **t, int idDoc) {
    TipoPatNo *p;
    int i;
    TCelula *celula;
    TItem item;

    printf("String: %s\n", k);
    if (*t == NULL){ /* Árvore está vazia, logo criamos um nó externo com a palavra k passada como parâmetro */
        return (CriaNoExt(k,idDoc));
    }
    else { /* Árvore não está vazia */
        p = *t;
        while (!ConfereTipoNo(p)) { /* Se for nó interno */
            /* Se k[p->NO.NInterno.Index] for <= ao caractere do nó p, p passa a apontar para o filho à esquerda */
            if (MenorIgual(Caractere(p->NO.NInterno.Index, k), p->NO.NInterno.Caractere))
                p = p->NO.NInterno.Esq;
            /* Caso contrário, p passa a apontar para o filho à direita */
            else
                p = p->NO.NInterno.Dir;
        }

        /* acha o primeiro Caractere diferente */
        i = 0;
        if(strlen(k) >= strlen(p->NO.Chave)) { /* Se o tamanho da palavra k for >= ao tamanho da palavra do nó p */
            /* Enquanto i for <= ao tamanho da palavra k && k[i] for igual à p->NO.Chave[i] */
            while ((i <= strlen(k)) && (Caractere(i, k) == Caractere(i, p->NO.Chave)))
                i++;
            /* Se i for >= ao tamanho da palavra k */
            if (i >= strlen(k)) {
                celula = p->NoLista.Lista.primeiro->prox;
                /* Se o idDoc da palavra k for igual ao idDoc da celula atual */
                if(celula->item.idDoc == idDoc) {
                    celula->item.qtde++; /* Incrementa a quantidade de ocorrências da palavra k */
                }
                /* Caso contrário */
                else {
                    /* Procura uma célula que tenha o dado idDoc */
                    while(celula->prox != NULL && celula->item.idDoc != idDoc)
                        celula = celula->prox;
                    /* Se foi encontrada uma célula que tenha o dado idDoc */
                    if(celula->item.idDoc == idDoc)
                        celula->item.qtde++; /* Incrementa a quantidade de ocorrências da palavra k */
                    /* Caso contrário */
                    else {
                        if(celula->item.idDoc != idDoc && celula->prox == NULL){
                            /* Cria uma celula com a palavra k no dado idDoc */
                            item.idDoc = idDoc;
                            item.qtde = 1;
                            item.relevancia = 0;
                            insereLista(&(p->NoLista.Lista), &item); /* Insere a célula na lista */
                            p->NoLista.tamanho++; /* Incrementa o tamanho da lista */
                        }
                    }
                }
                return (*t);
            }
            else /* Se i for < que o tamanho da palavra k */
                return (InsereEntre(k, t, i,idDoc));
        }
        /* Se a palavra k for < que a palavra do nó p */
        else {
            /* Enquanto i for <= ao tamanho da palavra k && k[i] for igual à p->NO.Chave[i] */
            while ((i <= strlen(p->NO.Chave)) && (Caractere(i, k) == Caractere(i, p->NO.Chave)))
                i++;
            /* Se i for >= ao tamanho da palavra k */
            if (i >= strlen(p->NO.Chave)){
                celula = p->NoLista.Lista.primeiro->prox;
                /* Se o idDoc da palavra k for igual ao idDoc da celula atual */
                if(celula->item.idDoc == idDoc){
                    celula->item.qtde++; /* Incrementa a quantidade de ocorrências da palavra k */
                }
                /* Caso contrário */
                else {
                    /* Procura uma célula que tenha o dado idDoc */
                    while(celula->prox != NULL && celula->item.idDoc != idDoc)
                        celula = celula->prox;
                    /* Se foi encontrada uma célula que tenha o dado idDoc */
                    if(celula->item.idDoc == idDoc)
                        celula->item.qtde++; /* Incrementa a quantidade de ocorrências da palavra k */
                    else {
                        if(celula->item.idDoc != idDoc && celula->prox == NULL){
                            /* Cria uma célula com a palavra k no dado idDoc */
                            item.idDoc = idDoc;
                            item.qtde = 1;
                            item.relevancia = 0;
                            insereLista(&(p->NoLista.Lista),&item); /* Insere a célula na lista */
                            p->NoLista.tamanho++; /* Incrementa o tamanho da lista */
                        }
                    }
                }
                return (*t);
            }
            /* Se i for < que o tamanho da palavra k */
            else
                return (InsereEntre(k, t, i,idDoc));
        }
    }
}

/* Função para imprimir a árvore Patricia em ordem */
void imprimePatricia (TipoPatNo *no)
{

    if(no == NULL) {
        printf("Arvore esta vazia\n");
        return;
    }
    if(!ConfereTipoNo(no)) {/* Se for nó interno */
        imprimePatricia(no->NO.NInterno.Esq); /* Chamada recursiva para o nó à esquerda */
    }

    if (ConfereTipoNo(no)) {
        printf("Palavra: %s -> ",no->NO.Chave);
        imprimeLista(&(no->NoLista.Lista));
        return;
    }

    if(!ConfereTipoNo(no)) { /* Se for nó interno */
        imprimePatricia(no->NO.NInterno.Dir); /* Chamada recursiva para o nó à direita */
    }
}
