//Alunos: Fernanda Moraes Costa & Lucas Matheus Passos da Silva

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
        printf("Problema de alocao");
        exit(0);
    }

    return p;
}


void imprimeLista(Nodo *N) {
    Nodo *aux;
    int i, j;
    if(N == NULL){
        printf("\n A lista esta vazia!!");
    }
    else{
        for(aux = N; aux != NULL; aux = aux->prox){
            imprimeMatriz(N, aux->nome);
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

    m = (int **) malloc (linha * sizeof(int *));

    if (!m) {
        printf ("Problema de alocacao.");
        return 0;
     }

    for (i = 0; i < linha; i++ ) {
        m[i] = (int *) malloc (coluna * sizeof(int));
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

 Nodo* buscarMatriz(Nodo *N, char *nome){
    Nodo *aux;
    int i, j;
    if(N == NULL){
        printf("\n A lista esta vazia!!");
    }
    else{
        for(aux = N; aux != NULL; aux = aux->prox){
            if(!strcmp(aux->nome, nome)){
                return aux;
            }
        }
    }

 }

 void retiraLista(Nodo *N, char *nome){
    Nodo *aux;
    aux = N;
    if(N == NULL){
        printf("\n A lista esta vazia!!");
    }else if(strcmp(N->nome, nome)){
        if(N->prox == NULL){
            N = N->prox;
        }else{
            free(N);
            N = Cria_Nodo();
        }
    }
    else if(N->prox != NULL){
        for(; N->prox != NULL; N = N->prox){
            if(!strcmp(N->prox->nome, nome)){
                if(N->prox->prox != NULL){
                    N->prox = N->prox->prox;
                }else{
                    N->prox = NULL;
                }
            }
        }
        N = aux;
    }
 }

 void transporMatriz(Nodo **Lista, char *nome, char *nomeTransposta){
    Nodo *matrizEncontrada = buscarMatriz(Lista, nome);
    int i,j;

    int linhaMatriz = matrizEncontrada->coluna;
    int colunaMatriz = matrizEncontrada->linha;
    int **matriz = criarMatriz(linhaMatriz, colunaMatriz);

    for(i = 0; i < matrizEncontrada->linha; i++){
        for(j = 0; j < matrizEncontrada->coluna; j++){
            matriz[j][i] = matrizEncontrada->matriz[i][j];
        }
    }

    insereInicioLista(Lista, matriz, linhaMatriz, colunaMatriz, nomeTransposta);
    imprimeLista(Lista);

 }

 void somaMatrizes(Nodo **Lista, char *nomeMatriz1, char *nomeMatriz2, char *nomeSoma){
    Nodo *matriz1 = buscarMatriz(Lista, nomeMatriz1);
    Nodo *matriz2 = buscarMatriz(Lista, nomeMatriz2);
    int i, j;
    int **matrizResultante;

    printf("\nmatriz 1: %s", matriz1->nome);
    printf("\nmatriz 2: %s", matriz2->nome);

    if(mesmoTamanhoMatrizes(matriz1, matriz2)){
        matrizResultante = criarMatriz(matriz1->linha, matriz2->coluna);
        for(i = 0; i < matriz1->linha; i++){
            for(j = 0; j < matriz1->coluna; j++){
                matrizResultante[i][j] = matriz1->matriz[i][j] + matriz2->matriz[i][j];
            }
        }

        insereInicioLista(Lista, matrizResultante, matriz1->linha, matriz1->coluna, nomeSoma);
        imprimeMatriz(Lista, nomeSoma);
    }

 }

 void multiplicaMatrizes(Nodo **Lista, char *nomeMatriz1, char *nomeMatriz2, char *nomeMultiplica){
    Nodo *matriz1 = buscarMatriz(Lista, nomeMatriz1);
    Nodo *matriz2 = buscarMatriz(Lista, nomeMatriz2);
    int i, j, k;

    int **matrizResultante;

    printf("\nmatriz 1: %s", matriz1->nome);
    printf("\nmatriz 2: %s", matriz2->nome);

    if(possivelMultiplicar(matriz1, matriz2)){
        matrizResultante = criarMatriz(matriz1->linha, matriz2->coluna);
        for(i = 0; i < matriz1->linha; i++){
            for(j = 0; j < matriz2->coluna; j++){
                for(k = 0; k < matriz1->coluna; k++){
                    matrizResultante[i][j] = matrizResultante[i][j] + (matriz1->matriz[i][k] * matriz2->matriz[k][j]);
                }
            }
        }
        insereInicioLista(Lista, matrizResultante, matriz1->linha, matriz2->coluna, nomeMultiplica);
        imprimeMatriz(Lista, nomeMultiplica);
    }

 }

 void divideMatrizes(Nodo **Lista, char *nomeMatriz1, char *nomeMatriz2, char *nomeMultiplica){
    Nodo *matriz1 = buscarMatriz(Lista, nomeMatriz1);
    Nodo *matriz2 = buscarMatriz(Lista, nomeMatriz2);
    int i, j;

    int **matrizResultante;

    if(possivelDividir(matriz1, matriz2)){
        matrizResultante = criarMatriz(matriz1->linha, matriz1->coluna);
        for(i = 0; i < matriz1->linha; i++){
            for(j = 0; j < matriz1->coluna; j++){
                matrizResultante[i][j] = matriz1->matriz[i][j] / matriz2->matriz[i][j];
            }
        }
        insereInicioLista(Lista, matrizResultante, matriz1->linha, matriz2->coluna, nomeMultiplica);
        imprimeMatriz(Lista, nomeMultiplica);
    }

}

void destroiMatriz(Nodo *Lista, char *nomeMatriz1){
    Nodo *matriz = buscarMatriz(Lista, nomeMatriz1);
    if(matriz != NULL){
        int i;

        for(i = 0; i < matriz->linha; i++){
            free(matriz->matriz[i]);
        }
        free(matriz->matriz);
        retiraLista(Lista, nomeMatriz1);
    }
}


int possivelDividir(Nodo *matriz1, Nodo *matriz2){
    int i, j;
    if(mesmoTamanhoMatrizes(matriz1, matriz2)){
        for(i = 0; i < matriz2->linha; i++){
            for(j = 0; j < matriz2->coluna; j++){
                if(matriz2->matriz[i][j] == 0){
                    return 0;
                }
            }
        }
        return 1;
    }else{
        return 0;
    }
 }

 int possivelMultiplicar(Nodo *matriz1, Nodo *matriz2){
    if(matriz1->coluna == matriz2->linha){
        return 1;
    }else{
        return 0;
    }
 }

 int mesmoTamanhoMatrizes(Nodo *matriz1, Nodo *matriz2){
    if(matriz1->linha != matriz2->linha && matriz1->coluna != matriz2->coluna){
        return 0;
    }
    return 1;
 }

 void diagonalPrimariaMatriz(Nodo *lista, char *nome){
    Nodo *matriz = buscarMatriz(lista, nome);
    int i,j;

    imprimeMatriz(lista, nome);
    printf("\n\n-----  DIAGONAL PRIMARIA  -------\n\n");

    for(i = 0; i < matriz->linha; i++){
        for(j = 0; j < matriz->coluna; j++){
            if(i == j){
                printf("%d ", matriz->matriz[i][j]);
            }
        }
    }
    printf("\n\n");

 }

 void imprimeMatriz(Nodo *lista, char *nome){
    Nodo *matriz = buscarMatriz(lista, nome);
    int i, j;
    printf("\n-----------------\n\n");
    printf("%s\n\n", matriz->nome);
    for(i = 0; i < matriz->linha; i++){
        for(j = 0; j < matriz->coluna; j++){
            printf("%d ", matriz->matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n-----------------\n");
 }

 void subtraiMatrizes(Nodo **Lista, char *nomeMatriz1, char *nomeMatriz2, char *nomeSoma){
    Nodo *matriz1 = buscarMatriz(Lista, nomeMatriz1);
    Nodo *matriz2 = buscarMatriz(Lista, nomeMatriz2);
    int i, j;
    int **matrizResultante;

    printf("\nmatriz 1: %s", matriz1->nome);
    printf("\nmatriz 2: %s", matriz2->nome);

    if(mesmoTamanhoMatrizes(matriz1, matriz2)){
        matrizResultante = criarMatriz(matriz1->linha, matriz2->coluna);
        for(i = 0; i < matriz1->linha; i++){
            for(j = 0; j < matriz1->coluna; j++){
                matrizResultante[i][j] = matriz1->matriz[i][j] - matriz2->matriz[i][j];
            }
        }

        insereInicioLista(Lista, matrizResultante, matriz1->linha, matriz1->coluna, nomeSoma);
        imprimeMatriz(Lista, nomeSoma);
    }
 }


void main(){
    int linha, coluna, opcao = 0;
    char nome [50], nome2[50], nome3[50];
    Nodo *lista;
    inicializaLista(&lista);

    do{

        printf("*************************************\n");
        printf("*                                   *\n");
        printf("* 1 - DECLARAR UMA MATRIZ           *\n");
        printf("* 2 - TRANSPOR UMA MATRIZ           *\n");
        printf("* 3 - SOMA DE DUAS MATRIZES         *\n");
        printf("* 4 - IMPRIME MATRIZES              *\n");
        printf("* 5 - IMPRIME MATRIZ                *\n");
        printf("* 6 - DIAGONAL PRIMARIA DA MATRIZ   *\n");
        printf("* 7 - SUBTRACAO DE DUAS MATRIZES    *\n");
        printf("* 8 - MULTIPLICACAO DE DUAS MATRIZES*\n");
        printf("* 9 - DIVISAO UTILIZANDO MATRIZES   *\n");
        printf("* 10 - DESTRUIR MATRIZ              *\n");
        printf("* 0 - SAIR                          *\n");
        printf("*                                   *\n");
        printf("*************************************\n");
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
                printf("Nome da matriz transposta: ");
                scanf("%s", nome2);
                transporMatriz(lista, nome, nome2);
            break;
            case 3:
                printf("Nome da primeira matriz: ");
                scanf("%s", nome);
                printf("Nome da segunda matriz: ");
                scanf("%s", nome2);
                printf("Nome do resultado das soma: ");
                scanf("%s", nome3);
                somaMatrizes(&lista, nome, nome2, nome3);
            break;
            case 4:
              imprimeLista(lista);
            break;
            case 5:
                printf("Nome da matriz: ");
                scanf("%s", nome);
                imprimeMatriz(lista, nome);
            break;
            case 6:
                printf("Nome da matriz: ");
                scanf("%s", nome);
                diagonalPrimariaMatriz(lista, nome);
            break;
            case 7:
                printf("Nome da primeira matriz: ");
                scanf("%s", nome);
                printf("Nome da segunda matriz: ");
                scanf("%s", nome2);
                printf("Nome do resultado das subtracao: ");
                scanf("%s", nome3);
                subtraiMatrizes(&lista, nome, nome2, nome3);
            break;
            case 8:
                printf("Nome da primeira matriz: ");
                scanf("%s", nome);
                printf("Nome da segunda matriz: ");
                scanf("%s", nome2);
                printf("Nome do resultado da multiplicacao: ");
                scanf("%s", nome3);
                multiplicaMatrizes(&lista, nome, nome2, nome3);
            break;
            case 9:
                printf("Nome da primeira matriz: ");
                scanf("%s", nome);
                printf("Nome da segunda matriz: ");
                scanf("%s", nome2);
                printf("Nome do resultado da multiplicacao: ");
                scanf("%s", nome3);
                divideMatrizes(&lista, nome, nome2, nome3);
            break;
            case 10:
                printf("Nome da matriz: ");
                scanf("%s", nome);
                destroiMatriz(&lista, nome);
            break;
        }

    } while(opcao != 0);

    free(lista);

}
