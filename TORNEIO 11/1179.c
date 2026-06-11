/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1179
Data        : 19/05/2026
Objetivo    : Ler valores inteiros, separá-los em vetores de números
              pares e ímpares e imprimir os vetores sempre que atingirem
              a capacidade máxima definida pelo problema.
Aprendizado : Aprendi a manipular vetores, utilizar funções para evitar
              repetição de código, aplicar estruturas condicionais para
              classificação de valores e organizar saídas em C.
-------------------------------------------------------------------------- */
#include <stdlib.h>
#include <stdio.h>

void imprime(char *nome, int *vetor, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%s[%d] = %d\n", nome, i, vetor[i]);
    }
}

int main()
{
    int valor, par[5], impar[5], n_par, n_impar;

    n_par = 0;
    n_impar = 0;
    for (int i = 0; i < 15; ++i)
    {
        scanf("%d", &valor);

        if (abs(valor) % 2)
        {
            impar[n_impar++] = valor;

            if (n_impar == 5)
            {
                imprime("impar", impar, n_impar);
                n_impar = 0;
            }
        }
        else
        {
            par[n_par++] = valor;

            if (n_par == 5)
            {
                imprime("par", par, n_par);
                n_par = 0;
            }
        }
    }

    imprime("impar", impar, n_impar);
    imprime("par", par, n_par);

    return 0;
}
