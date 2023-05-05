#include <stdio.h>
#include <stdlib.h>

typedef struct NO{
    int elem;
    int prioridade;
    struct NO *prox;
}No;

typedef struct{
    No *primeiro;
    int tam;
}Fila;

void ini(Fila *fila){
    fila->primeiro=NULL;
    fila->tam=0;
}

void inserir(Fila *fila, int elem,int prioridade) {
    No *novo = malloc(sizeof(No));
    novo->elem = elem;
    novo->prioridade=prioridade;
    novo->prox=NULL;
    
    if (fila->primeiro==NULL) {
        fila->primeiro = novo;
        fila->tam++;
    } 
    else if(fila->primeiro->prioridade>prioridade){
        novo->prox = fila->primeiro;
        fila->primeiro=novo;
        fila->tam++;
    }
    else {
        No *aux=fila->primeiro;
        while (aux->prox != NULL && aux->prox->prioridade <= prioridade) {
            aux = aux->prox;
        }
        if (aux->prox==NULL){
            aux->prox=novo;
            fila->tam++;
        }
        else{
            novo->prox = aux->prox;
            aux->prox = novo;
            fila->tam++;
        }
        
    }
}


void imprimir(Fila *fila){
    No *aux=fila->primeiro;
    while(aux!=NULL){
        printf("%d\n",aux->elem);
        aux=aux->prox;
    }
}

void remover(Fila *fila) {
    if(fila->primeiro==NULL){
        printf("Essa fila esta vazia\n");
        return;}
    No *aux=fila->primeiro;
    fila->primeiro=aux->prox;
    free(aux);
    fila->tam--;
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
    inserir(&fila,10,1);
    inserir(&fila,15,1);
    inserir(&fila,11,1);
    inserir(&fila,13,1);
    inserir(&fila,1,1);
    inserir(&fila,6,1);
    inserir(&fila,8,1);
    inserir(&fila,13,2);
    imprimir(&fila);
    printf("\n");
    inserir(&fila,23,0);
    inserir(&fila,14,0);
    remover(&fila);
    printf("\n");
    imprimir(&fila);
    return 0;
}
