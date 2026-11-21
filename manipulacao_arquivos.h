// Dupla: Gustavo Nobre, Kaua Souza Rocha
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

int incluir_abastecimento(Abastecimento abastecimento)
{
    FILE *arq;
    int sucesso = 0;

    arq = fopen("abastecimentos.dat", "ab");
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

// exercicio 3 - pesquisar_veiculo_por_codigo()
Veiculo pesquisar_veiculo_por_codigo(int codigo)
{
    FILE *arq;
    Veiculo veiculo = {0};
    int posicao;
    arq = fopen("veiculos.dat", "rb");

    posicao = localizar_veiculo(codigo);
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo de veiculos.\n");
    }
    else
    {
        if (posicao == -1)
        {
            printf("Veiculo nao encontrado!\n");
        }
        else
        {
            fseek(arq, posicao * sizeof(Veiculo), SEEK_SET);
            fread(&veiculo, sizeof(Veiculo), 1, arq);
            fclose(arq);
        }
    }

    return veiculo;
}

/* exercicio 4 - verificar_tem_abastecimentos(), excluir_veiculo_logica(), recuperar_veiculo(),
copiar_registros_veiculos_exceto(), substituir_arquivo(), excluir_veiculos_fisica() */
int verificar_tem_abastecimento(int codigo)
// passa por todos os registros ate achar um que tenha o codigo fornecido, se tiver retorna 1
{
    FILE *arq;
    Abastecimento abastecimento = {0};
    int tem_abastecimento = 0;
    arq = fopen("abastecimentos.dat", "rb");

    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo de abastecimentos.");
    }
    else
    {
        while (fread(&abastecimento, sizeof(Abastecimento), 1, arq) == 1 && tem_abastecimento == 0)
        {
            if (abastecimento.veiculo_codigo == codigo)
            {
                tem_abastecimento = 1;
            }
        }
    }

    return tem_abastecimento;
}

void excluir_veiculo_logica(int posicao)
{
    Veiculo veiculo;
    veiculo = pesquisar_veiculo_por_codigo(posicao);
    int sobreescreveu = 0, tem_abastecimento;
    if (veiculo.situacao == 1)
    {
        tem_abastecimento = verificar_tem_abastecimento(veiculo.codigo);
        if (tem_abastecimento == 0)
        {
            veiculo.situacao = 0;
            sobreescreveu = sobreescrever_veiculo(posicao, veiculo);
            if (sobreescreveu == 1)
            {
                printf("Veiculo excluido logicamente.\n");
            }
            else
            {
                printf("Falha ao excluir o veiculo.\n");
            }
        }
        else
        {
            printf("Veiculos com abastecimentos registrados nao podem ser excluidos.\n");
        }
    }
    else
    {
        printf("Veiculo ja excluido logicamente.\n");
    }
}

void recuperar_veiculo(int posicao)
{
    Veiculo veiculo;
    veiculo = pesquisar_veiculo_por_codigo(posicao);
    int sobreescreveu = 0;
    if (veiculo.situacao == 0)
    {
        veiculo.situacao = 1;
        sobreescreveu = sobreescrever_veiculo(posicao, veiculo);
        if (sobreescreveu == 1)
        {
            printf("Veiculo recuperado.\n");
        }
        else
        {
            printf("Falha ao recuperar o veiculo.\n");
        }
    }
    else
    {
        printf("Veiculo ja ativo.\n");
    }
}

int copiar_registros_veiculos_exceto()
// copia todos os registros de veiculo para o arquivo temporario, exceto os com situacao = 0
{
    FILE *arq_orig, *arq_dest;
    Veiculo veiculo;
    int resultado = 1;
    arq_orig = fopen("veiculos.dat", "rb");
    if (arq_orig == NULL)
    {
        resultado = 0;
    }
    else
    {
        arq_dest = fopen("veiculos_temporario.dat", "wb");
        if (arq_dest == NULL)
        {
            resultado = 0;
        }
        else
        {
            while (fread(&veiculo, sizeof(Veiculo), 1, arq_orig) == 1)
            {
                if (veiculo.situacao == 1)
                {
                    fwrite(&veiculo, sizeof(Veiculo), 1, arq_dest);
                }
            }
            fclose(arq_dest);
        }
        fclose(arq_orig);
    }

    return resultado;
}

int substituir_arquivo()
{
    int resultado = 1;
    if (remove("veiculos.dat") != 0)
    {
        resultado = 0;
    }
    else
    {
        if (rename("veiculos_temporario.dat", "veiculos.dat") != 0)
        {
            resultado = 0;
        }
    }
    return resultado;
}

void excluir_veiculos_fisica()
{
    int resultado;
    resultado = copiar_registros_veiculos_exceto();
    if (resultado == 1)
    {
        resultado = substituir_arquivo();
        if (resultado == 1)
        {
            printf("Veiculos excluidos fisicamente.\n");
        }
        else
        {
            printf("Erro ao substituir o arquivo original.\n");
        }
    }
    else
    {
        printf("Erro ao criar o arquivo temporario.\n");
        remove("veiculos_temporario.dat");
    }
}

// exercicio 5 - outra parte esta em menu.h, linha 67 
Veiculo retornar_veiculo_por_posicao(int posicao)
{
    FILE *arq;
    Veiculo veiculo = {0};
    arq = fopen("veiculos.dat", "rb");

    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo de veiculos.\n");
    }
    else
    {
        fseek(arq, posicao * sizeof(Veiculo), SEEK_SET);
        fread(&veiculo, sizeof(Veiculo), 1, arq);
        fclose(arq);
    }

    return veiculo;
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
                if (quantidade_litros < 0)
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