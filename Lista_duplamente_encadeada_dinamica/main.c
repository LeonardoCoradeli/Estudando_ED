#include <stdio.h>
#include <stdlib.h>

typedef struct No{//elementos da lista
    int info;
    struct No *prox;
    struct No *ant;
}no;

typedef struct LISTA{//descritor, mostra o tamanho, incio e fim da lista, com ele não é necessario usar ponteiro de ponteiro nas funções
    int tam;//esse tamanho sera util na função de busca
    no *inic;
    no *fim;
}Lista;

void ini(Lista *lista){
    lista->tam=0;
    lista->fim=NULL;
    lista->inic=NULL;
}

void inserir(Lista *lista, int elem) {
    no *novo = malloc(sizeof(no));
    novo->info = elem;
    novo->prox = NULL;
    novo->ant = NULL;
    if (lista->inic == NULL && lista->fim == NULL) {
        lista->inic = novo;
        lista->fim = novo;
        lista->tam++;
    } else {
        no *aux = lista->inic;
        if (aux->info >= elem) {
            novo->prox = aux;
            aux->ant = novo;
            lista->inic = novo;
            lista->tam++;
            }
        else if (lista->fim->info < elem) {
            novo->ant = lista->fim;
            lista->fim->prox = novo;
            lista->fim = novo;
            lista->tam++;
            }
        else {
            while (aux->prox != NULL && aux->info < elem) {
                aux = aux->prox;
            }
            novo->prox = aux;
            novo->ant = aux->ant;
            aux->ant->prox = novo;
            aux->ant = novo;
            lista->tam++;
        }
    }
}

void remover(Lista *lista,int elem){
    if(lista->inic==NULL && lista->fim==NULL){
        printf("Voce não pode remover pois essa lista esta vazia!\n");
    }
    else{
        if(lista->inic==lista->fim){
            free(lista->inic);
            free(lista->fim);
            ini(lista);
            printf("Elemento %d removido com sucesso!\n", elem);
        }
        else{
            if(lista->inic->info==elem){
                lista->inic->prox->ant=NULL;
                lista->tam--;
                lista->inic=lista->inic->prox;
                free(lista->inic->ant);
                printf("Elemento %d removido com sucesso!\n", elem);
            }
            else if(lista->fim->info==elem){
                lista->fim->ant->prox=NULL;
                lista->tam--;
                lista->fim=lista->fim->ant;
                free(lista->fim->prox);
                printf("Elemento %d removido com sucesso!\n", elem);
            }
            else{
                no *aux=lista->inic;
                while(aux!=NULL && aux->info<elem){
                    aux=aux->prox;
                }
                if(aux==NULL){
                    printf("Esse elemento não existe na lista!\n");
                }
                else{
                    aux->ant->prox=aux->prox;
                    aux->prox->ant=aux->ant;
                    free(aux);
                    lista->tam--;
                    printf("Elemento %d removido com sucesso!\n", elem);
                }
            }
        }
    }
}


void mostrar(Lista *lista){
    no *aux=lista->inic;
    for(int i=0;i<lista->tam;i++){
        printf("%d\n",aux->info);
        aux=aux->prox;
    }
}
void buscar(Lista *lista,int elem){
    if(lista->inic->info==elem){
        printf("Elemento %d encontrado na posicao 0\n",elem);
    }
    else if(lista->fim->info==elem){
        printf("Elemento %d encontrado na posicao %d\n",elem,lista->tam-1);
    }
    else{
        no *aux=lista->inic;
        int cont=0;
        while(aux!=NULL && aux->info<elem){
            aux=aux->prox;
            cont++;
        }
        if(aux==NULL){
            printf("O elemento %d nao existe na lista\n",elem);
        }
        else{
            printf("o elemento %d foi encontrado na posicao %d",elem,cont);
        }
    }

}

int main()
{
    Lista lista;
    ini(&lista);
    inserir(&lista,1);
    inserir(&lista,2);
    inserir(&lista,3);
    inserir(&lista,4);
    inserir(&lista,5);
    inserir(&lista,6);
    mostrar(&lista);
    remover(&lista,3);
    buscar(&lista,2);
    return 0;
}
