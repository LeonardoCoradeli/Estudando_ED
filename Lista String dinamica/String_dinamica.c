#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "String_dinamica.h"

#define MAX 50

const str * const NULO = NULL;//Define uma constante para nulo, usei isso na função de concatenar


void ini(str **palavra){//uma lista dinamica tem um ponteiro primerio que aponta para o primeiro elemento, como a lista ta vazia aponta NULL
    *palavra=NULL;
}

void inserir_str(str **palavra,char letra) {
    str *novo = malloc(sizeof(str));//novo elemento da string(nova letra) alocado dinamicamente
    if (novo == NULL) { printf("Memória cheia ou erro ao alocar!"); }
    else {
        novo->c = letra;
        novo->proximo = NULL;
        if (*palavra == NULL) {//caso a string esteja vazia, a nova letra é inserida no primeiro lugar da lista
            *palavra = novo;//o * é importante pois como palavra é ponteiro de ponteiro é necessario mexer com o ponteiro para a qual ele aponta e não com palavra necessariamente
        } else {//caso não esteja vazia
            str *aux = *palavra;//cria um auxiliar
            while (aux->proximo != NULL) {//roda a string até o final
                aux = aux->proximo;
            }
            aux->proximo = novo;//faz o ultimo caracter apontar para o novo em vez de para null
        }
    }
}

void limpar_str(str **palavra) {//recebe a palavra
    str *aux = (*palavra)->proximo;//pega a proxima letra
    while (aux != NULL) {//roda a string
        str *aux2 = aux->proximo;//pega a proxima da proxima letra(ou seja se aux tem a 2 letra, aux2 tem a 3...)
        free(aux);//libera a letra(seguindo o exemplo de cima seria liberar a 2 letra)
        aux = aux2;//faz o auxiliar receber a proxima letra
    }
    *palavra = NULL;//incializa a string como uma string vazia
}

void imprimir(str **palavra){//recebe uma palavra
    str *aux= *palavra;//define um auxiliar
    if (aux==NULL){//verfica se a string está vazia
        printf("Essa e uma string vaiza!!!\n");
    }
    while(aux!=NULL){//roda a string até o ultimo caractere
        printf("%c",aux->c);//imprime o caractere
        aux=aux->proximo;//auxiliar recebe o proximo
    }
    printf("\n");
}
int tamanho(str **palavra){//percorre a string
    str *aux = *palavra;
    int cont = 0;
    while(aux!=NULL){//incrementa o contador conforme roda a string
        cont++;
        aux=aux->proximo;
    }
    return cont;
}

void copiar(str **palavra1,str **palavra2){//recebe a primeira e a segunda lista, a primeira lista é para onde será copiado
    str *aux = *palavra2;//cria um auxiliar para receber a segunda palavra
    while(aux!=NULL){
        inserir_str(palavra1,aux->c);//roda a palavra inserido os caracteres na primeira
        aux=aux->proximo;
    }
}

void concatena(str **palavra1,str **palavra2,str **palavra3){//salva o conteudo da segunda e terceira string(caso essa não seja nula) na primeira
    str *aux = *palavra2;
    str *aux2 = *palavra3;
    while(aux!=NULL){//percorre a string inserindo  na outra
        inserir_str(palavra1,aux->c);
        aux=aux->proximo;
    }
    if(palavra3!=NULL){//se ouver uma 3 string insere também
        while(aux2!=NULL){//percorre a string inserindo  na outra
            inserir_str(palavra1,aux2->c);
            aux2=aux2->proximo;
        }
    }
}

