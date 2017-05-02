#include "Patricia.h"
#include "ListaEncadeada.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Função para inicializar a árvore Patricia como NULL */
void inicializaPatricia (TipoPatNo **raiz) {
    *raiz = NULL;
}

/* Função que compara 2 caracteres e retorna 1 se o caractere a for >= a  b e retorna 0 quando b > a */
unsigned int ComparaChar (char a, char b) {
    return (a <= b) ? 1:0;
}

/* Função para conferir se o nó passado como parâmetro é interno ou externo */
unsigned int ConfereTipoNo (TipoPatNo *no) {
    return (no->nt == Externo) ? 1:0; /* Retorna 1 se for externo e retorna 0 se for interno */
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
    item.peso = 0;

    no = (TipoPatNo *)malloc(sizeof(TipoPatNo));
    no->nt = Externo;
    strcpy(no->NO.NExterno.Palavra, k); /*  */

    inicializaLista(&(no->NO.NExterno.Lista));
    insereLista(&(no->NO.NExterno.Lista), &item);
    no->NO.NExterno.Lista.tamanho = 1;
    return no;
}

/* Função para pesquisar se uma palavra k se encontra na árvore com seu respectivo idDoc */
void PesquisaPatricia (char *k, TipoPatNo *t, int idDoc) {
    TCelula *celula; /* Célula auxiliar para percorrer a lista do nó externo encontrado */

    if (ConfereTipoNo(t)) /* Se o nó for externo */
    {
        celula = t->NO.NExterno.Lista.primeiro->prox; /* Passa a apontar para a primeira célula da lista */
        if (strcmp(k, t->NO.NExterno.Palavra) == 0){ /* Se a palavra k procurada for igual à palavra do nó externo */
            while(celula != NULL){
                if(celula->item.idDoc == idDoc) {/* Confere se a palavra se encontra no idDoc procurado */
                    printf("A palavra %s, cujo idDoc eh %d se encontra na arvore\n", t->NO.NExterno.Palavra, celula->item.idDoc); /* Achou a palavra k no dado idDoc */
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
    if (ComparaChar(k[t->NO.NInterno.Index], t->NO.NInterno.Caractere))
        PesquisaPatricia(k, t->NO.NInterno.Esq, idDoc);
    /* Caso contrário, chama recursivamente para o nó à direita */
    else
        PesquisaPatricia(k, t->NO.NInterno.Dir, idDoc);

}

TipoPatNo * InsereEntre (char *k, TipoPatNo **t, short i, int idDoc) {
    TipoPatNo *p;
    char caractere;

    if (ConfereTipoNo(*t) || i < (*t)->NO.NInterno.Index) {
        if(ConfereTipoNo(*t)) { /* Se for nó externo */
            caractere = (*t)->NO.NExterno.Palavra[i];
        }
        else { /* Se for nó interno */
            caractere = (*t)->NO.NInterno.Caractere;
            printf("-------------Entrou aqui---------------\n");
        }
        /* Cria um novo nó externo */
        p = CriaNoExt(k, idDoc);
        /* Se k[i] <= caractere, cria um nó interno com o indice i e o caractere, o filho à esquerda desse novo nó interno passa a ser
           o nó p e o filho à direita passa a ser o nó t */
        if (ComparaChar(k[i], caractere))
            return (CriaNoInt(i, &p, t, k[i]));
        /* Caso contrário, cria um nó interno com o indice i e o caractere, o filho à esquerda desse novo nó interno passa a ser
           o nó t e o filho à direita passa a ser o nó p */
        else
            return (CriaNoInt(i, t, &p, caractere));
    }
    /* Nó é interno ou i >=  (*t)->NO.NInterno.Index */
    else {
        /* Se k[(*t)->NO.NInterno.Index] for <= ao caractere do nó interno atual, chama recursivamente para o nó à esquerda */
        if (ComparaChar(k[(*t)->NO.NInterno.Index], (*t)->NO.NInterno.Caractere))
            (*t)->NO.NInterno.Esq = InsereEntre(k, &(*t)->NO.NInterno.Esq, i, idDoc);
        /* Caso contrário, chama recursivamente para o nó à direita */
        else
            (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i, idDoc);

        return (*t);
    }
}

/* Função principal para inserir uma palavra k na árvore Patricia */
TipoPatNo * InserePatricia (char *k, TipoPatNo **t, int idDoc) {
    TipoPatNo *p;
    int i;
    TCelula *celula;
    TItem item;

    if (*t == NULL){ /* Árvore está vazia, logo criamos um nó externo com a palavra k passada como parâmetro */
        return (CriaNoExt(k,idDoc));
    }
    else { /* Árvore não está vazia */
        p = *t;
        while (!ConfereTipoNo(p)) { /* Enquanto p for nó interno */
            /* Se k[p->NO.NInterno.Index] for <= ao caractere do nó p, p passa a apontar para o filho à esquerda */
            if (ComparaChar(k[p->NO.NInterno.Index], p->NO.NInterno.Caractere))
                p = p->NO.NInterno.Esq;
            /* Caso contrário, p passa a apontar para o filho à direita */
            else
                p = p->NO.NInterno.Dir;
        }

        /* acha o primeiro Caractere diferente */
        i = 0;
        /* Se o tamanho da palavra k for >= ao tamanho da palavra do nó p */
        if(strlen(k) >= strlen(p->NO.NExterno.Palavra)) {
            /* Enquanto i for < que o tamanho da palavra k && k[i] for igual à p->NO.Palavra[i] */
            while ((i < strlen(p->NO.NExterno.Palavra)) && (k[i] == p->NO.NExterno.Palavra[i]))
                i++;
            /* Se i for == ao tamanho da palavra k */
            printf("\ni: %d\n", i);
            if (i == strlen(k)) {
                celula = p->NO.NExterno.Lista.primeiro->prox;
                /* Se o idDoc da palavra k passado como parâmetro for igual ao idDoc da celula atual */
                if(celula->item.idDoc == idDoc)
                    celula->item.qtde++; /* Incrementa a quantidade de ocorrências da palavra k */
                /* Caso contrário */
                else {
                    /* Procura uma célula que tenha o idDoc passado como parâmetro */
                    while(celula->prox != NULL && celula->item.idDoc != idDoc)
                        celula = celula->prox;
                    /* Se foi encontrada uma célula cujo idDoc seja igual ao idDoc passado como parâmetro */
                    if(celula->item.idDoc == idDoc)
                        celula->item.qtde++; /* Incrementa a quantidade de ocorrências da palavra k */
                    /* Caso contrário - Se não existir nenhuma célula da palavra k com o idDoc passado como parâmetro */
                    else {
                        if(celula->item.idDoc != idDoc && celula->prox == NULL) {
                            /* Cria uma nova célula com a palavra k cujo campo idDoc seja o idDoc passado como parâmetro */
                            item.idDoc = idDoc;
                            item.qtde = 1;
                            item.peso = 0;
                            insereLista(&(p->NO.NExterno.Lista), &item); /* Insere a célula na lista */
                            p->NO.NExterno.Lista.tamanho++; /* Incrementa o tamanho da lista */
                        }
                    }
                }
                return (*t);
            }
            /* Se i for < que o tamanho da palavra k */
            else
                return (InsereEntre(k, t, i,idDoc));
        }
        /* Se a palavra k for < que a palavra do nó p */
        else {
            /* Enquanto i for < que o tamanho da palavra k && k[i] for igual à p->NO.Palavra[i] */
            while ((i < strlen(k)) && (k[i] == p->NO.NExterno.Palavra[i]))
                i++;
            printf("\ni do else: %d\n", i);
            return (InsereEntre(k, t, i,idDoc));
        }
    }
}

/* Função para imprimir a árvore Patricia em ordem */
void imprimePatricia (TipoPatNo *no) {
    if(no == NULL) {
        printf("Arvore esta vazia\n");
        return;
    }
    if(!ConfereTipoNo(no)) /* Se for nó interno */
        imprimePatricia(no->NO.NInterno.Esq); /* Chamada recursivamente para o nó à esquerda */

    if (ConfereTipoNo(no)) { /* Se for nó externo, o nó deve ser impresso */
        printf("[%s] -> ",no->NO.NExterno.Palavra);
        imprimeLista(&(no->NO.NExterno.Lista));
        return;
    }

    if(!ConfereTipoNo(no)) /* Se for nó interno */
        imprimePatricia(no->NO.NInterno.Dir); /* Chamada recursivamente para o nó à direita */
}
