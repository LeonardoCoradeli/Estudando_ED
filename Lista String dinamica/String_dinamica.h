#ifndef STRING_DINAMICA_H_INCLUDED
#define STRING_DINAMICA_H_INCLUDED

#define MAX 50

typedef struct tipostring{
    char c;
    struct tipostring *proximo;
}str;

extern const str * const NULO;

void ini(str **palavra);

void inserir_str(str **palavra,char letra);

void limpar_str(str **palavra);

void imprimir(str **palavra);

int tamanho(str **palavra);

void copiar(str **palavra1,str **palavra2);

void concatena(str **palavra1,str **palavra2,str **palavra3);

void remover(str **palavra,int nro,int start);

void inserir_especificado(str **palavra);

int compara_tamanho(str **palavra1,str **palavra2);

void comparar_palavra(str **palavra1,str **palavra2);

void buscar(str **palavra);

#endif // STRING_DINAMICA_H_INCLUDED
