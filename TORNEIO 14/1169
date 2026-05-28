/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1169
Data        : 28/05/2026
Objetivo    : Calcular a quantidade de grãos de trigo em um tabuleiro
               de xadrez utilizando progressão geométrica e converter
               o resultado para quilogramas.
Aprendizado : Aprendi a utilizar funções recursivas, potência,
               progressão geométrica e variáveis do tipo unsigned long long.
Pergunta de segunda ordem: Por que um tabuleiro de xadrez consegue
               gerar números tão grandes?
-------------------------------------------------------------------------- */
#include <stdio.h>

unsigned long long int potencia(int base, int expoente)
{
    if (expoente == 1)
        return base;
    if (expoente % 2)
        return base * potencia(base, expoente - 1);

    unsigned long long int p = potencia(base, expoente / 2);
    return p * p;
}

unsigned long long int somaPG(int a0, int q, int n)
{
    return a0 * (potencia(q, n) - 1) / (q - 1);
}

int main()
{
    int N, X;

    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &X);

        printf("%llu kg\n", somaPG(1, 2, X) / 12000);
    }

    return 0;
}
