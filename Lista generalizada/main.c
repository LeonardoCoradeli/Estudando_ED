#include <stdio.h>
#include <stdlib.h>

typedef struct{
        int tipo_a;//tipo de dado
        union{
        int atomo_i;
        char atomo_c;
        float atomo_f;
        };
}Atomo;

typedef struct NO{
    int tipo_no;//atomo ou lista
    union{
        Atomo atomo;
        struct LISTA *lista;
    }elem;
    struct NO *prox;
    struct NO *ant;   
}No;

typedef struct LISTA{
    No *inicio;
    No *fim;
    int tam;
}Lista;

void ini(Lista *lista){
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tam = 0;
}

void insere(Lista *lista,int tipo_no,int tipo_a,void *elem/*insira -1 em tudo relacionado a elem caso lista*/,Lista *sublista/*insira NULL caso elemento*/){
    No *novo = (No*)malloc(sizeof(No));
    novo->prox = NULL;
    novo->ant = NULL;
    novo->tipo_no=tipo_no;
    if (elem == NULL && sublista==NULL) {
            printf("Nada foi inserido!\n");}// Tratar erro, não há valor válido
    else{
        if(tipo_no == 0){
            Atomo atomo;
            if(tipo_a==0){//tudo isso é para que elem seja uma variavel generica, ou seja, possa recebr qualquer tipo(no caso int,char,float)
                atomo.tipo_a=0;
                atomo.atomo_i=*((int*)elem);
            }
            else if(tipo_a==1){
                atomo.tipo_a=1;
                atomo.atomo_c=*((char*)elem);
            }
            else{
                atomo.tipo_a=2;
                atomo.atomo_f=*((float*)elem);
            }
        novo->elem.atomo=atomo;
        }else{
            novo->elem.lista = sublista;
        }
        if(lista->inicio == NULL){
            lista->inicio = novo;
            lista->fim = novo;
        }else{
            novo->ant=lista->fim;
            lista->fim->prox = novo;
            lista->fim = novo;
        }
        lista->tam++;
    }
}

void imprime(Lista *lista){
    No *aux = lista->inicio;
    while(aux != NULL){
        if(aux->tipo_no == 0){
            printf("//\n");
            if(aux->elem.atomo.tipo_a == 0){
            printf("%d\n",aux->elem.atomo.atomo_i);}
            else if(aux->elem.atomo.tipo_a == 1){
            printf("%c\n",aux->elem.atomo.atomo_c);}
            else if(aux->elem.atomo.tipo_a == 2){
            printf("%0.2f\n",aux->elem.atomo.atomo_f);}
        }
        else if(aux->elem.lista->inicio!=NULL){
            imprime(aux->elem.lista);
        }
        aux = aux->prox;
    }
}

void remover_pos(Lista *lista,int pos){//remove todo uma lista de uma vez caso esteja na posicao escolhida
    if(lista->inicio != NULL){
        No *aux;
        if(pos == 0){
            aux=lista->inicio;
            if(aux->tipo_no==0){
                lista->inicio = aux->prox;
                free(aux);
            }
            else{
                for(int i=0;i<=aux->elem.lista->tam;i++){
                    printf(".\n");
                    remover_pos(aux->elem.lista,0);
                }
                lista->inicio = aux->prox;
            }
        }
        else if(pos == (lista->tam)-1){
            aux=lista->fim;
            if(aux->tipo_no==0){
                lista->fim = aux->ant;
                free(aux);
            }
            else{
                for(int i=0;i<=aux->elem.lista->tam;i++){
                    printf("..\n");
                    remover_pos(aux->elem.lista,0);
                }
                lista->fim = aux->ant;
            }
        }
        else{
            aux=lista->inicio;
            for(int i=0;i<pos-1;i++){
                aux = aux->prox;
            }
            if(aux==NULL){
                printf("Essa posicao nao existe na lista!\n");
            }
            else{
                if(aux->tipo_no==0){
                    aux->prox->ant = aux->prox;
                    free(aux);
                }
                else{
                    for(int i=0;i<=aux->elem.lista->tam;i++){
                        printf("...\n");
                        remover_pos(aux->elem.lista,0);
                    }
                    aux->prox->ant = aux->prox;
                }
            }
        }
        lista->tam--;
    }
    else{
        printf("Teste\n");
    }
}

void remover_elem(Lista *lista,int tipo_a,void *elem){//remove um elemento da lista principal ou dentro de sublistas, remove o primeiro elemento do tipo que encontrar
    No *aux=lista->inicio;
    while(aux!=NULL){
        if(aux->tipo_no==0){
            if(aux->elem.atomo.atomo_i==*(int*)elem || aux->elem.atomo.atomo_c==*(char*)elem || aux->elem.atomo.atomo_f==*(float*)elem){
                aux->ant->prox=aux->prox;
                aux->prox->ant=aux->ant;
                free(aux);
                break;
                lista->tam--;
            }
            aux=aux->prox;
        }
        else{
            remover_elem(aux->elem.lista,tipo_a,elem);
        }
    }
}

int main()
{
    Lista lista,lista2;
    ini(&lista);
    ini(&lista2);
    //Para inserir crie uma variavel do tipo int, char ou float e insira seu endereço de memoria
    //primeiro numero 0 para atomo, 1 para sublista
    //segundo numero 0 para int, 1 para char e 2 para float
    int elem=0,elem1=1,elem2=2,elem3=3;
    char elem4='b';
    float elem5=0.5;
    int elem6=6,elem7=7,elem8=8;
    insere(&lista,0,0,&elem,NULL);
    insere(&lista,0,0,&elem1,NULL);
    insere(&lista,0,0,&elem2,NULL);
    insere(&lista,0,0,&elem3,NULL);
    insere(&lista,0,1,&elem4,NULL);
    insere(&lista,0,2,&elem5,NULL);
    insere(&lista2,0,0,&elem6,NULL);
    insere(&lista2,0,0,&elem7,NULL);
    insere(&lista,1,0,NULL,&lista2);
    imprime(&lista);
    //remover_pos(&lista,6);
    //imprime(&lista);
    //insere(&lista,0,0,&elem8,NULL);
    remover_elem(&lista,0,&elem1);
    imprime(&lista);
    return 0;
}