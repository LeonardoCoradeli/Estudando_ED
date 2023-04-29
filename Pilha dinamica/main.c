#include <stdio.h>
#include <stdlib.h>

typedef struct NO{
    struct NO *prox;
    struct NO *ant;
    int info;
}no;

typedef struct{
    no *inicio;
    no *fim;
    int tam;
}Pilha;

void ini(Pilha *pilha){
    pilha->inicio = NULL;
    pilha->fim = NULL;
    pilha->tam = 0;
}

void push(Pilha *pilha,int elem){
    no *novo = (no*)malloc(sizeof(no));
    novo->info = elem;
    novo->prox = NULL;
    novo->ant = NULL;
    if(pilha->inicio == NULL){
        pilha->inicio = novo;
        pilha->fim = novo;
    }else{
        novo->ant = pilha->fim;
        pilha->fim->prox = novo;
        pilha->fim = novo;
    }
    pilha->tam++;
}

void pop(Pilha *pilha){
    no *aux=pilha->fim;
    if(pilha->inicio == NULL){
        printf("Pilha vazia\n");}
    else{
        pilha->fim->ant->prox = NULL;
        pilha->fim = pilha->fim->ant;
        free(aux);
    }
}

void print(Pilha *pilha){
    no *aux = pilha->fim;
    printf("Na ordem em que os elementos vao sair:\n");
    while(aux != NULL){
        printf("%d\n",aux->info);
        aux = aux->ant;
    }
}

int main()
{
    Pilha pilha;
    ini(&pilha);
    push(&pilha,1);
    push(&pilha,2);
    push(&pilha,3);
    push(&pilha,4);
    print(&pilha);
    pop(&pilha);
    print(&pilha);
    return 0;
}
