/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1028
Data        : 26/05/2026
Objetivo    : Ler pares de números inteiros e calcular o
               Máximo Divisor Comum (MDC) utilizando o algoritmo
               de Euclides.
Aprendizado : Aprendi a utilizar funções recursivas e operações
               matemáticas em linguagem C.
Pergunta de segunda ordem: Por que não existe divisão por 0?
-------------------------------------------------------------------------- */

#include <stdio.h>

int MDC(int a, int b)
{
    return (b == 0) ? a : MDC(b, a % b);
}

int main()
{
    int N, F1, F2;

    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        scanf("%d %d", &F1, &F2);
        printf("%d\n", MDC(F1, F2));
    }

    return 0;
}
