#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 5

typedef struct Aluno{
    int matricula;              
    char nome[80];     
    char email[40];
}tpAluno;

int funchash(int matricula){
    int indice=0;
    indice = matricula%max;
    
    return indice;
}

int main(){
    tpAluno tabelahash[max], *tbhash[max];
    for (int i=0; i<max; i++){
        tabelahash[i].matricula = -1;
    }
    tabelahash[0].matricula = 201;
    strcpy(tabelahash[0].nome, "Carlos");
    strcpy(tabelahash[0].email, "carlos@gmail.com");
    tabelahash[2].matricula = 123;
    strcpy(tabelahash[2].nome, "Ronaldo");
    strcpy(tabelahash[2].email, "ronaldo@gmail.com");
    tabelahash[3].matricula = 985;
    strcpy(tabelahash[3].nome, "Murilo");
    strcpy(tabelahash[3].email, "murilo@gmail.com");
    
    for (int i=0; i<max; i++){
        if (tabelahash[i].matricula != -1){
            tbhash[funchash(tabelahash[i].matricula)] = &tabelahash[i];
        }
    }
    
    for (int i=0;i<max;i++){
        (tbhash[i]!=NULL)?(printf("%d      %s\n",i,tbhash[i]->nome)):printf("%d\n",i);
    }
    return 0;
}
