#include <stdio.h>
#include <stdlib.h>

typedef struct NO{
    int elem;
    int prioridade;
    struct NO *prox;
}No;

typedef struct{
    No *primeiro,*ultimo;
    int tam;
}Fila;

void ini(Fila *fila){
    fila->primeiro=NULL;
    fila->ultimo=NULL;
    fila->tam=0;
}

void inserir(Fila *fila, int elem,int prioridade) {
    No *novo = malloc(sizeof(No));
    novo->elem = elem;
    novo->prioridade=prioridade;
    novo->prox=NULL;
    
    if (fila->primeiro==NULL) {
        fila->primeiro = novo;
        fila->ultimo = novo;
    } else {
        No *aux=fila->primeiro;
        while (aux->prox != NULL && aux->prioridade <= prioridade) {
            aux = aux->prox;
        }
        novo->prox = aux->prox;
        aux->prox = novo;
    }
}


void imprimir(Fila *fila){
    No *aux=fila->primeiro;
    while(aux!=NULL){
        printf("%d\n",aux->elem);
        aux=aux->prox;
    }
}

void remover(Fila *fila, int posicao) {
    No *aux = fila->primeiro;
    for (int i = 0; i < posicao - 1; i++) {
        aux = aux->prox;
    }
    No *no_remover = aux->prox;
    aux->prox = aux->prox->prox;
    free(no_remover);
}


void buscar(Fila *fila,int valor){
    No *aux=fila->primeiro;
    int cont=0;
    while(aux!=NULL && aux->elem<=valor){
        if(aux->elem==valor){
            printf("O valor %d foi encontrado na posicao %d",valor,cont);
            return;
        }
        else{
            aux=aux->prox;
        }
        cont++;
    }
    printf("O valor nao foi encontrado na Fila");
}

int main()
{
    Fila fila;
    ini(&fila);
    inserir(&fila,10,0);
    inserir(&fila,15,0);
    inserir(&fila,11,0);
    inserir(&fila,13,0);
    inserir(&fila,1,1);
    inserir(&fila,6,1);
    inserir(&fila,8,1);
    inserir(&fila,13,2);
    imprimir(&fila);
    remover(&fila,2);
    printf("\n");
    imprimir(&fila);
    return 0;
}
