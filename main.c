// Dupla: Gustavo Nobre, Kaua Souza Rocha
#include "menu.h"
#include "manipulacao_arquivos.h"

int main()
{
    inicializar_arquivo();
    int op;
    printf("\n\n");
    op = apresentar_menu();
    do
    {
        switch (op)
        {
        case 1:
            cadastrar_veiculo();
            break;
        case 2:
            atualizar_veiculo();
            break;
        case 3:
            pesquisar_veiculo();
            break;
        case 4:
            excluir_recuperar_veiculo();
            break;
        case 5:
            apresentar_lista_ativos();
            break;
        case 6:
            cadastrar_abastecimento();
            break;
        case 7:
            apresentar_relatorio_abastecimentos();
            break;
        case 8:
            apresentar_consumo_medio();
            break;
        case 9:
            apresentar_gasto_mensal();
            break;
        case 10:
            apresentar_veiculos_sem_abastecimento();
            break;
        case 11:
            apresentar_veiculos_mais_menos_gastou();
            break;
        case 12:
            apresentar_resumo_frota();
            break;
        case 13:
            printf("Programa finalizado!\n");
            break;
        default:
            printf("Operacao invalida!\n");
            break;
        }
        op = apresentar_menu();
    } while (op != 13);
    return 0;
}