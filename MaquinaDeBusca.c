#include "MaquinaDeBusca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* Função  */
char *strlwr(char *str) {
    unsigned char *p = (unsigned char *)str;

    while (*p) {
        *p = tolower((unsigned char)*p);
        p++;
    }
    return str;
}

void AdicionaArquivo (TLista *ListaArquivos) {
    TItem item;

    printf("Entre com o nome do arquivo que voce deseja adicionar: ");
    scanf("%s", item.it.arq.nome_arquivo);
    item.it.arq.entrada = fopen(item.it.arq.nome_arquivo, "r");
    if (item.it.arq.entrada) {
        printf("Arquivo válido\n");
        item.it.arq.termos_distintos = 0;
        insereLista(ListaArquivos, &item);
    }
    else
        printf("Arquivo inválido\n");
}

void FechaArquivos (TLista *ListaArquivos) {
    TCelula *celula;
    celula = ListaArquivos->primeiro->prox;
    while (celula != NULL) {
        fclose(celula->item.it.arq.entrada);
        celula = celula->prox;
    }
}

void CalculaPesos (TipoPatNo *no, int N) {
    TCelula *celula;
    int d; /* Número de documentos na coleção que contêm o termo k */
    if(no == NULL) {
        printf("Arvore esta vazia\n");
        return;
    }
    if(!ConfereTipoNo(no)) /* Se for nó interno */
        CalculaPesos(no->NO.NInterno.Esq, N); /* Chamada recursivamente para o nó à esquerda */

    if (ConfereTipoNo(no)) { /* Se for nó externo, o nó deve ser impresso */
        d = no->NO.NExterno.Lista.tamanho; /* O tamanho da lista representa a quantidade de documentos que possuem a palavra k */
        celula = no->NO.NExterno.Lista.primeiro->prox; /* Variável celula passa a apontar para a primeira célula da lista */
        while (celula != NULL) {
            celula->item.it.termo.peso =  (float)((celula->item.it.termo.qtde) * (log10(N) / d));
            celula = celula->prox;
        }
        return;
    }
    if(!ConfereTipoNo(no)) /* Se for nó interno */
        CalculaPesos(no->NO.NInterno.Dir, N); /* Chamada recursivamente para o nó à direita */
}

void CalculaTermosDistintos (TipoPatNo *no, TCelula *arq, int idDoc) {
    TCelula *celula;

    if (no == NULL)
        return;

    if(!ConfereTipoNo(no))
        CalculaTermosDistintos(no->NO.NInterno.Esq, arq, idDoc);

    if (ConfereTipoNo(no)) {
        celula = no->NO.NExterno.Lista.primeiro->prox;
        while (celula != NULL) {
            if (celula->item.it.termo.idDoc == idDoc) {
                arq->item.it.arq.termos_distintos++;
                break;
            }
            celula = celula->prox;
        }
        return;
    }

    if(!ConfereTipoNo(no))
        CalculaTermosDistintos(no->NO.NInterno.Dir, arq, idDoc);
}

void MontaIndiceInvertido (TLista *ListaArquivos) {
    TipoPatNo *raizPat;
    TipoTSTNo *raizTST;
    TCelula *celula; /* Célula auxiliar para percorrer toda a Lista de Arquivos */
    char string[50]; /* String para armazenar cada palavra de um arquivo de entrada */
    int idDoc = 1; /* O idDoc sempre começa como 1 */
    int i; /* Variável auxiliar para atribuir o caractere c à posição i da string */
    char c; /* Caractere auxiliar para ler caractere por caractere de cada arquivo */

    inicializaPatricia(&raizPat); /* Inicializando a Patricia */
    inicializaTST(&raizTST); /* Inicializando a TST */

    celula = ListaArquivos->primeiro->prox; /* Aponta para a primeira célula da Lista de Arquivos */

    while (celula != NULL) {
        /* Enquanto não chegar no final do arquivo */
        while (!feof(celula->item.it.arq.entrada)) {
            i = 0; /* Posição para ser atribuído o caractere c na string */
            c = fgetc(celula->item.it.arq.entrada);
            /* Enquanto c for um caractere válido (não especial) */
            while (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122))) {
                string[i] = c;
                c = fgetc(celula->item.it.arq.entrada);
                i++;
            }
            string[i] = '\0'; /* Adiciona '\0' indicando o fim da string */
            strlwr(string); /* Transforma todas as letras da string em letras minúsculas */
            /* Condição para não inserir uma string vazia nas árvores */
            if (strlen(string) > 0) {
                raizPat = InserePatricia(string, &raizPat, idDoc); /* Insere na Patricia */
                insereTST(&raizTST, string); /* Insere na TST */
            }
        }
        celula->item.it.arq.idDoc = idDoc;
        CalculaTermosDistintos(raizPat, celula, celula->item.it.arq.idDoc); /* Calcula termos distintos do documento atual */
        printf("\nQuantidade de termos distintos do documento %d: %d\n", celula->item.it.arq.idDoc, celula->item.it.arq.termos_distintos);
        idDoc++; /* Incrementa o id do documento da lista */
        celula = celula->prox; /* Passa para a próxima célula */
    }
    CalculaPesos(raizPat, ListaArquivos->tamanho); /* Calcula o peso de todos os termos inseridos na árvore Patricia */
    printf("\nPatricia Final\n");
    imprimePatricia(raizPat);
}
