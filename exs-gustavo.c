
#include "menu.h"

// exercicio 7
Abastecimento obter_abastecimento_por_posicao(int posicao)
{
    FILE *arq;
    Abastecimento abastecimento = {0};
    arq = fopen("abastecimento.dat", "rb");

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

void gerar_relatorio_abastecimentos(int total)
{
    Veiculo veiculo;
    Abastecimento abastecimento;
    char opcao = 'n';
    int codigo, i, pos;
    float total_litros = 0, valor_total_gasto = 0, valor_total = 0;

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
        veiculo = pesquisar_veiculo_por_codigo(codigo);

        printf("Relatorio de abastecimentos:\n");
        for (i = 0; i < total; i++)
        {
            abastecimento = obter_abastecimento_por_posicao(i);
            if (veiculo.codigo == abastecimento.veiculo_codigo)
            {
                valor_total = abastecimento.litros * abastecimento.valor;
                total_litros += abastecimento.litros;
                valor_total_gasto += abastecimento.litros * abastecimento.valor;
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