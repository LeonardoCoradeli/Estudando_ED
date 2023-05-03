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

void ini(Matriz *matriz){
    for(int i = 0; i < n_linhas; i++){
        matriz->linhas[i] = NULL;
    }
    for(int i = 0; i < n_colunas; i++){
        matriz->colunas[i] = NULL;
    }
}

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
    No *aux = matriz->colunas[coluna];
    No *anterior = NULL;

    // Encontrar o nó anterior ao nó a ser removido na coluna
    while (aux != NULL && aux->linha < linha) {
        anterior = aux;
        aux = aux->baixo;
    }

    // Atualizar os ponteiros para remover o nó
    if (anterior != NULL) {
        anterior->baixo = aux->baixo;
    } else {
        matriz->colunas[coluna] = aux->baixo;
    }

    free(aux);

    aux = matriz->linhas[linha];
    anterior = NULL;

    // Encontrar o nó anterior ao nó a ser removido na linha
    while (aux != NULL && aux->coluna < coluna) {
        anterior = aux;
        aux = aux->direita;
    }

    // Atualizar os ponteiros para remover o nó
    if (anterior != NULL) {
        anterior->direita = aux->direita;
    } else {
        matriz->linhas[linha] = aux->direita;
    }

    free(aux);
}

void buscar(Matriz *matriz,int info){
    for(int i=0;i<n_linhas;i++){
        No *aux=matriz->linhas[i];
        for(int j=0;j<n_colunas;j++){
            if(aux !=NULL && aux->elem!=info){
            aux=aux->direita;
            }
            else if(aux!=NULL){
                printf("Elemento encontrado na linha %d e coluna %d\n",i,aux->coluna);
                break;
            }
        }
    }
}

int main(){
    Matriz matriz;
    ini(&matriz);
    inserir(&matriz,0,0,1);
    inserir(&matriz,0,1,1);
    inserir(&matriz,2,1,1);
    inserir(&matriz,1,1,1);
    inserir(&matriz,2,2,2);
    inserir(&matriz,3,3,3);
    inserir(&matriz,4,4,4);
    imprimir(&matriz);
    remover(&matriz,0,1);
    printf("\n");
    imprimir(&matriz);
    printf("\n");
    buscar(&matriz,2);
    return 0;
}