// Dupla: Gustavo Nobre, Kaua Souza Rocha
/* Kaua: exercicios 1, 2, 6, 8, 10 e 11
Gustavo: exercicios 3, 4, 5, 7, 9 e 12*/

#ifndef MENU_H
#define MENU_H

#include "manipulacao_arquivos.h"
#include "funcoes_basicas.h"
#include "ctype.h"

void ler_placa(char placa[], int tamanho, int codigo_ignorar)
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
            printf("erro 1\n");
            valido = 0;
        }
        else
        {
            for (i = 0; i < 7; i++)
            {
                if (i == 0 || i == 1 || i == 2 || i == 4)
                {
                    if (placa[i] < 'A' || placa[i] > 'Z')
                    {
                        printf("erro 2\n");
                        valido = 0;
                    }
                }
                else
                {
                    if (placa[i] < '0' || placa[i] > '9')
                    {
                        printf("erro 3\n");
                        valido = 0;
                    }
                }
            }
            pos_placa = localizar_placa(placa, codigo_ignorar);
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

Veiculo ler_dados_veiculo()
{
    Veiculo veiculo;
    ler_placa(veiculo.placa, 8, -1);
    getchar();
    ler_string("Modelo: ", veiculo.modelo, TC);
    veiculo.ano = ler_ano(2026);
    veiculo.km_atual = ler_float("Km atual: ");
    return veiculo;
}

// exercicio 1
void cadastrar_veiculo()
{
    Veiculo veiculo;
    int pos_veiculo, codigo;
    do
    {
        codigo = ler_int("Digite o codigo: ");
        pos_veiculo = localizar_veiculo(codigo);

        if (pos_veiculo != -1)
        {
            printf("Codigo ja cadastrado!\n");
        }

    } while (pos_veiculo != -1);

    veiculo = ler_dados_veiculo();
    veiculo.codigo = codigo;
    incluir_veiculo(veiculo);
}

// exercicio 2
void alterar_placa(int pos)
{
    Veiculo veiculo;
    veiculo = obter_veiculo_por_posicao(pos);
    ler_placa(veiculo.placa, 8, veiculo.codigo);
    sobreescrever_veiculo(pos, veiculo);
}

void alterar_modelo(int pos)
{
    Veiculo veiculo;
    veiculo = obter_veiculo_por_posicao(pos);
    ler_string("Digite o modelo: ", veiculo.modelo, TC);
    sobreescrever_veiculo(pos, veiculo);
}

void alterar_ano(int pos)
{
    Veiculo veiculo;
    veiculo = obter_veiculo_por_posicao(pos);
    veiculo.ano = ler_ano(2026);
    sobreescrever_veiculo(pos, veiculo);
}

void alterar_todos(int pos)
{
    Veiculo veiculo;
    veiculo = obter_veiculo_por_posicao(pos);
    ler_placa(veiculo.placa, 8, veiculo.codigo);
    ler_string("Digite o modelo: ", veiculo.modelo, TC);
    veiculo.ano = ler_ano(2026);
    sobreescrever_veiculo(pos, veiculo);
}

// exercicio 3 - pesquisar_veiculo_por_codigo()
void pesquisar_veiculo()
{
    Veiculo veiculo;
    int posicao;

    posicao = obter_posicao_veiculo();
    if (posicao == -1)
    {
        printf("Veiculo nao encontrado.\n");
    }
    else
    {
        veiculo = obter_veiculo_por_posicao(posicao);
        if (veiculo.situacao == 1)
        {
            apresentar_dados_veiculo(veiculo);
        }
        else
        {
            printf("Veiculo esta inativo.\n");
        }
    }
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

// exercicio 6
void cadastrar_abastecimento()
{
    int codigo, pos;
    float quilometragem;
    Abastecimento abastecimento;
    Veiculo veiculo;
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
            veiculo = obter_veiculo_por_posicao(pos);
            if (veiculo.situacao == 0)
            {
                printf("Veiculo inativo!\n");
            }
        }
    } while (pos == -1 || veiculo.situacao == 0);

    do
    {
        quilometragem = ler_float("Digite a quilometragem: ");
        if (quilometragem <= veiculo.km_atual)
        {
            printf("Valor da quilometragem invalido!\n");
        }
    } while (quilometragem <= veiculo.km_atual);
    abastecimento = ler_dados_abastecimento();
    abastecimento.veiculo_codigo = codigo;
    abastecimento.km_abastecimento = quilometragem;

    if (incluir_abastecimento(abastecimento))
    {
        veiculo.km_atual = quilometragem;
        sobreescrever_veiculo(pos, veiculo);
    }
}

