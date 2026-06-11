/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1078
Data        : 28/04/2026
Objetivo    : Ler um número e mostrar a tabuada do mesmo.
Aprendizado : Uso de estrutura de repetição (for), 
leitura de dados com scanf e formatação de saída com printf para gerar a tabuada de um número.
-------------------------------------------------------------------------- */

#include <stdio.h>

int main(){
    int i,num,res;
    
    scanf("%d",&num);
    
    for (i=1; i<=10; i++)
    {
        printf("%d x %d = %d\n",i,num,num*i);
    }
return 0;
}
