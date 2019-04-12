#include <stdio.h>
#include <stdlib.h>

typedef struct bloco {
    struct bloco *prox;
    int **matriz;
    int linha, coluna;
} Nodo;

void inicializaLista(Nodo **N) {
 *N = NULL;
}

Nodo * Cria_Nodo() {
    Nodo *p;
    p = (Nodo *) malloc(sizeof(Nodo));

    if(!p) {
        printf("Problema de alocação");
        exit(0);
    }

    return p;
}

void imprimeLista(Nodo *N) {
    Nodo *aux;
    int i, j;
    if(N == NULL){
        printf("\n A lista está vazia!!");
    }
    else{
        for(aux = N; aux != NULL; aux = aux->prox){
            for(i = 0; i < aux->linha; i++){
                for(j = 0; j < aux->coluna; j++){
                    printf("%d ", aux->matriz[i][j]);
                }
                printf("\n");
            }
        }
    }
}

void insereInicioLista(Nodo **N, int ***matriz, int linha, int coluna) {
    Nodo *novo;
    novo = Cria_Nodo();
    novo->matriz = matriz;
    novo->prox = *N;
    novo->linha = linha;
    novo->coluna = coluna;
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

 void imprimeMatriz(int **matriz, int linha, int coluna){
 int i, j;
    for(i = 0; i < linha; i++){
        for(j = 0; j < coluna; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
 }

void main(){
    int linha, coluna, i, j;
    Nodo *lista;
    inicializaLista(&lista);

    printf("linha: ");
    scanf("%d", &linha);
    printf("coluna: ");
    scanf("%d", &coluna);


    int **matriz = criarMatriz(linha, coluna);
    leMatriz(matriz, linha, coluna);
    insereInicioLista(&lista, matriz, linha, coluna);
    imprimeLista(lista);


}
