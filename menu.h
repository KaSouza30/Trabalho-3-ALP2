// Dupla: Gustavo Nobre, Kaua Souza Rocha
/* Kaua: exercicios 1, 2, 6, 8, 10 e 11
Gustavo: exercicios 3, 4, 5, 7, 9 e 12*/

#ifndef MENU_H
#define MENU_H

#include "manipulacao_arquivos.h"
#include "funcoes_basicas.h"

// exercicio 1
int cadastrar_veiculo(Veiculo veiculo, int total)
{
    int codigo, pos_veiculo;
    if (total < TV)
    {
        do
        {
            codigo = ler_int("Digite o codigo: ");
            pos_veiculo = localizar_veiculo(codigo);

            if (pos_veiculo != -1)
            {
                printf("Codigo ja cadastrado!\n");
            }

        } while (pos_veiculo != -1);

        ler_placa(veiculo.placa, 7, -1);
        veiculo.codigo = codigo;
        veiculo.ano = ler_int("Digite o ano: ");
        veiculo.km_atual = ler_float("Digite a km atual: ");
        ler_string("Digite o modelo: ", veiculo.modelo, TC);

        if (incluir_veiculo(veiculo))
        {
            total++;
        }
    }
    return total;
}

// exercicio 2
void alterar_placa(Veiculo veiculo[], int pos)
{
    ler_placa(veiculo[pos].placa, 7, veiculo[pos].codigo);
}

void alterar_modelo(Veiculo veiculo[], int pos)
{
    ler_string("Digite o modelo: ", veiculo[pos].modelo, TC);
}

void alterar_ano(Veiculo veiculo[], int pos)
{
    veiculo[pos].ano = ler_int("Digite o ano: ");
}

void alterar_todos(Veiculo veiculo[], int pos)
{
    ler_placa(veiculo[pos].placa, 7, veiculo[pos].codigo);
    ler_string("Digite o modelo: ", veiculo[pos].modelo, TC);
    veiculo[pos].ano = ler_int("Digite o ano: ");
}

// exercicio 6
void validar_data(int *dia, int *mes, int *ano)
{
    do
    {
        *dia = ler_int("Digite o dia da venda: ");
        if (*dia <= 0 || *dia > 31)
        {
            printf("Dia invalido!\n");
        }
    } while (*dia <= 0 || *dia > 31);
    do
    {
        *mes = ler_int("Digite o mes da venda: ");
        if (*mes <= 0 || *mes > 12)
        {
            printf("Mes invalido!\n");
        }
        if (*mes == 2)
        {
            if (*dia > 28)
            {
                while (*dia > 28 || *dia < 1)
                {
                    printf("Dia invalido!\n");
                    *dia = ler_int("Digite o dia da venda: ");
                }
            }
        }
    } while (*mes <= 0 || *mes > 12);
    do
    {
        *ano = ler_int("Digite o ano da venda: ");
        if (*ano <= 1999 || *ano > 2026)
        {
            printf("Ano invalido!\n");
        }
    } while (*ano <= 1999 || *ano > 2026);
}

int cadastrar_abastecimento(Abastecimento abastecimento[], Veiculo veiculo[], int total, int total_abastecimento)
{
    int dia, mes, ano, codigo, pos;
    float quilometragem;

    if (total > 0)
    {
        if (total_abastecimento < TA)
        {
            validar_data(&dia, &mes, &ano);
            do
            {
                codigo = ler_int("Digite um codigo: ");
                pos = localizar_veiculo(codigo);

                if (pos == -1)
                {
                    printf("Codigo nao encontrado!\n");
                }
                else
                {
                    if (veiculo[pos].situacao == 0)
                    {
                        printf("Veiculo inativo!\n");
                    }
                }
            } while (pos == -1 || veiculo[pos].situacao == 0);

            do
            {
                quilometragem = ler_float("Digite a quilometragem: ");
                if (quilometragem <= veiculo[pos].km_atual)
                {
                    printf("Valor da quilometragem invalido!\n");
                }
            } while (quilometragem <= veiculo[pos].km_atual);
            abastecimento[total_abastecimento].ano = ano;
            abastecimento[total_abastecimento].dia = dia;
            abastecimento[total_abastecimento].mes = mes;
            abastecimento[total_abastecimento].veiculo_codigo = codigo;
            abastecimento[total_abastecimento].litros = ler_float("Digite a quantidade de litros: ");
            abastecimento[total_abastecimento].valor = ler_float("Digite o valor do litro: ");

            if (incluir_abastecimento(abastecimento[total_abastecimento]))
            {
                veiculo[pos].km_atual = quilometragem;
                sobreescrever_veiculo(pos, veiculo[pos]);
                total_abastecimento++;
            }
        }
        else
        {
            printf("Maximo de abastecimentos feitos!\n");
        }
    }
    else
    {
        printf("Nenhum veiculo cadastrado!\n");
    }
    return total_abastecimento;
}

#endif