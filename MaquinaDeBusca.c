#include "MaquinaDeBusca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* Função para converter todos os caracteres da string passada como parâmetro para minúsculo */
char *strlwr(char *str) {
    unsigned char *p = (unsigned char *)str;

    while (*p) {
        *p = tolower((unsigned char)*p);
        p++;
    }
    return str;
}

/* Função para ler um arquivo e o inserir na lista de arquivos */
void AdicionaArquivo (TLista *ListaArquivos) {
    TItem item;

    printf("Entre com o nome do arquivo que voce deseja adicionar: ");
    scanf("%s", item.arq.nome_arquivo);
    item.arq.entrada = fopen(item.arq.nome_arquivo, "r");
    if (item.arq.entrada) {
        printf("Arquivo válido\n");
        item.arq.termos_distintos = 0;
        item.arq.relevancia = (float)0;
        insereLista(ListaArquivos, &item);
    }
    else
        printf("Arquivo inválido\n");
}

/* Fecha todos os arquivos da lista de arquivos */
void FechaArquivos (TLista *ListaArquivos) {
    TCelula *celula;
    celula = ListaArquivos->primeiro->prox;
    while (celula != NULL) {
        fclose(celula->item.arq.entrada); /* Fecha o arquivo atual */
        celula = celula->prox; /* Passa para a próxima célula */
    }
}

/* Calcula os pesos de todas as palavras da arvore Patricia de acordo com o numero N de documentos da coleção */
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
            celula = celula->prox; /* Passa para a próxima celula */
        }
        return;
    }
    if(!ConfereTipoNo(no)) /* Se for nó interno */
        CalculaPesos(no->NO.NInterno.Dir, N); /* Chamada recursivamente para o nó à direita */
}

/* Calcula a quantidade de termos distintos do documento arq */
void CalculaTermosDistintos (TipoPatNo *no, TCelula *arq, int idDoc) {
    TCelula *celula;

    if (no == NULL)
        return;

    /* Se o nó atual for um nó interno, chama recursivamente para o nó à esquerda */
    if(!ConfereTipoNo(no))
        CalculaTermosDistintos(no->NO.NInterno.Esq, arq, idDoc);

    /* Se o nó atual for um nó externo, confere se a palavra dele se encontra no idDoc do documento arq */
    if (ConfereTipoNo(no)) {
        celula = no->NO.NExterno.Lista.primeiro->prox;
        while (celula != NULL) {
            if (celula->item.termo.idDoc == idDoc) {
                arq->item.arq.termos_distintos++; /* Encontrou, logo incrementa a quantidade de termos distintos do documento arq */
                break; /* Sai do while */
            }
            celula = celula->prox; /* Passa para a próxima célula se já não tiver achado */
        }
        return;
    }

    /* Se o nó atual for um nó interno, chama recursivamente para o nó à direita */
    if(!ConfereTipoNo(no))
        CalculaTermosDistintos(no->NO.NInterno.Dir, arq, idDoc);
}

/* Calcula a relevância de todos os documentos da lista de arquivos de acordo com todos os termos de busca */
void CalculaRelevancia (TipoPatNo *no, TLista *ListaArquivos, char **palavras, int n_termos) {
    float somatorio = (float)0;
    int i;
    TCelula *celula;

    celula = ListaArquivos->primeiro->prox; /* Começa do primeiro documento da lista de arquivos */
    while (celula != NULL) {
        for (i=0; i<n_termos; i++) { /* Soma os pesos de todos os termos de busca no documento atual */
            somatorio += RetornaPesoTermo(palavras[i], no, celula->item.arq.idDoc);
        }
        /* Calcula a relevância */
        celula->item.arq.relevancia = (float)(somatorio / celula->item.arq.termos_distintos);
        somatorio = (float)0; /* Somatório é zerado para começar a contar para o próximo documento da lista de arquivos */
        celula = celula->prox; /* Passa para o próximo documento */
    }
    OrdenaListaArquivos(ListaArquivos);
    celula = ListaArquivos->primeiro->prox; /* Começa do primeiro documento da lista de arquivos */
    /* Imprime os documentos por ordem decrescente de relevância */
    while (celula != NULL) {
        printf("Texto %d (%s)\n", celula->item.arq.idDoc, celula->item.arq.nome_arquivo);
        celula = celula->prox;
    }
}

/* Recebe a string de todos os termos de busca, e armazena cada termo em uma posição do vetor de strings */
void BuscaTermos (TipoPatNo *no, TLista *ListaArquivos, char *string) {
    int q_termos = 0; /* Conta a quantidade de termos de busca */
    char aux[50]; /* String auxiliar para guardar temporariamente cada palavra de busca separadamente */
    char *palavras[30]; /* Vetor de Strings - Consideramos o máximo de 30 palavras de busca */
    char c; /* Caractere auxiliar para ler caractere por caractere da string que contém todas as palavras de busca */
    int i = 0; /* Indica a posição onde c deve ser armazenado na string aux */
    int j = 0; /* Indica a posição onde a string aux deve ser armazenada no vetor palavras */
    int cont = 0; /* Indica a posição atual da string que contém todas as palavras de busca */

    strlwr(string); /* Passa a string inteira para minúscula */

    /* Enquanto não chegar no final da string */
    while (string[cont] != '\0') {
        c = string[cont];
        if (c != ' ') { /* Enquanto o caractere não for um espaço, atribui-se ele à posição i da string aux */
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
    aux[i-1] = '\0';
    q_termos++; /* Incrementa a quantidade de termos de busca */
    palavras[j] = strdup(aux); /* Atribui a string auxiliar à j-ésima string do vetor de strings */
    /* Calcula a relevância de todos os termos de busca para todos os documentos da lista de arquivos */
    CalculaRelevancia(no, ListaArquivos, palavras, q_termos); /* Calcula a relevância de todos os termos de busca para todos os documentos
                                                                 da  lista de arquivos abertos */
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
        while (!feof(celula->item.arq.entrada)) {
            i = 0; /* Posição para ser atribuído o caractere c na string */
            c = fgetc(celula->item.arq.entrada);
            /* Enquanto c for um caractere válido (não especial) */
            while (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)) || c == 39 || c == 45) {
                string[i] = c;
                c = fgetc(celula->item.arq.entrada);
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
        celula->item.arq.idDoc = idDoc;
        celula->item.arq.relevancia = (float)0;
        CalculaTermosDistintos(raizPat, celula, celula->item.arq.idDoc); /* Calcula termos distintos do documento atual */
        idDoc++; /* Incrementa o id do documento da lista */
        celula = celula->prox; /* Passa para a próxima célula */
    }
    CalculaPesos(raizPat, ListaArquivos->tamanho); /* Calcula o peso de todos os termos inseridos na árvore Patricia */
}
