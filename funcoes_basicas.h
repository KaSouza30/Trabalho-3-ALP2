#include <stdio.h>
#include <string.h>
#define TC 100
#define T 7

typedef struct {
    int codigo;
    char placa[T];
    char modelo[TC];
    int ano;
    float km_atual;
    char situacao;
} Veiculo;

typedef struct {
    int dia;
    int mes;
    int ano;
    int veiculo_codigo;
    float litros;
    float valor;
    float km_abastecimento;
} Abastecimento;

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

char ler_string(char mensagem[], char vetor[])
{
    printf("%s", mensagem);
    fgets(vetor, TC, stdin);
    limpar_enter(vetor);
}