// exercicio 8
float calcular_consumo_medio()
{
    int codigo, pos, contador;
    float maior, menor, quantidade_litros, diferenca, media = 0;

    codigo = ler_int("Digite o codigo do veiculo: ");
    pos = localizar_veiculo(codigo);
    if (pos != -1)
    {
        contador = contar_abastecimentos(codigo);
        if (contador < 2)
        {
            printf("Nao e possivel calcular o consumo! Total de abastecimentos incorreto.\n");
        }
        else
        {
            quantidade_litros = calcular_litros(codigo);
            encontrar_maior_menor(&maior, &menor, codigo);
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
    return media;
}

void apresentar_consumo_medio()
{
    float media;
    media = calcular_consumo_medio();
    printf("Media: %.2f\n", media);
}

// exercicio 11
void apresentar_veiculos_mais_menos_gastou()
{
    float mais_gastou = -1;
    float menos_gastou = -1;
    int codigo_mais = -1;
    int codigo_menos = -1;

    encontrar_mais_menos_gastou(&mais_gastou, &menos_gastou, &codigo_mais, &codigo_menos);

    if (codigo_mais != -1)
    {
        printf("\nVeiculo que mais gastou:\n");
        printf("Codigo: %d\n", codigo_mais);
        printf("Valor gasto: R$ %.2f\n", mais_gastou);

        printf("\nVeiculo que menos gastou:\n");
        printf("Codigo: %d\n", codigo_menos);
        printf("Valor gasto: R$ %.2f\n", menos_gastou);
    }
    else
    {
        printf("Nenhum abastecimento cadastrado!\n");
    }
}

void apresentar_gasto_mensal()
{
    int qtd_abastecimentos;
    float valor_total_gasto, total_litros;

    calcular_gasto_mensal(&qtd_abastecimentos, &valor_total_gasto, &total_litros);

    if (qtd_abastecimentos > 0)
    {
        printf("Valor total gasto: R$ %.2f | ", valor_total_gasto);
        printf("Quantidade de abastecimentos: %d | ", qtd_abastecimentos);
        printf("Total de litros: %.2f L\n", total_litros);
    }
    else
    {
        printf("Nao ha abastecimento deste periodo registrado.\n");
    }
}

// exercicio 12 - calcular_ativos_inativos(), calcular_total_gasto_frota(), apresentar_resumo_frota()
void apresentar_resumo_frota()
{
    int qtd_ativos, qtd_inativos, qtd_veiculos_cadastrados, qtd_abastecimentos_registrados;
    float total_gasto;

    qtd_veiculos_cadastrados = calcular_ativos_inativos(&qtd_ativos, &qtd_inativos);
    total_gasto = calcular_total_gasto_frota();
    qtd_abastecimentos_registrados = retornar_quant_abasts();

    printf("Qtd de veiculos cadastrados: %d | ", qtd_veiculos_cadastrados);
    printf("Ativos: %d | ", qtd_ativos);
    printf("Inativos: %d | \n", qtd_inativos);
    printf("Qtd de abastecimentos registrados: %d | ", qtd_abastecimentos_registrados);
    printf("Total gasto pela frota: R$ %.2f\n", total_gasto);
}

int apresentar_menu()
{
    int op;
    do
    {
        printf("1 - Incluir veículos\n");
        printf("2 - Alterar veículos\n");
        printf("3 - Pesquisar um veículo\n");
        printf("4 - Excluir e recuperar veículos\n");
        printf("5 - Apresentar a lista de veículos ativos\n");
        printf("6 - Registrar um abastecimento\n");
        printf("7 - Relatório de abastecimentos de um veículo\n");
        printf("8 - Consumo médio de um veículo\n");
        printf("9 - Gasto mensal com combustível\n");
        printf("10 - Veículos sem abastecimento\n");
        printf("11 - Ranking de gastos\n");
        printf("12 - Resumo da frota\n");
        printf("13 - Finalizar\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();
    } while (op < 1 || op > 13);
    return op;
}

int apresentar_submenu()
{
    int op;
    do
    {
        printf("1 - Alterar placa\n");
        printf("2 - Alterar modelo\n");
        printf("3 - Alterar ano\n");
        printf("4 - Alterar todos\n");
        printf("5 - Finalizar\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();
    } while (op < 1 || op > 5);
    return op;
}

void atualizar_veiculo()
{
    int codigo, pos, opcao;
    codigo = ler_int("Digite o codigo do veiculo: ");
    pos = localizar_veiculo(codigo);
    if (pos != -1)
    {
        do
        {
            opcao = apresentar_submenu();
            switch (opcao)
            {
            case 1:
                alterar_placa(pos);
                break;
            case 2:
                alterar_modelo(pos);
                break;
            case 3:
                alterar_ano(pos);
                break;
            case 4:
                alterar_todos(pos);
                break;
            case 5:
                printf("Alteracao finalizada!\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
            }
        } while (opcao != 5);
    }
    else
    {
        printf("Veiculo nao encontrado!\n");
    }
}

// exercicio 4
int submenu_excluir_recuperar()
{
    int op;
    do
    {
        printf("Opcoes disponiveis:\n");
        printf("1 - Excluir logicamente.\n");
        printf("2 - Excluir veiculos inativos fisicamente.\n");
        printf("3 - Recuperar veiculo inativo.\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();
    } while (op < 1 || op > 3);
    return op;
}

void excluir_recuperar_veiculo()
{
    int codigo, opcao, pos;
    printf("Exclusao ou recuperacao de veiculo: \n\n");
    codigo = ler_int("Digite o codigo do veiculo: ");
    pos = localizar_veiculo(codigo);

    if (pos != -1)
    {
        opcao = submenu_excluir_recuperar();
        switch (opcao)
        {
        case 1:
            excluir_veiculo_logica(pos);
            break;
        case 2:
            excluir_veiculos_fisica();
            break;
        case 3:
            recuperar_veiculo(pos);
            break;
        default:
            printf("Erro ao excluir ou recuperar.");
            break;
        }
    }
    else
    {
        printf("Veiculo inexistente.\n");
    }
}

#endif