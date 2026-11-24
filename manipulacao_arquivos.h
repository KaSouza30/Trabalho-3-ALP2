// Dupla: Gustavo Nobre, Kaua Souza Rocha
#ifndef MANIPULACAO_ARQUIVOS_H
#define MANIPULACAO_ARQUIVOS_H
#include "funcoes_basicas.h"
#include <string.h>
#include <ctype.h>

void inicializar_arquivo()
{
    FILE *arq_veiculos;
    FILE *arq_abastecimentos;

    arq_veiculos = fopen("veiculos.dat", "rb");
    arq_abastecimentos = fopen("abastecimentos.dat", "rb");

    Veiculo veiculo[5] = {
        {1, "ABC1D23", "Fiat Uno", 2018, 45200, 1},
        {2, "DEF4G56", "Volkswagen Gol", 2020, 31800, 1},
        {3, "HIJ7K89", "Ford Ka", 2017, 78350, 0},
        {4, "LMN0P12", "Renault Kwid", 2022, 12400, 1},
        {5, "QRS3T45", "Chevrolet Onix", 2021, 27900, 1}};

    Abastecimento abastecimento[6] = {
        {5, 9, 2026, 1, 38.5, 5.89, 44100},
        {12, 9, 2026, 2, 42.0, 5.95, 30900},
        {18, 9, 2026, 1, 40.2, 5.89, 45200},
        {20, 9, 2026, 4, 30.0, 6.05, 11850},
        {3, 10, 2026, 2, 44.5, 6.10, 31800},
        {9, 10, 2026, 5, 36.8, 5.99, 27900}};

    if (arq_veiculos == NULL)
    {
        arq_veiculos = fopen("veiculos.dat", "wb");
        if (arq_veiculos != NULL)
        {
            fwrite(veiculo, sizeof(Veiculo), 5, arq_veiculos);
            fclose(arq_veiculos);
        }
    }

    if (arq_abastecimentos == NULL)
    {
        arq_abastecimentos = fopen("abastecimentos.dat", "wb");
        if (arq_abastecimentos != NULL)
        {
            fwrite(abastecimento, sizeof(Abastecimento), 6, arq_abastecimentos);
            fclose(arq_abastecimentos);
        }
    }
    fclose(arq_veiculos);
    fclose(arq_abastecimentos);
}

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

// exercicio 4 - verificar_tem_abastecimentos(), excluir_veiculo_logica(), recuperar_veiculo()
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
        fclose(arq);
    }

    return tem_abastecimento;
}

Veiculo obter_veiculo_por_posicao(int posicao)
{
    FILE *arq;
    Veiculo veiculo = {0};
    arq = fopen("veiculos.dat", "rb");

    if (arq == NULL)
    {
        printf("Falha ao abrir o arquivo de veiculos.\n");
    }
    else
    {
        fseek(arq, posicao * sizeof(Veiculo), SEEK_SET);
        fread(&veiculo, sizeof(Veiculo), 1, arq);
        fclose(arq);
    }

    return veiculo;
}

