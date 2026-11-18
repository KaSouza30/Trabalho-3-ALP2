#include <stdio.h>
#define T 100
#define TC 7

struct Veiculo
{
    int codigo;
    char placa[TC];
    char modelo[T];
    int ano;
    float km;
    char sit;
};

struct Abastecimento
{
    int dia;
    int mes;
    int ano;
    int veiculo;
    float litros;
    float valor;
    float km_abastecimento;
};

void limpar_enter(char vetor[])
{
    int tl;
    tl = strlen(vetor);
    if (vetor[tl - 1] == '\n')
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