void remover(str **palavra,int nro,int start){
    str *aux = *palavra;
    str *aux2;
    str *aux3;
    if(tamanho(palavra)<start){
        printf("Esse start é maior que o numero de caracteres da string");
    }
    else{
        if((tamanho(palavra)-start)<=nro){
            printf("Numero de caracteres a ser excluido excede o numero restante na string, diminua o start ou o numero a ser removido!\n");
        }
        else{
            for(int i=0;i<start-1;i++){//roda a string até o ponto onde começa a ser removido
                aux=aux->proximo;
            }
            aux3=aux;
            for(int i=0;i<=nro;i++){//remove percorre a string removendo o numero especificado
                aux2 = aux->proximo;
                free(aux);
                aux=aux2;
            }
            aux3->proximo=aux;//liga a parte da string antes da que foi excluda com a parte após ser excluida
        }
    }
}

void inserir_especificado(str **palavra){
    int start;
    char v[MAX];
    str *sub;
    ini(&sub);
    fflush(stdin);
    printf("Digite algo: ");
    fgets(v,MAX,stdin);
    v[strcspn(v, "\n")] = '\0';
    for(int i=0;i<strlen(v);i++){
        inserir_str(&sub,v[i]);
    }//tudo acima é para criar uma substrig que vai ser incluida
    printf("A partir de qual posicao: ");
    fflush(stdin);
    scanf("%d",&start);
    if(tamanho(palavra)<start){
        printf("Valor insirido maior do que  string");
    }
    else if(tamanho(palavra)==start){
        concatena(palavra,&sub,&NULO);//se for pedido para inserir ao final da string simplemente concatena
    }
    else{
        str *aux=*palavra;
        for(int i=0;i<start-1;i++){//roda a string até o ponto onde sera inserido
            aux=aux->proximo;
        }
        str *proximo=aux->proximo;//marca qual é o proximo caracter da string
        aux->proximo=sub;//o ponto escolhido passa a apontar para a substring
        str *aux2=sub;
        while(aux2->proximo!=NULL){//roda a substring
            aux2=aux2->proximo;
        }
        aux2->proximo=proximo;//faz o ultimo caractere da substring apontar novamente para a string principal
    }
}

int compara_tamanho(str **palavra1,str **palavra2){
    if(tamanho(palavra1)==tamanho(palavra2)){
        return 1;
    }
    else if(tamanho(palavra1)<tamanho(palavra2)){
        return 2;
    }
    else{
        return 0;
    }
}

void comparar_palavra(str **palavra1, str **palavra2) {
    str *aux = *palavra1;
    str *aux2 = *palavra2;
    int cont = 0;

    while (aux != NULL && aux2 != NULL) {
        if (aux->c != aux2->c) {
            printf("Nao sao iguais!\n");
            cont++;
            return;
        }
        aux = aux->proximo;
        aux2 = aux2->proximo;
    }

    if (aux == NULL && aux2 == NULL) {
        printf("Sao iguais!\n");
    } else {
        printf("Nao sao iguais!\n");
    }
}

void buscar(str **palavra){
    char v[MAX];
    int cont=-1;
    //str *sub;
    //ini(&sub);
    fflush(stdin);
    printf("Digite o que voce quer buscar: ");
    fgets(v,MAX,stdin);
    v[strcspn(v, "\n")] = '\0';
    //for(int i=0;i<strlen(v);i++){
        //inserir_str(&sub,v[i]);}
    str *aux = *palavra;
    while(aux!=NULL && aux->c!=v[0]){
        aux=aux->proximo;
        printf("%d\n",cont);
        cont++;
    }
    if(aux==NULL){
        printf("Substring %s nao encontrada!\n",v);
    }
    else{
        int i=0;
        while(aux->c==v[i]){
            aux=aux->proximo;
            i++;
        }
        if(i!=strlen(v)){
            printf("Substring %s nao encontrada!\n",v);
        }
        else{
            if(cont==-1){
            printf("Substring encontrada na 0 posicao\n");
            }
            else if(cont+1==strlen(v)){
                printf("Substring encontrada na %d posicao\n",strlen(v));
                }
            else{
                printf("Substring encontrada na %d posicao\n",cont);
                }
        }
    }
}