void excluir_veiculo_logica(int posicao)
{
    Veiculo veiculo;
    veiculo = obter_veiculo_por_posicao(posicao);
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
    veiculo = obter_veiculo_por_posicao(posicao);
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

// exercicio 5 - outra parte esta em manipulacao_arquivo.h
void apresentar_lista_ativos()
{
    FILE *arq;
    Veiculo veiculo;

    arq = fopen("veiculos.dat", "rb");
    printf("Lista de veiculos ativos: \n");

    if (arq == NULL)
    {
        printf("Falha ao abrir o arquivo de veiculos.\n");
    }
    else
    {
        while (fread(&veiculo, sizeof(Veiculo), 1, arq))
        {
            if (veiculo.situacao == 1)
            {
                apresentar_dados_veiculo(veiculo);
            }
        }
        fclose(arq);
    }
}

// exercicio 10
int contar_abastecimentos(int codigo)
{
    FILE *arq;
    int contador = 0;
    Abastecimento abastecimento;
    arq = fopen("abastecimentos.dat", "rb");
    if (arq != NULL)
    {
        while (fread(&abastecimento, sizeof(Abastecimento), 1, arq) == 1)
        {
            if (abastecimento.veiculo_codigo == codigo)
            {
                contador++;
            }
        }
        fclose(arq);
    }
    return contador;
}

void apresentar_veiculos_sem_abastecimento()
{
    FILE *arq;
    Veiculo veiculo;
    int encontrou = 0, contador, ativos = 0;
    arq = fopen("veiculos.dat", "rb");
    if (arq != NULL)
    {
        while (fread(&veiculo, sizeof(Veiculo), 1, arq) == 1)
        {
            if (veiculo.situacao == 1)
            {
                contador = contar_abastecimentos(veiculo.codigo);
                if (contador == 0)
                {
                    printf("Codigo: %d\n", veiculo.codigo);
                    printf("Placa: %s\n", veiculo.placa);
                    printf("Modelo: %s\n", veiculo.modelo);
                    encontrou = 1;
                }
                ativos = 1;
            }
        }
        fclose(arq);
    }

    if (encontrou == 0 && ativos == 1)
    {
        printf("Todos os veiculos ja foram abastecidos!\n");
    }
    else if (ativos == 0)
    {
        printf("Nenhum veiculo ativo no momento!\n");
    }
}

void encontrar_maior_menor(float *maior, float *menor, int codigo)
{
    FILE *arq;
    Abastecimento abastecimento;
    *maior = 0;
    *menor = -1;
    arq = fopen("abastecimentos.dat", "rb");
    if (arq != NULL)
    {
        while (fread(&abastecimento, sizeof(Abastecimento), 1, arq) == 1)
        {
            if (abastecimento.veiculo_codigo == codigo)
            {
                if (abastecimento.km_abastecimento > *maior)
                {
                    *maior = abastecimento.km_abastecimento;
                }
                if (abastecimento.km_abastecimento < *menor || *menor == -1)
                {
                    *menor = abastecimento.km_abastecimento;
                }
            }
        }
        fclose(arq);
    }
}

float calcular_valor_abastecimentos(int codigo)
{
    FILE *arq;
    Abastecimento abastecimento;
    float valor_total = 0;
    arq = fopen("abastecimentos.dat", "rb");
    if (arq != NULL)
    {
        while (fread(&abastecimento, sizeof(Abastecimento), 1, arq) == 1)
        {
            if (abastecimento.veiculo_codigo == codigo)
            {
                valor_total += abastecimento.valor * abastecimento.litros;
            }
        }
        fclose(arq);
    }
    return valor_total;
}

float calcular_litros(int codigo)
{
    FILE *arq;
    int contador;
    float quantidade_litros = 0;
    Abastecimento abastecimento;
    contador = 0;
    arq = fopen("abastecimentos.dat", "rb");
    if (arq != NULL)
    {
        while (fread(&abastecimento, sizeof(Abastecimento), 1, arq) == 1)
        {
            if (abastecimento.veiculo_codigo == codigo)
            {
                if (contador == 0)
                {
                    contador++;
                }
                else
                {
                    quantidade_litros += abastecimento.litros;
                    contador++;
                }
            }
        }
        fclose(arq);
    }
    return quantidade_litros;
}

// exercicio 7
float calcular_cada_abastecimento(int pos)
{
    FILE *arq;
    Abastecimento abastecimento;
    float valor_total = 0;
    arq = fopen("abastecimentos.dat", "rb");
    if (arq != NULL)
    {
        fseek(arq, pos * sizeof(Abastecimento), SEEK_SET);
        fread(&abastecimento, sizeof(Abastecimento), 1, arq);
        valor_total += abastecimento.valor * abastecimento.litros;
        fclose(arq);
    }
    return valor_total;
}

int obter_posicao_veiculo()
{
    char opcao = 'n';
    int codigo, pos;

    do
    {
        codigo = ler_int("Digite o codigo do veiculo: ");
        pos = localizar_veiculo(codigo);
        if (pos == -1)
        {
            printf("Codigo nao encontrado, deseja digitar novamente? (s - sim, n - nao): ");
            scanf(" %c", &opcao);
        }
    } while (opcao == 's');

    return pos;
}

void apresentar_relatorio_abastecimentos()
{
    FILE *arq;
    Veiculo veiculo;
    Abastecimento abastecimento;
    int pos, i = 0;
    float total_litros = 0, valor_total_gasto = 0, valor_total = 0;

    pos = obter_posicao_veiculo();

    arq = fopen("abastecimentos.dat", "rb");

    if (arq == NULL)
    {
        printf("Falha ao abrir o arquivo de abastecimentos.\n");
    }
    else
    {
        if (pos != -1)
        {
            veiculo = obter_veiculo_por_posicao(pos); // linha 144 no manipulacao_arquivos

            printf("Relatorio de abastecimentos:\n");
            while (fread(&abastecimento, sizeof(Abastecimento), 1, arq) == 1)
            {
                if (veiculo.codigo == abastecimento.veiculo_codigo)
                {
                    valor_total = calcular_cada_abastecimento(i);
                    printf("%d/%d/%d | ", abastecimento.dia, abastecimento.mes, abastecimento.ano);
                    printf("%.2f L | ", abastecimento.litros);
                    printf("Valor do litro: %.2f | ", abastecimento.valor);
                    printf("Valor total: R$ %.2f | ", valor_total);
                    printf("Quilometragem: %.2f KM\n", abastecimento.km_abastecimento);
                }
                i++;
            }

            total_litros = calcular_litros(veiculo.codigo);
            valor_total_gasto = calcular_valor_abastecimentos(veiculo.codigo);

            printf("\nTotal de litros: %.2f L\n", total_litros);
            printf("Valor total gasto pelo veiculo: R$ %.2f\n", valor_total_gasto);
        }
        fclose(arq);
    }
}

// exercicio 8

// exercicio 9
void calcular_gasto_mensal(int *qtd_abastecimentos, float *valor_total_gasto, float *total_litros)
{
    FILE *arq;
    int mes, ano;
    Abastecimento abastecimento;
    *qtd_abastecimentos = 0;
    *valor_total_gasto = 0;
    *total_litros = 0;

    mes = ler_mes();
    ano = ler_ano(2026);

    arq = fopen("abastecimentos.dat", "rb");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo de abastecimentos.\n");
    }
    else
    {
        while (fread(&abastecimento, sizeof(Abastecimento), 1, arq) == 1)
        {
            if (abastecimento.mes == mes && abastecimento.ano == ano)
            {
                *valor_total_gasto += abastecimento.valor * abastecimento.litros;
                (*qtd_abastecimentos)++;
                *total_litros += abastecimento.litros;
            }
        }
        fclose(arq);
    }
}

