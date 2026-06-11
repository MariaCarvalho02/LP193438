/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1030
Data        : 09/06/2026
Objetivo    : Determinar a posição do sobrevivente em um processo
               de eliminação circular, considerando a quantidade
               de pessoas e o intervalo de eliminação informado.
Aprendizado : Aprendi a utilizar funções recursivas, operações
               com módulo e resolução de problemas envolvendo
               recursão e eliminação circular.
Pergunta de segunda ordem: Por que a última pessoa não é eliminada?
-------------------------------------------------------------------------- */
#include <stdio.h>

int sobrevivente(int n, int k){
    if(n == 1)  return 0;
    return (sobrevivente(n - 1, k) + k) % n;
}

int main(){
    int NC, n, k;

    scanf("%d", &NC);

    for(int i = 1; i <= NC; ++i){
        scanf("%d %d", &n, &k);

        printf("Case %d: %d\n", i, sobrevivente(n, k) + 1);
    }

    return 0;
}
