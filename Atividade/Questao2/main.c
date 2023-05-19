#include <stdio.h>
#include <stdlib.h>

#define n_linhas 5
#define n_colunas 5

typedef struct NO{
    int elem, linha, coluna;
    struct NO *direita, *baixo;
}No;

typedef struct{
    No *linhas[n_linhas], *colunas[n_colunas];
}Matriz;

void inserir(Matriz *matriz, int linha, int coluna, int elem) {
    if (linha < 0 || linha >= n_linhas || coluna < 0 || coluna >= n_colunas) {
        printf("Posicao invalida, essa e uma matriz %dx%d\n", n_linhas, n_colunas);
        return;
    }

    No *novo = malloc(sizeof(No));
    novo->elem = elem;
    novo->linha = linha;
    novo->coluna = coluna;
    novo->direita = NULL;
    novo->baixo = NULL;

    if (matriz->linhas[linha] == NULL) {
        matriz->linhas[linha] = novo;
    } else {
        No *aux = matriz->linhas[linha];
        while (aux->direita != NULL && aux->direita->coluna < coluna) {
            aux = aux->direita;
        }
        novo->direita = aux->direita;
        aux->direita = novo;
    }

    if (matriz->colunas[coluna] == NULL) {
        matriz->colunas[coluna] = novo;
    } else {
        No *aux = matriz->colunas[coluna];
        while (aux->baixo != NULL && aux->baixo->linha < linha) {
            aux = aux->baixo;
        }
        novo->baixo = aux->baixo;
        aux->baixo = novo;
    }
}

void ini(Matriz *matriz){
    for(int i = 0; i < n_linhas; i++){
        matriz->linhas[i] = NULL;
    }
    for(int i = 0; i < n_colunas; i++){
        matriz->colunas[i] = NULL;
    }
    int cont=1;
    for(int i=0;i<n_linhas;i++){
        for(int j=0;j<n_colunas;j++){
            inserir(matriz,i,j,cont);
            cont++;
        }
    }
}


void imprimir(Matriz *matriz){
    for(int i=0;i<n_linhas;i++){
        No *aux=matriz->linhas[i];
        for(int j=0;j<n_colunas;j++){
            if(aux!=NULL && aux->coluna==j){
            printf(" %d ",aux->elem);
            aux=aux->direita;
            }
            else{
                printf(" 0 ");
            }
        }
        printf("\n");
    }
}

void remover(Matriz *matriz, int linha, int coluna) {
    if (linha < 0 || linha >= n_linhas || coluna < 0 || coluna >= n_colunas) {
        printf("Linha ou coluna inválida.\n");
        return;
    }

    No *aux = matriz->colunas[coluna];
    No *anterior = NULL;
    while (aux != NULL && aux->linha < linha) {
        anterior = aux;
        aux = aux->baixo;
    }
    if (aux != NULL && aux->linha == linha) {
        if (anterior != NULL) {
            anterior->baixo = aux->baixo;
        } else {
            matriz->colunas[coluna] = aux->baixo;
        }
        free(aux);
    }

    aux = matriz->linhas[linha];
    anterior = NULL;
    while (aux != NULL && aux->coluna < coluna) {
        anterior = aux;
        aux = aux->direita;
    }
    if (aux != NULL && aux->coluna == coluna) {
        if (anterior != NULL) {
            anterior->direita = aux->direita;
        } else {
            matriz->linhas[linha] = aux->direita;
        }
        free(aux);
    }
}

void somark(Matriz *matriz, int linha, int valork) {
    No *aux = matriz->linhas[linha];
    if (aux == NULL) {
        for (int i = 0; i < n_colunas; i++) {
            inserir(matriz, linha, i, valork);
        }
    } else {
        for (int i = 0; i < n_colunas; i++) {
            if (aux->coluna == i) {
                if (aux->elem + valork == 0) {
                    aux = aux->direita;
                    remover(matriz,linha,i);
                } else {
                    aux->elem = aux->elem + valork;
                    aux = aux->direita;
                }
            } else {
                inserir(matriz, linha, i, valork);
            }
        }
    }
}


int main(){
    int valork,linha;
    Matriz matriz;
    ini(&matriz);
    printf("A matriz ja foi incializada com 0,0=1 ... 4,4=25\n");
    imprimir(&matriz);
    printf("Digite um valor: ");
    scanf("%d",&valork);
    printf("e uma linha: "); 
    scanf("%d",&linha);
    somark(&matriz,linha,valork);
    printf("---------------------------------------------------------\n");
    imprimir(&matriz);
    getchar();
    return 0;
}