// exercicio 11

void encontrar_mais_menos_gastou(float *mais_gastou, float *menos_gastou, int *codigo_mais, int *codigo_menos)
{
    FILE *arq_veiculo, *arq_abastecimento;
    Abastecimento abastecimento;
    Veiculo veiculo;
    *mais_gastou = 0;
    *menos_gastou = -1;
    *codigo_mais = -1;
    *codigo_menos = -1;
    float valor_total;
    arq_veiculo = fopen("veiculos.dat", "rb");
    arq_abastecimento = fopen("abastecimentos.dat", "rb");
    if (arq_veiculo != NULL && arq_abastecimento != NULL)
    {
        while (fread(&veiculo, sizeof(Veiculo), 1, arq_veiculo) == 1)
        {
            valor_total = calcular_valor_abastecimentos(veiculo.codigo);
            rewind(arq_abastecimento);
            while (fread(&abastecimento, sizeof(Abastecimento), 1, arq_abastecimento) == 1)
            {
                if (abastecimento.veiculo_codigo == veiculo.codigo)
                {
                    if (valor_total > *mais_gastou)
                    {
                        *mais_gastou = valor_total;
                        *codigo_mais = veiculo.codigo;
                    }
                    if (valor_total < *menos_gastou || *menos_gastou == -1)
                    {
                        *menos_gastou = valor_total;
                        *codigo_menos = veiculo.codigo;
                    }
                }
            }
        }
        fclose(arq_veiculo);
        fclose(arq_abastecimento);
    }
}

Abastecimento obter_abastecimento_por_posicao(int posicao)
{
    FILE *arq;
    Abastecimento abastecimento = {0};
    arq = fopen("abastecimentos.dat", "rb");

    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo de abastecimentos.\n");
    }
    else
    {
        fseek(arq, posicao * sizeof(Abastecimento), SEEK_SET);
        fread(&abastecimento, sizeof(Abastecimento), 1, arq);
        fclose(arq);
    }

    return abastecimento;
}

// exercicio 12
int calcular_ativos_inativos(int *qtd_ativos, int *qtd_inativos)
{
    FILE *arq;
    int i = 0;
    Veiculo veiculo;
    *qtd_ativos = 0;
    *qtd_inativos = 0;

    arq = fopen("veiculos.dat", "rb");

    if (arq == NULL)
    {
        printf("Falha ao abrir o arquivo de veiculos.\n");
    }
    while (fread(&veiculo, sizeof(Veiculo), 1, arq) == 1)
    {
        if (veiculo.situacao == 0)
        {
            (*qtd_inativos)++;
        }
        i++;
    }
    fclose(arq);

    *qtd_ativos = i - *qtd_inativos;
    return i; // total de veiculos
}

float calcular_total_gasto_frota()
{
    FILE *arq;
    float total_gasto = 0;
    Abastecimento abastecimento;

    arq = fopen("abastecimentos.dat", "rb");

    if (arq == NULL)
    {
        printf("Falha ao abrir o arquivo de abastecimentos.\n");
    }
    else
    {
        while (fread(&abastecimento, sizeof(Abastecimento), 1, arq) == 1)
        {
            total_gasto += abastecimento.valor * abastecimento.litros;
        }
        fclose(arq);
    }

    return total_gasto;
}

int retornar_quant_abasts()
{
    FILE *arq;
    int quantidade = 0;
    arq = fopen("abastecimentos.dat", "rb");
    if (arq != NULL)
    {
        fseek(arq, 0, SEEK_END);
        quantidade = ftell(arq) / sizeof(Abastecimento);
        fclose(arq);
    }
    return quantidade;
}

#endif