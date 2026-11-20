// Dupla: Gustavo Nobre, Kaua Souza Rocha
#ifndef FUNCOES_BASICAS_H
#define FUNCOES_BASICAS_H
#include <stdio.h>
#include <string.h>
#define TC 100
#define T 8
#define TV 100

struct Veiculo
{
    int codigo, ano;
    char placa[T], modelo[TC], situacao;
    float km_atual;
};

struct Abastecimento
{
    int dia, mes, ano, veiculo_codigo;
    float litros, valor, km_abastecimento;
};

void limpar_enter(char vetor[])
{
    int tl;
    tl = strlen(vetor);
    if (tl > 0 && vetor[tl - 1] == '\n')
    {
        vetor[tl - 1] = '\0';
    }
}

int ler_int(char mensagem[])
{
    int valor;
    do
    {
        printf("%s", mensagem);
        scanf("%d", &valor);
        if (valor < 0)
        {
            printf("Valor invalido! Digite novamente.\n");
        }
    } while (valor < 0);
    return valor;
}

float ler_float(char mensagem[])
{
    float valor;
    do
    {
        printf("%s", mensagem);
        scanf("%f", &valor);
        if (valor < 0)
        {
            printf("Valor invalido! Digite novamente.\n");
        }
    } while (valor < 0);
    return valor;
}

void ler_string(char mensagem[], char vetor[], int tamanho)
{
    getchar();
    printf("%s", mensagem);
    fgets(vetor, tamanho, stdin);
    limpar_enter(vetor);
}

#endif