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

// exercicio 10

int contar_abastecimentos(Abastecimento abastecimento[], int total_abastecimento, int codigo)
{
    int i;
    int contador = 0;

    if (total_abastecimento > 0)
    {
        for (i = 0; i < total_abastecimento; i++)
        {
            if (abastecimento[i].veiculo_codigo == codigo)
            {
                contador++;
            }
        }
    }
    else
    {
        printf("Nenhum abastecimento cadastrado!\n");
    }
    return contador;
}

// exercicio 8
void encontrar_maior_menor(Abastecimento abastecimento[], int total_abastecimento,
                           float *maior, float *menor, int codigo)
{
    int i;
    *maior = 0;
    *menor = -1;

    if (total_abastecimento > 0)
    {
        for (i = 0; i < total_abastecimento; i++)
        {
            if (abastecimento[i].veiculo_codigo == codigo)
            {
                if (abastecimento[i].km_abastecimento > *maior)
                {
                    *maior = abastecimento[i].km_abastecimento;
                }
                if (abastecimento[i].km_abastecimento < *menor || *menor == -1)
                {
                    *menor = abastecimento[i].km_abastecimento;
                }
            }
        }
    }
    else
    {
        printf("Nenhum abastecimento cadastrado!\n");
    }
}

float calcular_litros(Abastecimento abastecimento[], int total_abastecimento, int codigo)
{
    int i, contador;
    float quantidade_litros = 0;
    if (total_abastecimento > 0)
    {
        contador = 0;
        for (i = 0; i < total_abastecimento; i++)
        {
            if (abastecimento[i].veiculo_codigo == codigo)
            {
                if (contador == 0)
                {
                    contador++;
                }
                else
                {
                    quantidade_litros += abastecimento[i].litros;
                    contador++;
                }
            }
        }
    }
    else
    {
        printf("Nenhum abastecimento cadastrado!\n");
    }
    return quantidade_litros;
}

float calcular_consumo_medio(Abastecimento abastecimento[], int total_abastecimento)
{
    int codigo, pos, contador;
    float maior, menor, quantidade_litros, diferenca, media = 0;
    if (total_abastecimento > 0)
    {
        codigo = ler_int("Digite o codigo do veiculo: ");
        pos = localizar_veiculo(codigo);
        if (pos != -1)
        {
            contador = contar_abastecimentos(abastecimento, total_abastecimento, codigo);
            if (contador < 2)
            {
                printf("Nao e possivel calcular o consumo! Total de abastecimentos incorreto.\n");
            }
            else
            {
                quantidade_litros = calcular_litros(abastecimento, total_abastecimento, codigo);
                encontrar_maior_menor(abastecimento, total_abastecimento, &maior, &menor, codigo);
                diferenca = maior - menor;
                if (quantidade_litros <= 0)
                {
                    printf("Nao e possivel calcular o consumo! Quantidade de litros incorreto.\n");
                }
                else
                {
                    media = diferenca / quantidade_litros;
                }
            }
        }
    }
    else
    {
        printf("Nenhum abastecimento cadastrado!\n");
    }
    return media;
}

// exercicio 11
void calcular_valor_abastecimentos(Abastecimento abastecimento[], int total_abastecimento, float *valor_total, int codigo)
{
    int i;
    *valor_total = 0;
    if (total_abastecimento > 0)
    {
        for (i = 0; i < total_abastecimento; i++)
        {
            if (abastecimento[i].veiculo_codigo == codigo)
            {
                *valor_total += abastecimento[i].valor;
            }
        }
    }
    else
    {
        printf("Nenhum abastecimento cadastrado!\n");
    }
}

void encontrar_mais_menos_gastou(Abastecimento abastecimento[], int total_abastecimento, int codigo,
                                 float *mais_gastou, float *menos_gastou, int *pos_mais, int *pos_menos)
{
    int i;
    *mais_gastou = 0;
    *menos_gastou = -1;
    *pos_mais = -1;
    *pos_menos = -1;
    float valor_total;
    if (total_abastecimento > 0)
    {
        valor_total = 0;
        calcular_valor_abastecimentos(abastecimento, total_abastecimento, &valor_total, codigo);
        for (i = 0; i < total_abastecimento; i++)
        {
            if (abastecimento[i].veiculo_codigo == codigo)
            {
                if (valor_total > *mais_gastou)
                {
                    *mais_gastou = valor_total;
                    *pos_mais = codigo;
                }
                if (valor_total < *menos_gastou || *menos_gastou == -1)
                {
                    *menos_gastou = valor_total;
                    *pos_menos = codigo;
                }
            }
        }
    }
    else
    {
        printf("Nenhum abastecimento cadastrado!\n");
    }
}

#endif