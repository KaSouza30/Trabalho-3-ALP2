// Dupla: Gustavo Nobre, Kaua Souza Rocha
#ifndef FUNCOES_BASICAS_H
#define FUNCOES_BASICAS_H
#include "manipulacao_arquivos.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TC 100
#define T 8
#define TV 100
#define TA 1000

typedef struct Veiculo
{
    int codigo, ano;
    char placa[T], modelo[TC], situacao;
    float km_atual;
} Veiculo;

typedef struct Abastecimento
{
    int dia, mes, ano, veiculo_codigo;
    float litros, valor, km_abastecimento;
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

Veiculo ler_dados_veiculo()
{
    Veiculo veiculo;
    printf("Placa: ");
    ler_placa(veiculo.placa, 7, -1);
    ler_string("Modelo: ", veiculo.modelo, TC);
    printf("Ano: ");
    veiculo.ano = ler_ano(2026);
    veiculo.km_atual = ler_float("Km atual: ");
    return veiculo;
}

Abastecimento ler_dados_abastecimento()
{
    Abastecimento abastecimento;
    printf("Dia: ");
    ler_data(&abastecimento.dia, &abastecimento.mes, &abastecimento.ano);
    abastecimento.litros = ler_float("Litros: ");
    abastecimento.valor = ler_float("Valor litro: ");
    return abastecimento;
}


void ler_placa(char placa[], int tamanho, int pos_ignorar)
{
    int valido, i, j = 0, pos_placa;
    do
    {
        valido = 1;
        ler_string("Digite a placa: ", placa, tamanho);
        j = 0;
        while (placa[j] != '\0')
        {
            placa[j] = toupper(placa[j]);
            j++;
        }
        if (strlen(placa) != 7)
        {
            valido = 0;
        }
        else
        {
            for (i = 0; i < tamanho; i++)
            {
                if (i == 0 || i == 1 || i == 2 || i == 4)
                {
                    if (placa[i] < 'A' || placa[i] > 'Z')
                    {
                        valido = 0;
                    }
                }
                else
                {
                    if (placa[i] < '0' || placa[i] > '9')
                    {
                        valido = 0;
                    }
                }
            }
            pos_placa = localizar_placa(placa, pos_ignorar);
            if (pos_placa != -1)
            {
                valido = 0;
                printf("Placa ja cadastrada!\n");
            }
        }

        if (!valido)
        {
            printf("Placa invalida!\n");
        }
    } while (!valido);
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

int ler_dia (int dia_maximo)
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

int ler_mes ()
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

int ler_ano (int ano_atual)
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


#endif