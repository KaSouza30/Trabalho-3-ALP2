// Dupla: Gustavo Nobre, Kaua Souza Rocha
#ifndef FUNCOES_BASICAS_H
#define FUNCOES_BASICAS_H
#include <stdio.h>
#include <string.h>
#define TC 100
#define T 7
#define TV 100
#define TA 1000

typedef struct Veiculo
{
    int codigo;
    char placa[T];
    char modelo[TC];
    int ano;
    float km_atual;
    int situacao;
} Veiculo;

typedef struct Abastecimento
{
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
    getchar();
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
    getchar();
    return valor;
}

void ler_string(char mensagem[], char vetor[], int tamanho)
{
    printf("%s", mensagem);
    fgets(vetor, tamanho, stdin);
    limpar_enter(vetor);
}

int ler_dia(int dia_maximo)
{
    int dia;

    printf("Digite um dia entre 1 e %d: ", dia_maximo);
    dia = ler_int("");
    printf("\n");
    while (dia < 1 || dia > dia_maximo)
    {
        printf("Digite um dia entre 1 e %d!!!\n", dia_maximo);
        dia = ler_int("Digite: ");
    }

    return dia;
}

int ler_mes()
{
    int mes;

    mes = ler_int("Digite o mes: ");
    while (mes < 1 || mes > 12)
    {
        printf("Digite o mes entre 1 e 12!!!\n");
        mes = ler_int("Digite: ");
    }

    return mes;
}

int ler_ano(int ano_atual)
{
    int ano;

    ano = ler_int("Digite o ano: ");
    while (ano < 2008 || ano > ano_atual) // escolhemos 2008 porque é o ano de fundação do campus (a gente acha)
    {
        printf("Digite o ano entre 2008 e %d!!!\n", ano_atual);
        ano = ler_int("Digite: ");
    }

    return ano;
}

void ler_data(int *dia, int *mes, int *ano)
{
    *dia = ler_dia(31);

    *mes = ler_mes();
    if (*mes == 2 && *dia > 28)
    {
        *dia = ler_dia(28);
    }

    *ano = ler_ano(2026);
}

void apresentar_dados_veiculo(Veiculo veiculo)
{
    printf("Codigo: %d | ", veiculo.codigo);
    printf("Placa: %s | ", veiculo.placa);
    printf("Modelo: %s | ", veiculo.modelo);
    printf("Ano: %d | ", veiculo.ano);
    printf("Km atual: %.2f | ", veiculo.km_atual);
    if (veiculo.situacao == 1)
    {
        printf("Situacao: Ativo\n");
    }
    else
    {
        printf("Situacao: Inativo\n");
    }
    printf("\n");
}

#endif