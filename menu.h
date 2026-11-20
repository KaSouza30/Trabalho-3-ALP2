// Dupla: Gustavo Nobre, Kaua Souza Rocha
/* Kaua: exercicios 1, 2, 6, 8, 10 e 11
Gustavo: exercicios 3, 4, 5, 7, 9 e 12*/

#ifndef MENU_H
#define MENU_H

#include "manipulacao_arquivos.h"

void cadastrar_veiculo ()
{
    Veiculo veiculo;
    int pos, codigo;

    do
    {
        codigo = ler_int("Digite o codigo do veiculo: ");
        pos = localizar_veiculo(codigo);
        if (pos != -1)
        {
            printf("Codigo ja cadastrado! Digite novamente.\n");
        }
    } while (pos != -1);

    veiculo.codigo = codigo;

    do 
    {
        printf("Digite a placa do veiculo: ");
        ler_placa(veiculo.placa, 7, -1);
        pos = localizar_placa(veiculo.placa, -1);
        if (pos != -1)
        {
            printf("Placa ja cadastrada! Digite novamente.\n");
        }
    } while (pos != -1);

}

#endif