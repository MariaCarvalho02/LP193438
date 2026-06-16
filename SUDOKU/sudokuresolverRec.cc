/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C++
Problema    : Projeto Sudoku - Resolvedor Recursivo
Data        : 11/06/2026
Objetivo    : Resolver automaticamente um Sudoku utilizando recursão e
              backtracking com otimizações.
Aprendizado : Recursão, backtracking, matrizes, busca em profundidade,
              validação de restrições e otimização de candidatos.
-------------------------------------------------------------------------- */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iomanip>

using namespace std;

int sudoku[9][9];
int sudokuOriginal[9][9];
int totalChamadas = 0;
int totalBacktracks = 0;

bool encontrarVazio(int &linha, int &coluna) {
    for (linha = 0; linha < 9; linha++) {
        for (coluna = 0; coluna < 9; coluna++) {
            if (sudoku[linha][coluna] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool encontrarMelhorVazio(int &linha, int &coluna) {
    int melhorLinha = -1, melhorColuna = -1;
    int menorQuantidade = 10;
    
    for (int l = 0; l < 9; l++) {
        for (int c = 0; c < 9; c++) {
            if (sudoku[l][c] != 0) continue;
            
            int quantidade = 0;
            for (int v = 1; v <= 9; v++) {
                if (valorValido(l, c, v)) {
                    quantidade++;
                }
            }
            
            if (quantidade < menorQuantidade) {
                menorQuantidade = quantidade;
                melhorLinha = l;
                melhorColuna = c;
                if (quantidade == 1) break;
            }
        }
        if (menorQuantidade == 1) break;
    }
    
    if (melhorLinha != -1) {
        linha = melhorLinha;
        coluna = melhorColuna;
        return true;
    }
    return false;
}

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

vector<int> obterCandidatos(int linha, int coluna) {
    vector<int> candidatos;
    
    for (int v = 1; v <= 9; v++) {
        if (valorValido(linha, coluna, v)) {
            candidatos.push_back(v);
        }
    }
    
    return candidatos;
}

bool completarUnicos() {
    bool progresso = false;
    bool mudou;
    
    do {
        mudou = false;
        for (int l = 0; l < 9; l++) {
            for (int c = 0; c < 9; c++) {
                if (sudoku[l][c] != 0) continue;
                
                vector<int> candidatos = obterCandidatos(l, c);
                if (candidatos.size() == 1) {
                    sudoku[l][c] = candidatos[0];
                    mudou = true;
                    progresso = true;
                }
            }
        }
    } while (mudou);
    
    return progresso;
}

bool resolverRecursivo(int profundidade = 0) {
    totalChamadas++;
    
    if (profundidade > 80) {
        return true;
    }
    
    int linha, coluna;
    
    if (!encontrarMelhorVazio(linha, coluna)) {
        return true;
    }
    
    vector<int> candidatos = obterCandidatos(linha, coluna);
    
    if (candidatos.empty()) {
        totalBacktracks++;
        return false;
    }
    
    for (int valor : candidatos) {
        sudoku[linha][coluna] = valor;
        
        if (resolverRecursivo(profundidade + 1)) {
            return true;
        }
        
        sudoku[linha][coluna] = 0;
        totalBacktracks++;
    }
    
    return false;
}

bool resolverClassico(int profundidade = 0) {
    totalChamadas++;
    
    int linha, coluna;
    
    if (!encontrarVazio(linha, coluna)) {
        return true;
    }
    
    for (int valor = 1; valor <= 9; valor++) {
        if (valorValido(linha, coluna, valor)) {
            sudoku[linha][coluna] = valor;
            
            if (resolverClassico(profundidade + 1)) {
                return true;
            }
            
            sudoku[linha][coluna] = 0;
            totalBacktracks++;
        }
    }
    
    return false;
}

void imprimirSudoku(int opcao = 0) {
    cout << endl;
    if (opcao == 1) {
        cout << "  +-------+-------+-------+" << endl;
        for (int i = 0; i < 9; i++) {
            cout << (i+1) << " | ";
            for (int j = 0; j < 9; j++) {
                if (j == 3 || j == 6) cout << "| ";
                if (sudoku[i][j] == 0)
                    cout << ". ";
                else
                    cout << sudoku[i][j] << " ";
            }
            cout << "|" << endl;
            if (i == 2 || i == 5) {
                cout << "  +-------+-------+-------+" << endl;
            }
        }
        cout << "  +-------+-------+-------+" << endl;
    } else {
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
    }
    cout << endl;
}

void imprimirComparativo() {
    cout << endl;
    cout << "Tabuleiro original vs Solucao:" << endl;
    cout << "  Original     |  Solucao" << endl;
    cout << "  +-------+-------+  +-------+-------+" << endl;
    
    for (int i = 0; i < 9; i++) {
        cout << (i+1) << " | ";
        for (int j = 0; j < 9; j++) {
            if (j == 3 || j == 6) cout << "| ";
            if (sudokuOriginal[i][j] == 0)
                cout << ". ";
            else
                cout << sudokuOriginal[i][j] << " ";
        }
        cout << "|  ";
        
        cout << (i+1) << " | ";
        for (int j = 0; j < 9; j++) {
            if (j == 3 || j == 6) cout << "| ";
            if (sudoku[i][j] == 0)
                cout << ". ";
            else
                cout << sudoku[i][j] << " ";
        }
        cout << "|" << endl;
        
        if (i == 2 || i == 5) {
            cout << "  +-------+-------+  +-------+-------+" << endl;
        }
    }
    cout << "  +-------+-------+  +-------+-------+" << endl;
    cout << endl;
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

void analisarTabuleiro() {
    cout << "=== ANALISE DO TABULEIRO ===" << endl;
    int vazias = contarCelulasVazias();
    cout << "Celulas vazias: " << vazias << "/81" << endl;
    cout << "Celulas preenchidas: " << (81 - vazias) << "/81" << endl;
    
    cout << "Dificuldade estimada: ";
    if (vazias <= 20) cout << "Facil" << endl;
    else if (vazias <= 35) cout << "Medio" << endl;
    else if (vazias <= 45) cout << "Dificil" << endl;
    else cout << "Muito Dificil" << endl;
    cout << endl;
}

void mostrarMenu() {
    cout << "=== RESOLVEDOR RECURSIVO DE SUDOKU ===" << endl;
    cout << "Opcoes:" << endl;
    cout << "1 - Resolver com otimizacao (recomendado)" << endl;
    cout << "2 - Resolver sem otimizacao (classico)" << endl;
    cout << "3 - Mostrar estatisticas detalhadas" << endl;
    cout << "4 - Resetar tabuleiro" << endl;
    cout << "0 - Sair" << endl;
    cout << endl;
}

void mostrarEstatisticas() {
    cout << "=== ESTATISTICAS DA ULTIMA EXECUCAO ===" << endl;
    cout << "Total de chamadas recursivas: " << totalChamadas << endl;
    cout << "Total de backtracks: " << totalBacktracks << endl;
    cout << "Eficiencia: ";
    if (totalChamadas > 0) {
        float eficiencia = (float)(totalChamadas - totalBacktracks) / totalChamadas * 100;
        cout << fixed << setprecision(2) << eficiencia << "%" << endl;
    } else {
        cout << "N/A" << endl;
    }
    cout << endl;
}

int main() {
    int opcao;
    
    cout << "=== RESOLVEDOR RECURSIVO DE SUDOKU ===" << endl;
    cout << "Digite o tabuleiro (0 para celulas vazias):" << endl;
    cout << endl;
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> sudoku[i][j];
        }
    }
    
    memcpy(sudokuOriginal, sudoku, sizeof(sudoku));
    
    cout << endl << "Tabuleiro inicial:" << endl;
    imprimirSudoku(1);
    
    analisarTabuleiro();
    
    do {
        mostrarMenu();
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        
        switch(opcao) {
            case 1: {
                memcpy(sudoku, sudokuOriginal, sizeof(sudoku));
                totalChamadas = 0;
                totalBacktracks = 0;
                
                cout << endl << "Resolvendo com otimizacao..." << endl;
                cout << endl;
                
                bool resolveu = resolverRecursivo();
                
                if (resolveu) {
                    cout << "SUDOKU RESOLVIDO COM SUCESSO!" << endl;
                    imprimirSudoku(1);
                    imprimirComparativo();
                } else {
                    cout << "NAO EXISTE SOLUCAO PARA ESTE TABULEIRO." << endl;
                }
                
                mostrarEstatisticas();
                break;
            }
            
            case 2: {
                memcpy(sudoku, sudokuOriginal, sizeof(sudoku));
                totalChamadas = 0;
                totalBacktracks = 0;
                
                cout << endl << "Resolvendo sem otimizacao..." << endl;
                cout << endl;
                
                bool resolveu = resolverClassico();
                
                if (resolveu) {
                    cout << "SUDOKU RESOLVIDO COM SUCESSO!" << endl;
                    imprimirSudoku(1);
                    imprimirComparativo();
                } else {
                    cout << "NAO EXISTE SOLUCAO PARA ESTE TABULEIRO." << endl;
                }
                
                mostrarEstatisticas();
                break;
            }
            
            case 3: {
                mostrarEstatisticas();
                break;
            }
            
            case 4: {
                memcpy(sudoku, sudokuOriginal, sizeof(sudoku));
                cout << "Tabuleiro resetado para o original." << endl;
                imprimirSudoku(1);
                break;
            }
            
            case 0: {
                cout << "Saindo..." << endl;
                break;
            }
            
            default: {
                cout << "Opcao invalida!" << endl;
                break;
            }
        }
        
        cout << endl;
        if (opcao != 0) {
            cout << "Pressione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        
    } while (opcao != 0);
    
    return 0;
}
