#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int elem;
    struct No *prox;
}no;

typedef struct FILA{
    int tam;
    no *inicio;
    no *fim;
} Fila;

inicia_fila(Fila *fila){
    fila->tam = 0;
    fila->inicio = NULL;
    fila->fim = NULL;
}

void inserir_fila(Fila *fila, int elem){
    no *novo = malloc(sizeof(no));
    novo->elem = elem;
    novo->prox = NULL;
    if(fila->fim == NULL){ //inser��o em fila vazia
        fila->inicio = novo;
        fila->fim = novo;
        printf("\nElemento %d na fila\n", elem);
        fila->tam++;
    }
    else{
        fila->fim->prox = novo;
        fila->fim = novo;
        printf("\nElemento %d na fila\n", elem);
        fila->tam++;
    }
}

void remover_fila(Fila *fila){
    if(fila->inicio == NULL){
        printf("\nNao eh possivel remover de fila vazia\n");
        return 0;
    }
    no *novo = fila->inicio;
    fila->inicio = fila->inicio->prox;
    if(fila->inicio == NULL){ //fila ficou vazia
        fila->fim = NULL;
    }
    free(novo);
    printf("\n1o Elemento removido\n");
}

int consulta_fila(Fila *fila){
    if(fila->inicio == NULL){
        printf("\nNao ha ninguem na fila moreh\n");
        return 0;
    }
    return fila->inicio->elem;
}



void impressao_fila(Fila *fila){
     no *aux = fila->inicio;
     printf("======================");
     printf("\nElementos da fila:");
     for(int i=0; i<fila->tam; i++){
        printf("\n%d", aux->elem);
        aux = aux->prox;
    }
    printf("\n======================");
}


int main()
{
    Fila fi;
    int x;
    inicia_fila(&fi);
    inserir_fila(&fi, 5);
    inserir_fila(&fi, 90);
    inserir_fila(&fi, 13);
    inserir_fila(&fi, 24);
    inserir_fila(&fi, 89);
    inserir_fila(&fi, 27);
    x = consulta_fila(&fi);
    printf("\nPrimeiro elemento eh %d\n", x);
    remover_fila(&fi);
    x = consulta_fila(&fi);
    printf("\nPrimeiro elemento eh %d\n", x);
    inserir_fila(&fi, 800);
    x = consulta_fila(&fi);
    printf("\nPrimeiro elemento eh %d\n", x);
    impressao_fila(&fi);
    return 0;
}

