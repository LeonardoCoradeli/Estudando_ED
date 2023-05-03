#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./String_dinamica.h"

#define DIV printf("------------------------------------------------\n");

int main()
{
    //-----------------------------------------------------------------------------------
    //1) string vaiza
    //str *String1;//cria um ponteiro q aponta para o primeiro lugar da string
    //ini(&String1);//incia a string
    //-----------------------------------------------------------------------------------
    //2) Limpa uma string din�mica(tive que preencher ela primeiro)
    char v[MAX];//vetor que recebe a info do usu�rio
    str *String2,*aux;
    ini(&String2);
    ini(&aux);
    printf("Digite algo: ");
    fgets(v,MAX,stdin);
    v[strcspn(v, "\n")] = '\0';//fgets pega o \n tambem ent�o isso serve para tirar ele
    for(size_t i=0;i<strlen(v);i++){//roda a string do usu�rio
        inserir_str(&String2,v[i]);//transforma o que foi inserido em uma string dinamica
    }
    copiar(&aux,&String2);
    //verifica��o se o c�digo funciona
    imprimir(&String2);
    limpar_str(&String2);//caso queira contar a string transforme essas 2 em coment�rios
    //imprimir(&String2);
    copiar(&String2,&aux);
    DIV;/*
    //-----------------------------------------------------------------------------------
    //3) Imprimir
    //Tudo o que tinha que ser feito aqui ja foi feito na 2
    //-----------------------------------------------------------------------------------
    //4) Tamanho
    printf("Essa string tem %d caracteres\n",tamanho(&String2));
    DIV;
    //5) Inserir
    //Ja feito na 2(inserir_str)
    //-----------------------------------------------------------------------------------
    //6) Copiar
    str *String3;
    ini(&String3);
    copiar(&String3,&String2);
    imprimir(&String3);
    DIV;
    //-----------------------------------------------------------------------------------
    //7) Concatena
    str *String4;
    ini(&String4);
    concatena(&String4,&String2,&String3);
    imprimir(&String4);
    DIV;
    //-----------------------------------------------------------------------------------
    //8) Remover numero especificado
    int nro,start;
    printf("Digite o numero de caracteres a serem excluidos: ");
    scanf("%d",&nro);
    printf("Digite o numero referente ao start da exclusao(a contagem comeca em 1): ");
    scanf("%d",&start);
    remover(&String4,nro,start);
    imprimir(&String4);
    DIV;
    //-----------------------------------------------------------------------------------
    //9) Inserir no local
    str *String5;
    ini(&String5);
    copiar(&String5,&String2);
    inserir_especificado(&String5);
    imprimir(&String5);
    DIV;
    //-----------------------------------------------------------------------------------
    //10) Comparar tamanho
    str *String6,*String7;
    ini(&String6);
    ini(&String7);
    fflush(stdin);
    char a[MAX];
    printf("Digite a primeira string: ");
    fgets(a,MAX,stdin);
    a[strcspn(a, "\n")] = '\0';
    for(int i=0;i<strlen(a);i++){
        inserir_str(&String6,a[i]);
    }
    char b[MAX];
    fflush(stdin);
    printf("Digite a segunda string: ");
    fgets(b,MAX,stdin);
    b[strcspn(b, "\n")] = '\0';
    for(int i=0;i<strlen(b);i++){
        inserir_str(&String7,b[i]);
    }
    if(compara_tamanho(&String6,&String7)==1){
        printf("Elas tem o mesmo tamanho!\n");
    }
    else if(compara_tamanho(&String6,&String7)==2){
        printf("A a primeira palavra e menor que a segunda!\n");
    }
    else{
        printf("A a primeira palavra e maior que a segunda!\n");
    }
    //-----------------------------------------------------------------------------------
    //11) Comparar strings
    comparar_palavra(&String6,&String7);
    DIV;*/
    //-----------------------------------------------------------------------------------
    //12) Buscar
    printf("Busca feita na primeira string inserida!\n");
    buscar(&String2);
    DIV;
    return 0;
}
