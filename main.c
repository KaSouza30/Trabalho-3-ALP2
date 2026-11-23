// Dupla: Gustavo Nobre, Kaua Souza Rocha
#include "menu.h"
#include "funcoes_basicas.h"

int main()
{
    int op;
    printf("\n\n");
    op = apresentar_menu();
    while (op != 0)
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
                alterar_aluno();
                break;

            case 5:
                excluir_aluno();
                break;
        }
        op = apresentar_menu();
    }
    return 0;   
}