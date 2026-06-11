/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1024
Data        : 07/05/2026
Objetivo    : Ler uma frase e aplicar um processo de criptografia
em três etapas: deslocamento de letras, inversão da string
e alteração dos caracteres da metade final.
Aprendizado : Uso de strings em C com strlen, manipulação de caracteres com ctype.h, estruturas de repetição, troca de
caracteres e formatação de saída com printf.
-------------------------------------------------------------------------- */

#include <string.h>
#include <stdio.h>
#include <ctype.h>

int main(){
    int N, n;
    char aux, M[1001];

    scanf("%d\n", &N);

    for(int i = 0; i < N; ++i){
        scanf("%[^\n]\n", &M);

        n = strlen(M);

        for(int j = 0; j < n; ++j){
            if(isalpha(M[j])){
                M[j] += 3;
            }
        }

        for(int j = 0; j < n/2; ++j){
            aux = M[j];
            M[j] = M[n - 1 - j];
            M[n - 1 - j] = aux;
        }

        for(int j = n/2; j < n; ++j){
            --M[j];
        }

        printf("%s\n", M);
    }

    return 0;
}
