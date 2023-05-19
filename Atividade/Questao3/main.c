#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define True 1
#define False 0

#define MAX_PESO 10
#define MAX_DIMENSOES 100

typedef int bool;

struct timespec sleepTime;

typedef struct {
    int remetente;
    int destinatario;
    bool encomendaPreferencial;
    int peso;
    int dimensoes;
    int tempo_espera;
    int tempo_chegada;
}Encomenda;

typedef struct NOFILA{
    Encomenda elem;
    struct NOFILA *prox;
} Nofila;

typedef struct {
    Nofila *inicio;
    Nofila *final;
} Fila;

typedef struct {
    Encomenda lista_de_espera[50];
    int topo;
} Pilha;

typedef struct NODEQUE {
    Encomenda elem;
    struct NODEQUE *prox;
    struct NODEQUE *ant;
} Nodeque;

typedef struct {
    Nodeque *comeco;
    Nodeque *fim;
} Deque;

void inifila(Fila *fila) {
    fila->inicio = NULL;
    fila->final = NULL;
}

void inipilha(Pilha *pilha) {
    pilha->topo = -1;
}

void inideque(Deque *deque) {
    deque->comeco = NULL;
    deque->fim = NULL;
}

void inserir_fila(Fila *fila, Encomenda nova_encomenda) {
    Nofila *novo = malloc(sizeof(Nofila));
    novo->elem = nova_encomenda;
    novo->prox = NULL;
    if (fila->inicio == NULL) {
        fila->inicio = novo;
        fila->final = novo;
    }
    else {
        fila->final->prox = novo;
        fila->final = novo;
    }
}

void inserir_pilha(Pilha *pilha, Encomenda novaencomenda) {
    pilha->lista_de_espera[pilha->topo + 1] = novaencomenda;
    pilha->topo++;
}

void inserir_deque(Deque *deque, int prioridade, Encomenda novaencomenda) {
    Nodeque *novo = malloc(sizeof(Nodeque));
    novo->elem = novaencomenda;
    novo->prox = NULL;
    novo->ant = NULL;
    if (prioridade) {
        if (deque->comeco == NULL) {
            deque->comeco = novo;
            deque->fim = novo;
        }
        else {
            novo->prox = deque->comeco;
            deque->comeco->ant = novo;
            deque->comeco = novo;
        }
    }
    else {
        if (deque->comeco == NULL) {
            deque->comeco = novo;
            deque->fim = novo;
        }
        else {
            novo->ant = deque->fim;
            deque->fim->prox = novo;
            deque->fim = novo;
        }
    }
}

Encomenda remover_fila(Fila *fila) {
    if (fila->inicio == NULL) {
        printf("Essa fila esta vazia\n");
        Encomenda encomenda_vazia;
        return encomenda_vazia;
    }
    else {
        Nofila *aux = fila->inicio;
        Encomenda encomenda = aux->elem;
        fila->inicio = aux->prox;
        free(aux);
        return encomenda;
    }
}

Encomenda remover_pilha(Pilha *pilha) {
    if (pilha->topo == -1) {
        printf("Essa pilha esta vazia\n");
        Encomenda encomenda_vazia;
        return encomenda_vazia;
    }
    else {
        Encomenda encomenda = pilha->lista_de_espera[pilha->topo];
        pilha->topo--;
        return encomenda;
    }
}

Encomenda criarEncomenda(int tempo_chegada) {
    Encomenda encomenda;
    int rem_dest = rand() % 20 + 1;
    printf("\nRemetente%d\n", rem_dest);
    encomenda.remetente = rem_dest;
    printf("Destinatario%d\n", rem_dest);
    encomenda.destinatario = rem_dest;
    encomenda.encomendaPreferencial = rand() % 2;
    (encomenda.encomendaPreferencial == 1) ? printf("Encomenda preferencial\n") : printf("Encomenda comum\n");
    encomenda.peso = rand() % 13 + 1;
    printf("Peso: %d\n", encomenda.peso);
    encomenda.dimensoes = rand() % 100 + 1;
    printf("Dimensoes: %d\n", encomenda.dimensoes);
    encomenda.tempo_espera = rand()%10+1;
    encomenda.tempo_chegada = tempo_chegada;
    return encomenda;
}


void processamento(Pilha *pilha, Deque *deque) {
    if (pilha->topo != -1) {
        printf("\n===========================================\nProcessamento\n");
        Encomenda encomenda = pilha->lista_de_espera[pilha->topo];
        pilha->topo--;
        if (encomenda.peso > MAX_PESO && encomenda.dimensoes > MAX_DIMENSOES) {
            printf("\nEncomenda fora dos padroes\n");
            printf("\n===========================================\n");
        }
        else {
            if (encomenda.encomendaPreferencial) {
                inserir_deque(deque, 1, encomenda);
                printf("\nEncomenda preferencial adicionada a fila de saida!\n");
                printf("\n===========================================\n");
            }
            else {
                inserir_deque(deque, 0, encomenda);
                printf("\nEncomenda comum adicionada a fila de saida!\n");
                printf("\n===========================================\n");
            }
        }
    }
}

void simulacao(Fila *fila, Pilha *pilha, Deque *deque) {
    sleepTime.tv_sec = 0;
    sleepTime.tv_nsec = 500000000; 
    Encomenda aux;
    for (int i = 0; i < 50; i++) {
        if ((i % 5) == 0) {
            printf("\n-------------------------------------------\nNova encomenda chegou!\n");
            inserir_fila(fila, criarEncomenda(i));
            printf("\n-------------------------------------------\n");
            
        }
        if(fila->inicio!=NULL){
            aux = fila->inicio->elem;
            if ((aux.tempo_chegada + aux.tempo_espera) == i) {
                inserir_pilha(pilha, remover_fila(fila));
            }
        }
        processamento(pilha, deque);
        nanosleep(&sleepTime,NULL);
    }
}

int main() {
    int nafila=0;
    srand(time(NULL));
    Fila fila_entrada;
    Pilha pilha_processamento;
    Deque deque_final;
    inifila(&fila_entrada);
    inipilha(&pilha_processamento);
    inideque(&deque_final);
    simulacao(&fila_entrada, &pilha_processamento, &deque_final);
    Nofila *aux=fila_entrada.inicio;
    while(aux!=NULL){
        aux=aux->prox;
        nafila++;
    }
    printf("\n%d encomendas estao na fila de entrada para serem processadas!\n",nafila);
    getchar();
    return 0;
}