#include "Patricia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Função para inicializar a árvore Patricia como NULL */
void inicializaPatricia (TipoPatNo **raiz) {
    *raiz = NULL;
}

/* Função que compara 2 caracteres e retorna 1 se o caractere a for >= a  b e retorna 0 quando b > a */
short ComparaChar (char a, char b) {
    return (a <= b) ? 1:0;
}

/* Função para conferir se o nó passado como parâmetro é interno ou externo */
short ConfereTipoNo (TipoPatNo *no) {
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
    TItem item; /* Criação de um item temporário (auxiliar) para ser inserido na lista */
    item.termo.qtde = 1; /* Quando é a primeira palavra ocorrente no idDoc, sua quantidade é 1 */
    item.termo.idDoc = idDoc;
    item.termo.peso = (float)0; /* Valor inicial do peso da palavra no idDoc passado como parâmetro */

    no = (TipoPatNo *)malloc(sizeof(TipoPatNo));
    no->nt = Externo;
    strcpy(no->NO.NExterno.Palavra, k); /* Copia a palavra k para o campo palavra do novo nó externo */
    inicializaLista(&(no->NO.NExterno.Lista));
    insereLista(&(no->NO.NExterno.Lista), &item);
    no->NO.NExterno.Lista.tamanho = 1; /* Primeira célula da lista */
    return no;
}

/* Função para retornar o peso do termo k no idDoc passado como parâmetro */
float RetornaPesoTermo (char *k, TipoPatNo *t, int idDoc) {
    TCelula *celula; /* Célula auxiliar para percorrer a lista do nó externo encontrado */

    if (ConfereTipoNo(t)) /* Se o nó for externo */
    {
        celula = t->NO.NExterno.Lista.primeiro->prox; /* Passa a apontar para a primeira célula da lista */
        if (strcmp(k, t->NO.NExterno.Palavra) == 0){ /* Se a palavra k procurada for igual à palavra do nó externo */
            while(celula != NULL){
                if(celula->item.termo.idDoc == idDoc) {/* Confere se a palavra se encontra no idDoc passado como parâmetro */
                    /* Achou a palavra k no idDoc passado como parâmetro*/
                    return celula->item.termo.peso;
                }
                else
                    celula = celula->prox; /* Procura na próxima célula da lista */
            }
            if(celula == NULL) { /* Chegou na última célula e não encontrou a palavra com o idDoc passado como parâmetro */
                return (float)0;
            }
        }
        else { /* Não encontrou a palavra na árvore */
            return (float)0;
        }
    }
    /* Se k[t->NO.NInterno.Index] for <= ao caractere do nó interno atual, chama recursivamente para o nó à esquerda */
    if (ComparaChar(k[t->NO.NInterno.Index], t->NO.NInterno.Caractere))
        return RetornaPesoTermo(k, t->NO.NInterno.Esq, idDoc);
    /* Caso contrário, chama recursivamente para o nó à direita */
    else
        return RetornaPesoTermo(k, t->NO.NInterno.Dir, idDoc);

}

TipoPatNo * InsereEntre (char *k, TipoPatNo **t, int i, int idDoc, char Caractere) {
    TipoPatNo *p;

    if (ConfereTipoNo(*t) || i < (int)(*t)->NO.NInterno.Index) {
        p = CriaNoExt(k, idDoc);
        /* Se k[i] <= caractere, cria um nó interno com o indice i e o caractere, o filho à esquerda desse novo nó interno passa a ser
           o nó p e o filho à direita passa a ser o nó t */
        if (ComparaChar(k[i], Caractere))
            return (CriaNoInt(i, &p, t, k[i]));
        /* Caso contrário, cria um nó interno com o indice i e o caractere, o filho à esquerda desse novo nó interno passa a ser
           o nó t e o filho à direita passa a ser o nó p */
        else
            return (CriaNoInt(i, t, &p, Caractere));
    }
    /* Nó é interno ou i >=  (*t)->NO.NInterno.Index */
    else {
        /* Se k[(*t)->NO.NInterno.Index] for <= ao caractere do nó interno atual, chama recursivamente para o nó à esquerda */
        if (ComparaChar(k[(*t)->NO.NInterno.Index], (*t)->NO.NInterno.Caractere))
            (*t)->NO.NInterno.Esq = InsereEntre(k, &(*t)->NO.NInterno.Esq, i, idDoc, Caractere);
        /* Caso contrário, chama recursivamente para o nó à direita */
        else
            (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i, idDoc, Caractere);

        return (*t);
    }
}

/* Função principal para inserir uma palavra k na árvore Patricia */
TipoPatNo * InserePatricia (char *k, TipoPatNo **t, int idDoc) {
    TipoPatNo *p;
    int i;
    TCelula *celula;
    TItem item;

    if (*t == NULL) /* Árvore está vazia, logo criamos um nó externo com a palavra k passada como parâmetro */
        return (CriaNoExt(k,idDoc));
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
        /* Enquanto k[i] for igual à p->NO.NExterno.Palavra[i] */
        while (k[i] == p->NO.NExterno.Palavra[i])
            i++;
        /* Se a palavra do nó externo atual for igual à string k */
        if (strcmp(p->NO.NExterno.Palavra, k) == 0) {
            celula = p->NO.NExterno.Lista.primeiro->prox;
            /* Procura uma célula que tenha o idDoc passado como parâmetro */
            while(celula->prox != NULL && celula->item.termo.idDoc != idDoc)
                celula = celula->prox;
                /* Se foi encontrada uma célula cujo idDoc seja igual ao idDoc passado como parâmetro */
                if(celula->item.termo.idDoc == idDoc)
                    celula->item.termo.qtde++; /* Incrementa a quantidade de ocorrências da palavra k */

                /* Caso contrário - Se não existir nenhuma célula da palavra k com o idDoc passado como parâmetro */
                else {
                    /* Cria uma nova célula com a palavra k cujo campo idDoc seja o idDoc passado como parâmetro */
                    item.termo.idDoc = idDoc;
                    item.termo.qtde = 1;
                    item.termo.peso = (float)0;
                    insereLista(&(p->NO.NExterno.Lista), &item); /* Insere a célula na lista */
                }
            return (*t);
        }
        /* Se a palavra do nó externo atual for diferente da string k */
        else
            return (InsereEntre(k, t, i, idDoc, p->NO.NExterno.Palavra[i]));
    }
}

/* Função para imprimir a árvore Patricia em ordem */
void imprimePatricia (TipoPatNo *no) {
    if(no == NULL) {
        printf("Arvore esta vazia\n");
        return;
    }
    if (ConfereTipoNo(no)) { /* Se for nó externo, o nó deve ser impresso */
        printf("[%s] == ",no->NO.NExterno.Palavra);
        imprimeLista(&(no->NO.NExterno.Lista));
        return;
    }
    /* Se for nó interno */
    imprimePatricia(no->NO.NInterno.Esq); /* Chamada recursivamente para o nó à esquerda */
    imprimePatricia(no->NO.NInterno.Dir); /* Chamada recursivamente para o nó à direita */

}
