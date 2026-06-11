/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1015
Data        : 14/05/2026
Objetivo    : Ler as coordenadas de dois pontos no plano cartesiano e calcular a distância entre eles utilizando a fórmula da distância euclidiana.
Aprendizado : Uso de variáveis do tipo double, operações matemáticas, utilização da biblioteca math.h com a função sqrt e formatação de saída com printf.
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <math.h>

int main(){
    double x1, y1, x2, y2, distancia;

    scanf("%lf %lf\n%lf %lf", &x1, &y1, &x2, &y2);

    distancia = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));

    printf("%.4lf\n", distancia);

    return 0;
}
