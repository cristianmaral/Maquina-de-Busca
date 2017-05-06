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

void AdicionaArquivo (char *nome_arq) {
    TItem *item = (TItem*)malloc(sizeof(TItem));

    printf("Entre com o nome do arquivo que voce deseja adicionar: ");
    item->arq.nome_arquivo = nome_arq;
    item->arq.entrada = fopen(item->arq.nome_arquivo, "r");
    if (item->arq.entrada) {
        printf("Arquivo válido\n");
        item->arq.termos_distintos = 0;
        item->arq.relevancia = 0.0;
        insereLista(ListaArquivos, item);
    }
    else
        printf("Arquivo inválido\n");
}

void FechaArquivos () {
    TCelula *celula;
    celula = ListaArquivos->primeiro->prox;
    while (celula != NULL) {
        fclose(celula->item.arq.entrada);
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

    if (ConfereTipoNo(no)) { /* Se for nó externo */
        d = no->NO.NExterno.Lista.tamanho; /* O tamanho da lista representa a quantidade de documentos que possuem a palavra k */
        celula = no->NO.NExterno.Lista.primeiro->prox; /* Variável celula passa a apontar para a primeira célula da lista */
        while (celula != NULL) {
            celula->item.termo.peso =  (float)((celula->item.termo.qtde) * (log10(N) / d));
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
            if (celula->item.termo.idDoc == idDoc) {
                arq->item.arq.termos_distintos++;
                break;
            }
            celula = celula->prox;
        }
        return;
    }

    if(!ConfereTipoNo(no))
        CalculaTermosDistintos(no->NO.NInterno.Dir, arq, idDoc);
}

void CalculaRelevancia (TipoPatNo *no, char **palavras, int n_termos) {
    float somatorio = (float)0;
    int i;
    TCelula *celula;

    celula = ListaArquivos->primeiro->prox;
    while (celula != NULL) {
        for (i=0; i<n_termos; i++) {
            somatorio += RetornaPesoTermo(palavras[i], no, celula->item.arq.idDoc);
        }
        celula->item.arq.relevancia = (float)(somatorio / celula->item.arq.termos_distintos);
        celula = celula->prox;
        somatorio = (float)0;
    }

}

void BuscaTermos (TipoPatNo *no, char *string) {
    int q_termos = 0; /* Conta a quantidade de termos de busca */
    char aux[50]; /* String auxiliar para guardar temporariamente cada palavra de busca separadamente */
    char *palavras[30]; /* Vetor de Strings - Consideramos o máximo de 30 palavras de busca */
    char c; /* Caractere auxiliar para ler caractere por caractere da string que contém todas as palavras de busca */
    int i = 0; /* Indica a posição onde c deve ser armazenado na string aux */
    int j = 0; /* Indica a posição onde a string aux deve ser armazenada no vetor palavras */
    int cont = 0; /* Indica a posição atual da string que contém todas as palavras de busca */

    strlwr(string); /* Passa a string inteira para minúscula */
    printf("String: %s\n", string);

    /* Enquanto não chegar no final da string */
    while (string[cont] != '\0') {
        c = string[cont];
        if (c != ' ') {
            aux[i] = c;
            i++;
        }
        /* Indica o final de uma palavra */
        if (c == ' ') {
            aux[i] = '\0';
            i = 0; /* Para armazenar a primeira letra da proxima palavra na posição 0 da string aux */
            palavras[j] = strdup(aux); /* Insere aux na posição j do vetor de palavras */
            j++; /* Incrementa o j */
            q_termos++; /* Incrementa a quantidade de palavras */
        }
        cont++; /* Passa para a próxima posição da string */
    }
    /* Tratando a última palavra de busca */
    aux[i] = '\0';
    q_termos++;
    palavras[j] = strdup(aux);

    for (i=0; i<q_termos; i++)
        printf("Palavra[%d]: %s\n", i, palavras[i]);
    printf("q_termos: %d\n", q_termos);
    CalculaRelevancia(no, palavras, q_termos);
}

void MontaIndiceInvertido () {
    cancela = FALSE;
    TipoPatNo *raizPatTemp;
    TipoTSTNo *raizTSTTemp;
    TCelula *celula; /* Célula auxiliar para percorrer toda a Lista de Arquivos */
    char string[50]; /* String para armazenar cada palavra de um arquivo de entrada */
    int idDoc = 1; /* O idDoc sempre começa como 1 */
    int i; /* Variável auxiliar para atribuir o caractere c à posição i da string */
    char c; /* Caractere auxiliar para ler caractere por caractere de cada arquivo */

    inicializaPatricia(&raizPatTemp); /* Inicializando a Patricia */
    inicializaTST(&raizTSTTemp); /* Inicializando a TST */

    celula = ListaArquivos->primeiro->prox; /* Aponta para a primeira célula da Lista de Arquivos */

    while (celula != NULL && !cancela) {
        /* Enquanto não chegar no final do arquivo */
        while (!feof(celula->item.arq.entrada)) {
            i = 0; /* Posição para ser atribuído o caractere c na string */
            c = fgetc(celula->item.arq.entrada);
            /* Enquanto c for um caractere válido (não especial) */
            while (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122))) {
                string[i] = c;
                c = fgetc(celula->item.arq.entrada);
                i++;
            }
            string[i] = '\0'; /* Adiciona '\0' indicando o fim da string */
            strlwr(string); /* Transforma todas as letras da string em letras minúsculas */
            /* Condição para não inserir uma string vazia nas árvores */
            if (strlen(string) > 0) {
                raizPatTemp = InserePatricia(string, &raizPatTemp, idDoc); /* Insere na Patricia */
                insereTST(&raizTSTTemp, string); /* Insere na TST */
            }
        }
        celula->item.arq.idDoc = idDoc;
        CalculaTermosDistintos(raizPatTemp, celula, celula->item.arq.idDoc); /* Calcula termos distintos do documento atual */
        printf("\nQuantidade de termos distintos do documento %d: %d\n", celula->item.arq.idDoc, celula->item.arq.termos_distintos);
        idDoc++; /* Incrementa o id do documento da lista */
        celula = celula->prox; /* Passa para a próxima célula */
    }
    if(!cancela){
	    CalculaPesos(raizPatTemp, ListaArquivos->tamanho); /* Calcula o peso de todos os termos inseridos na árvore Patricia */
	    printf("\nPatricia Final\n");
	    imprimePatricia(raizPatTemp);
    }
    else printf("Cancelado 1\n");
    if(!cancela){
	    raizPat = raizPatTemp;
	    raizTST = raizTSTTemp;
    }
    else printf("Cancelado 2\n");
}
