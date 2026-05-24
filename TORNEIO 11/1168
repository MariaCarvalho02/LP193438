/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1168
Data        : 19/05/2026
Objetivo    : Ler valores numéricos e calcular a quantidade total de LEDs
              necessária para exibir cada número informado, considerando
              a quantidade de LEDs utilizada por cada dígito.
Aprendizado : Aprendi a trabalhar com vetores para armazenar valores de
              referência, percorrer strings com laços de repetição e
              realizar cálculos utilizando caracteres em C.
-------------------------------------------------------------------------- */
#include <string.h>
#include <stdio.h>

int main(){
    char V[101];
    int N, resposta;
    int leds[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

    scanf("%d\n", &N);

    for(int i = 0; i < N; ++i){
        scanf("%s", &V);

        resposta = 0;
        for(int j = 0; j < strlen(V); ++j){
            resposta += leds[V[j] - '0'];
        }

        printf("%d leds\n", resposta);
    }

    return 0;
}
