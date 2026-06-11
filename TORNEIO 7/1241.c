/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1241
Data        : 05/05/2026
Objetivo    : Ler dois valores em formato de string e verificar
se o segundo valor encaixa no final do primeiro.
Aprendizado : Uso de strings em C com strlen, strcpy e strcmp, além de estruturas de repetição, leitura de dados com scanf
e comparação de partes de uma string.
-------------------------------------------------------------------------- */

#include <string.h>
#include <stdio.h>

int main(){
    int N;
    char A[1001], B[1001];

    scanf("%d\n", &N);

    for(int i = 0; i < N; ++i){
        scanf("%s %s\n", &A, &B);

        if(strlen(B) > strlen(A))   printf("nao encaixa\n");
        else{
            strcpy(A, A + (strlen(A) - strlen(B)));
            if(!strcmp(A, B))       printf("encaixa\n");
            else                    printf("nao encaixa\n");
        }
    }

    return 0;
}
