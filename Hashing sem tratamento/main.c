#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tam_tabela 10

typedef char String[100];

typedef struct HASH {
    String linhas[tam_tabela];
} Hash;


int funchash(String cpf){
    int soma=0,total=strlen(cpf);

    for(int i=0;i<total;i++){
        soma=soma+(i+1)*(int)(cpf[i]);
    }
    soma=soma%tam_tabela;
    return soma;
}

void insere(Hash *tabela,String elem){
    int indice=funchash(elem);
    strcpy(tabela->linhas[indice],elem);
}

int main(){
    Hash tabela;
    insere(&tabela,"000.000.000-00");

    return 0;
}