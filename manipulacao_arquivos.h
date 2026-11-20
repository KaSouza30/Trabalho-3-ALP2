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

void ler_placa(char placa[], int tamanho, int pos_ignorar)
{
    int valido, i, j, pos_placa;
    do
    {
        valido = 1;
        ler_string("Digite a placa: ", placa, tamanho);
        for (j = 0; placa[j] != '\0'; j++)
        {
            placa[j] = toupper(placa[j]);
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

#endif