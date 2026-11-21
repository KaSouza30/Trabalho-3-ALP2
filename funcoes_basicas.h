// Dupla: Gustavo Nobre, Kaua Souza Rocha
#ifndef FUNCOES_BASICAS_H
#define FUNCOES_BASICAS_H
#include "manipulacao_arquivos.h"
#include <stdio.h>
#include <string.h>
#define TC 100
#define T 8
#define TV 100
#define TA 1000

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
    printf("Codigo: %d\n", veiculo.codigo);
    printf("Placa: %s\n", veiculo.placa);
    printf("Modelo: %s\n", veiculo.modelo);
    printf("Ano: %d\n", veiculo.ano);
    printf("Km atual: %.2f\n", veiculo.km_atual);
    if (veiculo.situacao == 1)
    {
        printf("Situacao: Ativo\n");
    }
    else
    {
        printf("Situacao: Inativo\n");
    }
}

#endif