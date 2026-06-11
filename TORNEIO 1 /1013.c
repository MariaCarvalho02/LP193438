/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1013
Data        : 07/04/2026
Objetivo    : Ler três valores inteiros e identificar o maior entre eles.
Aprendizado : Uso de função para calcular o maior valor, utilização da função abs e aplicação de lógica matemática para comparação de números.
-------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>

int maior(int a, int b){
    return (a + b + abs(a - b))/2;
}

int main(){
    int a, b, c, resposta;

    scanf("%d %d %d", &a, &b, &c);
    
    resposta = maior(a, maior(b, c));

    printf("%d eh o maior\n", resposta);

    return 0;
}
