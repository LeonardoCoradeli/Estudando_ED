#include <stdio.h>
#include <stdlib.h>

typedef struct tipolista{
    int elem;
    struct tipolista *proximo;
}Lista;

void ini(Lista **lista){
    *lista=NULL;
}

void inserir(Lista **lista, int elem) {
    Lista *novo = malloc(sizeof(Lista));
    novo->elem = elem;
    novo->proximo = NULL;

    if (*lista == NULL) {
        *lista = novo;
    } else {
        Lista *aux = *lista;
        while (aux->proximo != NULL && aux->elem <= elem) {
            aux = aux->proximo;
        }
        novo->proximo = aux->proximo;
        aux->proximo = novo;
    }
}


void imprimir(Lista **lista){
    Lista *aux=*lista;
    while(aux!=NULL){
        printf("%d\n",aux->elem);
        aux=aux->proximo;
    }
}

void remover(Lista **lista,int posicao){
    Lista *aux=*lista;
    Lista *ant;
    Lista *pro;
    for(int i=0;i<posicao-1;i++){
        aux=aux->proximo;
    }
    ant=aux;
    aux=aux->proximo;
    pro=aux->proximo;
    free(aux);
    ant->proximo=pro;
}

void buscar(Lista **lista,int valor){
    Lista *aux=*lista;
    int cont=0;
    while(aux!=NULL && aux->elem<=valor){
        if(aux->elem==valor){
            printf("O valor %d foi encontrado na posicao %d",valor,cont);
            return;
        }
        else{
            aux=aux->proximo;
        }
        cont++;
    }
    printf("O valor nao foi encontrado na lista");
}

int main()
{
    Lista *lista;
    ini(&lista);
    inserir(&lista,1);
    inserir(&lista,2);
    inserir(&lista,3);
    imprimir(&lista);
    remover(&lista,1);
    imprimir(&lista);
    buscar(&lista,3);
    return 0;
}
