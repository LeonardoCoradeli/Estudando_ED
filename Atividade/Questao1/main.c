#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef int bool;

typedef struct tipoNo{
    char c;
    struct tipoNo *proximo;
    struct tipoNo *anterior;
}No;

typedef struct tipostring{
    No *inicio;
    No *fim;
}str;

void ini(str *palavra){
    palavra->inicio=NULL;
    palavra->fim=NULL;
}

void inserir_str(str *palavra) {
    char letra = fgetc(stdin);
    while (letra != '\n' && letra != EOF) {
        No *novo = malloc(sizeof(No));
        if (novo == NULL) {
            printf("Memória cheia ou erro ao alocar!");
            return;
        }

        novo->c = letra;
        novo->proximo = NULL;
        novo->anterior = NULL;

        if (palavra->inicio == NULL && palavra->fim == NULL) {
            palavra->inicio = novo;
            palavra->fim = novo;
        } else {
            palavra->fim->proximo = novo;
            novo->anterior = palavra->fim;
            palavra->fim = novo;
        }

        letra = fgetc(stdin);
    }
}

bool comparar_palavra(str *palavra1, str *palavra2){
    No *aux = palavra1->inicio;
    No *aux2 = palavra2->inicio;
    int cont = 0;
    while (aux != NULL && aux2 != NULL) {
        if (aux->c != aux2->c) {
            cont++;
            return FALSE;
        }
        aux = aux->proximo;
        aux2 = aux2->proximo;
    }

    if (aux == NULL && aux2 == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int main(){
    str palavra1,palavra2;
    ini(&palavra1);
    ini(&palavra2);
    printf("Digite uma palavra e pressione enter!\n");
    inserir_str(&palavra1);
    printf("Digite uma palavra e pressione enter!\n");
    inserir_str(&palavra2);
    if(comparar_palavra(&palavra1,&palavra2)){
        printf("Iguais\n");
    }
    else{
        printf("Diferentes\n");
    }
    getchar();
    return 0;
}