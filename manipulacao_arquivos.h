#ifndef MANIPULACAO_ARQUIVOS_H
#define MANIPULACAO_ARQUIVOS_H
#include "funcoes_basicas.h"
#include <string.h>
#include <ctype.h>

int localizar_veiculo(int codigo)
{
    FILE *arq;
    Veiculo veiculo;
    int i = 0, pos = -1;
    arq = fopen("veiculos.dat", "rb");
    if (arq != NULL)
    {
        while (fread(&veiculo, sizeof(Veiculo), 1, arq) == 1 && pos == -1)
        {
            if (veiculo.codigo == codigo)
            {
                pos = i;
            }
            i++;
        }
        fclose(arq);
    }
    return pos;
}

int localizar_placa(char placa[], int codigo_ignorar)
{
    FILE *arq;
    Veiculo veiculo;
    int i = 0, pos = -1, j;
    arq = fopen("veiculos.dat", "rb");
    if (arq != NULL)
    {
        while (fread(&veiculo, sizeof(Veiculo), 1, arq) == 1 && pos == -1)
        {
            for (j = 0; veiculo.placa[j] != '\0'; j++)
            {
                veiculo.placa[j] = toupper(veiculo.placa[j]);
            }
            if (veiculo.codigo != codigo_ignorar &&
                strcmp(veiculo.placa, placa) == 0)
            {
                pos = i;
            }
            i++;
        }
        fclose(arq);
    }
    return pos;
}

int buscar_veiculo(int posicao, Veiculo *veiculo)
{
    FILE *arq;
    int sucesso = 0;

    arq = fopen("veiculos.dat", "rb");

    if (arq != NULL)
    {
        if (fseek(arq, posicao * sizeof(Veiculo), SEEK_SET) == 0)
        {
            if (fread(veiculo, sizeof(Veiculo), 1, arq) == 1)
            {
                sucesso = 1;
            }
        }

        fclose(arq);
    }

    return sucesso;
}

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

int incluir_veiculo(Veiculo veiculo)
{
    FILE *arq;
    int pos, sucesso = 0;

    pos = localizar_veiculo(veiculo.codigo);
    if (pos != -1)
    {
        printf("Veiculo ja cadastrado!\n");
    }
    else
    {
        arq = fopen("veiculos.dat", "ab");
        if (arq == NULL)
        {
            printf("Nao foi possivel abrir o arquivo para gravacao!\n");
        }
        else
        {
            veiculo.situacao = 1;
            if (fwrite(&veiculo, sizeof(Veiculo), 1, arq) != 1)
            {
                printf("Erro ao gravar o veiculo!\n");
            }
            else
            {
                sucesso = 1;
            }
            fclose(arq);
        }
    }
    return sucesso;
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

int sobreescrever_veiculo(int posicao, Veiculo veiculo)
{
    FILE *arq;
    int sucesso = 0;
    arq = fopen("veiculos.dat", "rb+");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
    }
    else
    {
        if (fseek(arq, posicao * sizeof(Veiculo), SEEK_SET) != 0)
        {
            printf("Erro ao localizar o veiculo no arquivo.\n");
        }
        else if (fwrite(&veiculo, sizeof(Veiculo), 1, arq) != 1)
        {
            printf("Erro ao alterar o veiculo.\n");
        }
        else
        {
            sucesso = 1;
        }
        fclose(arq);
    }
    return sucesso;
}

// exercicio 6
int cadastrar_abastecimento(Abastecimento abastecimento[], Veiculo veiculo[], int total, int total_abastecimento)
{
    // não terminado
    int dia, mes, ano, codigo, pos;
    float quilometragem;

    if (total > 0)
    {
        if (total_abastecimento < TA)
        {
            do
            {
                dia = ler_int("Digite o dia da venda: ");
                if (dia <= 0 || dia > 31)
                {
                    printf("Dia invalido!\n");
                }
            } while (dia <= 0 || dia > 31);
            do
            {
                mes = ler_int("Digite o mes da venda: ");
                if (mes <= 0 || mes > 12)
                {
                    printf("Mes invalido!\n");
                }
                if (mes == 2)
                {
                    if (dia > 28)
                    {
                        while (dia > 28 || dia < 1)
                        {
                            printf("Dia invalido!\n");
                            dia = ler_int("Digite o dia da venda: ");
                        }
                    }
                }
            } while (mes <= 0 || mes > 12);
            do
            {
                ano = ler_int("Digite o ano da venda: ");
                if (ano <= 1999 || ano > 2026)
                {
                    printf("Ano invalido!\n");
                }
            } while (ano <= 1999 || ano > 2026);
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
            abastecimento[total_abastecimento].km_abastecimento = quilometragem;
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

int incluir_abastecimento(Abastecimento abastecimento)
{
    FILE *arq;
    int sucesso = 0;

    arq = fopen("veiculos.dat", "ab");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo para gravacao!\n");
    }
    else
    {
        if (fwrite(&abastecimento, sizeof(Abastecimento), 1, arq) != 1)
        {
            printf("Erro ao gravar o veiculo!\n");
        }
        else
        {
            sucesso = 1;
        }
        fclose(arq);
    }
    return sucesso;
}

// exercicio 8
void encontrar_maior_menor(Abastecimento abastecimento[], int total_abastecimento,
                           float *maior, float *menor, int *contador, int codigo)
{
    int i;
    *maior = 0;
    *menor = -1;
    *contador = 0;

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
                (*contador)++;
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
//
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
            encontrar_maior_menor(abastecimento, total_abastecimento, &maior, &menor, &contador, codigo);
            if (contador < 2)
            {
                printf("Nao e possivel calcular o consumo! Total de abastecimentos incorreto.\n");
            }
            else
            {
                quantidade_litros = calcular_litros(abastecimento, total_abastecimento, codigo);
                diferenca = maior - menor;
                if(quantidade_litros < 0)
                {
                    printf("Nao e possivel calcular o consumo! Quantidade de litros incorreto.\n");
                }
                media = diferenca / quantidade_litros;
            }
        }
    }
    else
    {
        printf("Nenhum abastecimento cadastrado!\n");
    }
    return media;
}

#endif