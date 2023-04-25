#include <stdio.h>

#define MAX 11
typedef struct
{
    int elem;
    int prox;
}reg;
typedef struct{
    int disp;
    int prim;
    int tam;
    reg A[MAX];
}lista;

void InicializaLista(lista *l1)
{
    int i;
    l1->disp = 0;
    l1->prim = -1;
    l1->tam =0;
    for(i=0 ; i<MAX ; i++)
        {l1->A[i].prox=i+1;}
    l1->A[i].prox= -1;
}
void InserirLista(lista *l1,int info){
    if (l1->tam!=MAX){
        l1->A[l1->disp].elem = info;
        int aux=l1->A[l1->disp].prox;
        l1->A[l1->disp].prox=-1;
        l1->tam++;

        if (l1->prim!=-1){
            int anterior=-1,i=l1->prim;

            while (i!=-1 && l1->A[i].elem < info){
                anterior=i;
                i=l1->A[i].prox;
            }
            if(anterior!=-1){
                l1->A[l1->disp].prox = l1->A[anterior].prox;
                l1->A[anterior].prox = l1->disp;

            }
            else {
                if(i!=-1){
                    l1->A[l1->disp].prox = i;
                    l1->prim = l1->disp;
                }
            }

        }
        else{
            l1->A[l1->disp].elem=info;
            l1->prim=l1->disp;
        }
        l1->disp=aux;
    }
    else{
        printf("Lista cheia!\n");
    }
}

void RemoverLista(lista *l1,int info){
    int anterior=-1,i=l1->prim;

    if(l1->prim!=-1){
        if(l1->tam>1) {
            while (i != -1 && info < l1->A[i].elem) {
                anterior = i;
                i = l1->A[i].prox;
            }
            if (i != -1 && info == l1->A[i].elem) {
                if (anterior == -1) {
                    l1->disp = 1;
                    l1->prim = l1->A[i].prox;
                } else {
                    l1->disp = l1->A[anterior].prox;
                    l1->A[anterior].prox = l1->A[i].prox;
                }
                l1->A[i].prox = l1->disp;
                l1->tam--;
            }
        }
            else if(info==l1->A[i].elem){
                l1->prim=-1;
                l1->A[i].prox=l1->disp;
                l1->disp=i;
                l1->tam--;
            }
        }
    else{
        printf("Lista vazia!\n");
    }
}


void BuscarLista(lista *l1,int info){
    int i=l1->prim,cont=0;
    while (i!=-1 && l1->A[i].elem != info){
        i=l1->A[i].prox;
        cont++;
    }
    if(i!=-1){
        printf("Elemento encontra-se na posicao %d do vetor sendo o %d da lista\n",i,cont+1);
    } else {
        printf("Elemento nao encontrado na lista!\n");
    }
    return;
}


int main(){
    lista l1;
    InicializaLista(&l1);
    InserirLista(&l1,5);
    InserirLista(&l1,10);
    InserirLista(&l1,8);
    BuscarLista(&l1,10);
    RemoverLista(&l1,5);
    BuscarLista(&l1,10);
    return 0;
}
