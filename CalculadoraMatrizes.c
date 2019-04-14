#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bloco {
    struct bloco *prox;
    int **matriz;
    int linha, coluna;
    char nome [50];
} Nodo;

void inicializaLista(Nodo **N) {
 *N = NULL;
}

Nodo * Cria_Nodo() {
    Nodo *p;
    p = (Nodo *) malloc(sizeof(Nodo));

    if(!p) {
        printf("Problema de aloca��o");
        exit(0);
    }

    return p;
}

void imprimeLista(Nodo *N) {
    Nodo *aux;
    int i, j;
    if(N == NULL){
        printf("\n A lista est� vazia!!");
    }
    else{
        for(aux = N; aux != NULL; aux = aux->prox){
            printf("\n-----------------\n\n");
            printf("%s\n\n", aux->nome);
            for(i = 0; i < aux->linha; i++){
                for(j = 0; j < aux->coluna; j++){
                    printf("%d ", aux->matriz[i][j]);
                }
                printf("\n");
            }
            printf("\n-----------------\n");
        }
    }
}

void insereInicioLista(Nodo **N, int ***matriz, int linha, int coluna, char *nome) {
    Nodo *novo;
    novo = Cria_Nodo();
    novo->matriz = matriz;
    novo->prox = *N;
    novo->linha = linha;
    novo->coluna = coluna;
    strcpy(novo->nome, nome);
    *N = novo;
}

int **criarMatriz (int linha, int coluna){
    int **m;
    int i;
    if (linha < 1 || coluna < 1) {
        printf ("Numero de linhas ou colunas invalido.\n");
        return 0;
    }

    m = (int **) malloc (sizeof(int *));

    if (!m) {
        printf ("Problema de alocacao.");
        return 0;
     }

    for (i = 0; i < linha; i++ ) {
        m[i] = (int *) malloc (sizeof(int));
        if (!m[i]) {
            printf ("Problema de alocacao.");
            return 0;
         }
    }
    return m;
}

void leMatriz(int **matriz, int lin, int col){
     int i, j;

     printf("\nDigite os valores: \n\n");

     for(i = 0;i < lin; i++){
        for(j = 0; j < col; j++){
            printf("[%d][%d]: ", i, j);
             scanf("%d", &matriz[i][j]);
         }
        printf("\n");
     }
 }

 int** buscarMatriz(Nodo **N, char **nome){
    Nodo *aux;
    int i, j;
    if(N == NULL){
        printf("\n A lista est� vazia!!");
    }
    else{
        for(aux = N; aux != NULL; aux = aux->prox){
            if(!strcmp(aux->nome, nome)){
                printf("\nAchou\n");
                return aux->matriz;
            }
        }
    }

 }

 void transporMatriz(Nodo *N, char *nome){
    buscarMatriz(N, nome);
 }

void main(){
    int linha, coluna, opcao = 0;
    char nome [50];
    Nodo *lista;
    inicializaLista(&lista);

    do{

        printf("********************************\n");
        printf("*                              *\n");
        printf("* 1 - DECLARAR UMA MATRIZ      *\n");
        printf("* 2 - TRANSPOR UMA MATRIZ      *\n");
        printf("*                              *\n");
        printf("********************************\n");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("Nome da matriz: ");
                scanf("%s", nome);
                printf("linha: ");
                scanf("%d", &linha);
                printf("coluna: ");
                scanf("%d", &coluna);
                int **matriz = criarMatriz(linha, coluna);
                leMatriz(matriz, linha, coluna);
                insereInicioLista(&lista, matriz, linha, coluna, nome);
                imprimeLista(lista);
            break;
            case 2:
                printf("Nome da matriz a ser transposta: ");
                scanf("%s", nome);
                transporMatriz(lista, nome);
            break;

        }

    } while(opcao != 0);




}
