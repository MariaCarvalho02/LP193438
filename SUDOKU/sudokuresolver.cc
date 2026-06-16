/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C++
Problema    : Projeto Sudoku - Resolvedor Iterativo
Data        : 14/06/2026
Objetivo    : Resolver um Sudoku utilizando uma abordagem iterativa
              combinando técnicas de candidato único e eliminação.
Aprendizado : Matrizes, laços de repetição, busca de candidatos válidos,
              técnicas de resolução iterativa e otimização.
-------------------------------------------------------------------------- */

#include <iostream>
#include <cstring>

using namespace std;

int sudoku[9][9];
int sudokuOriginal[9][9];

bool valorValido(int linha, int coluna, int valor) {
    for (int i = 0; i < 9; i++) {
        if (sudoku[linha][i] == valor)
            return false;
    }

    for (int i = 0; i < 9; i++) {
        if (sudoku[i][coluna] == valor)
            return false;
    }

    int inicioLinha = (linha / 3) * 3;
    int inicioColuna = (coluna / 3) * 3;

    for (int i = inicioLinha; i < inicioLinha + 3; i++) {
        for (int j = inicioColuna; j < inicioColuna + 3; j++) {
            if (sudoku[i][j] == valor)
                return false;
        }
    }

    return true;
}

void imprimirSudoku() {
    cout << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << sudoku[i][j] << " ";
            if (j == 2 || j == 5) cout << "| ";
        }
        cout << endl;
        if (i == 2 || i == 5) {
            cout << "------+-------+------" << endl;
        }
    }
    cout << endl;
}

bool completo() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == 0)
                return false;
        }
    }
    return true;
}

int contarCelulasVazias() {
    int count = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == 0)
                count++;
        }
    }
    return count;
}

bool encontrarUnicoCandidato(int& linha, int& coluna, int& valor) {
    for (int l = 0; l < 9; l++) {
        for (int c = 0; c < 9; c++) {
            if (sudoku[l][c] != 0) continue;

            int candidato = 0;
            int quantidade = 0;

            for (int v = 1; v <= 9; v++) {
                if (valorValido(l, c, v)) {
                    candidato = v;
                    quantidade++;
                    if (quantidade > 1) break;
                }
            }

            if (quantidade == 1) {
                linha = l;
                coluna = c;
                valor = candidato;
                return true;
            }
        }
    }
    return false;
}

bool encontrarUnicoNaLinha(int& linha, int& coluna, int& valor) {
    for (int l = 0; l < 9; l++) {
        for (int v = 1; v <= 9; v++) {
            int posicao = -1;
            int count = 0;

            for (int c = 0; c < 9; c++) {
                if (sudoku[l][c] == 0 && valorValido(l, c, v)) {
                    posicao = c;
                    count++;
                    if (count > 1) break;
                }
            }

            if (count == 1 && posicao != -1) {
                linha = l;
                coluna = posicao;
                valor = v;
                return true;
            }
        }
    }
    return false;
}

bool encontrarUnicoNaColuna(int& linha, int& coluna, int& valor) {
    for (int c = 0; c < 9; c++) {
        for (int v = 1; v <= 9; v++) {
            int posicao = -1;
            int count = 0;

            for (int l = 0; l < 9; l++) {
                if (sudoku[l][c] == 0 && valorValido(l, c, v)) {
                    posicao = l;
                    count++;
                    if (count > 1) break;
                }
            }

            if (count == 1 && posicao != -1) {
                linha = posicao;
                coluna = c;
                valor = v;
                return true;
            }
        }
    }
    return false;
}

bool encontrarUnicoNoBloco(int& linha, int& coluna, int& valor) {
    for (int blocoLinha = 0; blocoLinha < 3; blocoLinha++) {
        for (int blocoColuna = 0; blocoColuna < 3; blocoColuna++) {
            for (int v = 1; v <= 9; v++) {
                int posLinha = -1, posColuna = -1;
                int count = 0;

                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        int l = blocoLinha * 3 + i;
                        int c = blocoColuna * 3 + j;
                        if (sudoku[l][c] == 0 && valorValido(l, c, v)) {
                            posLinha = l;
                            posColuna = c;
                            count++;
                            if (count > 1) break;
                        }
                    }
                    if (count > 1) break;
                }

                if (count == 1 && posLinha != -1) {
                    linha = posLinha;
                    coluna = posColuna;
                    valor = v;
                    return true;
                }
            }
        }
    }
    return false;
}

bool eliminarCandidatos() {
    bool mudou = false;
    int candidatos[9][9][10] = {0};
    
    for (int l = 0; l < 9; l++) {
        for (int c = 0; c < 9; c++) {
            if (sudoku[l][c] != 0) continue;
            
            int count = 0;
            for (int v = 1; v <= 9; v++) {
                if (valorValido(l, c, v)) {
                    candidatos[l][c][v] = 1;
                    count++;
                }
            }
            
            if (count == 1) {
                for (int v = 1; v <= 9; v++) {
                    if (candidatos[l][c][v]) {
                        sudoku[l][c] = v;
                        mudou = true;
                        break;
                    }
                }
            }
        }
    }
    
    return mudou;
}

bool resolverIterativo() {
    bool progresso;
    int iteracoes = 0;
    int celulasVaziasAnterior;
    
    do {
        progresso = false;
        iteracoes++;
        celulasVaziasAnterior = contarCelulasVazias();
        
        int linha, coluna, valor;
        
        if (encontrarUnicoCandidato(linha, coluna, valor)) {
            sudoku[linha][coluna] = valor;
            progresso = true;
            continue;
        }
        
        if (encontrarUnicoNaLinha(linha, coluna, valor)) {
            sudoku[linha][coluna] = valor;
            progresso = true;
            continue;
        }
        
        if (encontrarUnicoNaColuna(linha, coluna, valor)) {
            sudoku[linha][coluna] = valor;
            progresso = true;
            continue;
        }
        
        if (encontrarUnicoNoBloco(linha, coluna, valor)) {
            sudoku[linha][coluna] = valor;
            progresso = true;
            continue;
        }
        
        if (eliminarCandidatos()) {
            progresso = true;
        }
        
        if (progresso) {
            cout << "Iteracao " << iteracoes << ": " 
                 << celulasVaziasAnterior - contarCelulasVazias() 
                 << " celulas preenchidas." << endl;
        }
        
    } while (progresso && !completo());
    
    cout << "Total de iteracoes: " << iteracoes << endl;
    return completo();
}

int main() {
    cout << "=== RESOLVEDOR ITERATIVO DE SUDOKU ===" << endl;
    cout << "Digite o tabuleiro (0 para celulas vazias):" << endl;
    cout << endl;
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> sudoku[i][j];
        }
    }
    
    memcpy(sudokuOriginal, sudoku, sizeof(sudoku));
    
    cout << endl << "Tabuleiro inicial:" << endl;
    imprimirSudoku();
    
    cout << "Iniciando resolucao..." << endl;
    cout << "Celulas vazias: " << contarCelulasVazias() << endl;
    cout << endl;
    
    if (resolverIterativo()) {
        cout << endl << "SUDOKU RESOLVIDO COM SUCESSO!" << endl;
        cout << "Solucao encontrada:" << endl;
        imprimirSudoku();
    } else {
        cout << endl << "NAO FOI POSSIVEL RESOLVER COMPLETAMENTE." << endl;
        cout << "Tabuleiro atual (faltam " << contarCelulasVazias() 
             << " celulas):" << endl;
        imprimirSudoku();
        
        cout << "Dica: Para Sudokus mais complexos, use o resolvedor recursivo." << endl;
    }
    
    return 0;
}
