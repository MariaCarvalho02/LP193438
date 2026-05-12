/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1534
Data        : 12/05/2026
Objetivo    : Ler um número inteiro N e gerar uma matriz quadradade ordem N, preenchendo a diagonal principal com 1, a diagonal secundária com 2 e os demais elementos com 3.
Aprendizado : Uso de estruturas de repetição aninhadas, condicionais, manipulação de matrizes logicamente e formatação de saída com printf.
-------------------------------------------------------------------------- */

#include <stdio.h>

int main() {
    int n;

    while (scanf("%d", &n) != EOF) {

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                if (i == j)
                    printf("1");

                else if (i + j == n - 1)
                    printf("2");

                else
                    printf("3");
            }

            printf("\n");
        }
    }

    return 0;
}
