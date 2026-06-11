/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1441
Data        : 26/05/2026
Objetivo    : Ler números inteiros e determinar o maior valor
               encontrado durante a sequência de Collatz até chegar em 1.
Aprendizado : Aprendi a utilizar estruturas de repetição,
               condicionais e operadores matemáticos.
Pergunta de segunda ordem: Por que o número 1 é tão importante?
-------------------------------------------------------------------------- */

#include <stdio.h>

int main()
{
    int n, resposta;

    while (scanf("%d", &n))
    {
        if (!n)
            break;

        resposta = n;

        while (n > 1)
        {
            if (n % 2)
                n = 3 * n + 1;
            else
                n /= 2;

            resposta = n > resposta ? n : resposta;
        }

        printf("%d\n", resposta);
    }

    return 0;
}
        if (!n)
            break;

        resposta = n;
        while (n > 1)
        {
            if (n % 2)
                n = 3 * n + 1;
            else
                n /= 2;
            resposta = n > resposta ? n : resposta;
        }

        printf("%d\n", resposta);
    }

    return 0;
}
