// Dupla: Gustavo Nobre, Kaua Souza Rocha
/* Kaua: exercicios 1, 2, 6, 8, 10 e 11
Gustavo: exercicios 3, 4, 5, 7, 9 e 12*/

#ifndef MENU_H
#define MENU_H

#include "manipulacao_arquivos.h"
#include "funcoes_basicas.h"

// exercicio 1
void cadastrar_veiculo()
{
    Veiculo veiculo;
    int codigo, pos_veiculo;
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
    ler_placa(veiculo.placa, 7, veiculo.codigo);
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
    ler_placa(veiculo.placa, 7, veiculo.codigo);
    ler_string("Digite o modelo: ", veiculo.modelo, TC);
    veiculo.ano = ler_ano(2026);
    sobreescrever_veiculo(pos, veiculo);
}

// exercicio 3 - pesquisar_veiculo_por_codigo()
void pesquisar_veiculo()
{
    Veiculo veiculo;
    int posicao, codigo;

    codigo = ler_int("Digite o codigo: ");
    posicao = localizar_veiculo(codigo);
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

// exercicio 7
void apresentar_relatorio_abastecimentos(int total)
{
    Veiculo veiculo;
    Abastecimento abastecimento;
    char opcao = 'n';
    int codigo, i, pos;
    float *total_litros = 0, *valor_total_gasto = 0, *valor_total = 0;

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

    if (pos != -1)
    {
        veiculo = obter_veiculo_por_posicao(pos); // linha 144 no manipulacao_arquivos

        printf("Relatorio de abastecimentos:\n");
        for (i = 0; i < total; i++)
        {
            abastecimento = obter_abastecimento_por_posicao(i); // linha 438 no manipulacao_arquivos
            if (veiculo.codigo == abastecimento.veiculo_codigo)
            {
                calcular_relatorio_abastecimentos(abastecimento, total, &valor_total, &total_litros, &valor_total_gasto);
                printf("%d/%d/%d | ", abastecimento.dia, abastecimento.mes, abastecimento.ano);
                printf("%.2f L | ", abastecimento.litros);
                printf("Valor do litro: %.2f | ", abastecimento.valor);
                printf("Valor total: R$ %.2f | ", valor_total);
                printf("Quilometragem: %.2f KM\n", abastecimento.km_abastecimento);
            }
        }

        printf("\nTotal de litros: %.2f L\n", total_litros);
        printf("Valor total gasto pelo veiculo: R$ %.2f\n", valor_total_gasto);
    }
}

// exercicio 9
void calcular_gasto_mensal(int tl_abastecimentos, int *qtd_abastecimentos,
                           float *valor_total_gasto, float *total_litros)
{
    int mes, ano, i = 0;
    Abastecimento abastecimento;

    mes = ler_mes();
    ano = ler_ano(2026);

    do
    {
        abastecimento = obter_abastecimento_por_posicao(i);
        if (abastecimento.mes == mes && abastecimento.ano == ano)
        {
            *valor_total_gasto += abastecimento.valor * abastecimento.litros;
            *qtd_abastecimentos++;
            *total_litros += abastecimento.litros;
        }
        i++;
    } while (i < tl_abastecimentos);
}

void apresentar_gasto_mensal(int tl)
{
    int qtd_abastecimentos;
    float valor_total_gasto, total_litros;

    calcular_gasto_mensal(tl, &qtd_abastecimentos, &valor_total_gasto, &total_litros);

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

// exercicio 12
void calcular_ativos_inativos(int tl_veiculos, int *qtd_ativos, int *qtd_inativos)
{
    int i;
    Veiculo veiculo;

    for (i = 0; i < tl_veiculos; i++)
    {
        veiculo = obter_veiculo_por_posicao(i);
        if (veiculo.situacao == 0)
        {
            (*qtd_inativos)++;
        }
    }

    *qtd_ativos = tl_veiculos - *qtd_inativos;
}

float calcular_total_gasto_frota(int tl_abastecimentos)
{
    int i;
    float total_gasto = 0;
    Abastecimento abastecimento;

    for (i = 0; i < tl_abastecimentos; i++)
    {
        abastecimento = obter_abastecimento_por_posicao(i);
        total_gasto += abastecimento.valor * abastecimento.litros;
    }

    return total_gasto;
}

void apresentar_resumo_frota(int tl_veiculos, int tl_abastecimentos)
{
    int qtd_ativos, qtd_inativos;
    float total_gasto;

    calcular_ativos_inativos(tl_veiculos, &qtd_ativos, &qtd_inativos);
    total_gasto = calcular_total_gasto_frota(tl_abastecimentos);

    printf("Qtd de veiculos cadastrados: %d | ", tl_veiculos);
    printf("Ativos: %d | ", qtd_ativos);
    printf("Inativos: %d | \n", qtd_inativos);
    printf("Qtd de abastecimentos registrados: %d | ", tl_abastecimentos);
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

#endif