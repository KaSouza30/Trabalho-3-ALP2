#include <stdio.h>
#include <string.h>

void limpar_enter(char vetor[])
{
    int tl;
    tl = strlen(vetor);
    if (vetor[tl - 1] == '\n')
    {
        vetor[tl - 1] = '\0';
    }
}

int ler_int(char mensagem[])
{
    int valor;
    do
    {
        printf("%s", mensagem);
        scanf("%d", &valor);
        if (valor < 0)
        {
            printf("Valor invalido! Digite novamente.\n");
        }
    } while (valor < 0);
    return valor;
}

float ler_float(char mensagem[])
{
    float valor;
    do
    {
        printf("%s", mensagem);
        scanf("%f", &valor);
        if (valor < 0)
        {
            printf("Valor invalido! Digite novamente.\n");
        }
    } while (valor < 0);
    return valor;
}

