/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C++
Problema    : Projeto Sudoku - Resolvedor Recursivo Completo
Data        : 11/06/2026
Objetivo    : Encontrar e exibir todas as soluções possíveis de um Sudoku
              utilizando recursão e backtracking com otimizações.
Aprendizado : Recursão, backtracking, enumeração de soluções, matrizes,
              busca em profundidade, análise de espaço de busca e
              otimização de candidatos.
-------------------------------------------------------------------------- */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int sudoku[9][9];
int sudokuOriginal[9][9];
int totalSolucoes = 0;
int totalChamadas = 0;
int maxSolucoes = 100;

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

void imprimirSudoku(int numeroSolucao = -1) {
    cout << endl;
    if (numeroSolucao > 0) {
        cout << "Solucao " << numeroSolucao << ":" << endl;
    }
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
}

void imprimirSudokuComparativo() {
    cout << endl;
    cout << "Tabuleiro original vs Solucao encontrada:" << endl;
    cout << "  Original     |  Solucao" << endl;
    cout << "  +-------+-------+  +-------+-------+-------+" << endl;
    
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
            cout << "  +-------+-------+  +-------+-------+-------+" << endl;
        }
    }
    cout << "  +-------+-------+  +-------+-------+-------+" << endl;
}

bool completarComUnicos() {
    bool progresso;
    do {
        progresso = false;
        for (int l = 0; l < 9; l++) {
            for (int c = 0; c < 9; c++) {
                if (sudoku[l][c] != 0) continue;
                
                vector<int> candidatos = obterCandidatos(l, c);
                if (candidatos.size() == 1) {
                    sudoku[l][c] = candidatos[0];
                    progresso = true;
                }
            }
        }
    } while (progresso);
    
    return true;
}

bool resolverTodas(int profundidade = 0) {
    totalChamadas++;
    
    if (profundidade > 80) {
        return true;
    }
    
    int linha, coluna;
    
    if (!encontrarMelhorVazio(linha, coluna)) {
        totalSolucoes++;
        
        cout << "Solucao " << totalSolucoes << " encontrada!" << endl;
        imprimirSudoku(totalSolucoes);
        
        if (totalSolucoes == 1) {
            imprimirSudokuComparativo();
        }
        
        return totalSolucoes >= maxSolucoes;
    }
    
    vector<int> candidatos = obterCandidatos(linha, coluna);
    
    if (candidatos.empty()) {
        return false;
    }
    
    for (int valor : candidatos) {
        sudoku[linha][coluna] = valor;
        
        if (resolverTodas(profundidade + 1)) {
            return true;
        }
        
        sudoku[linha][coluna] = 0;
    }
    
    return false;
}

bool resolverComBacktracking() {
    int linha, coluna;
    if (!encontrarVazio(linha, coluna)) {
        totalSolucoes++;
        imprimirSudoku(totalSolucoes);
        return true;
    }
    
    vector<int> candidatos = obterCandidatos(linha, coluna);
    
    for (int valor : candidatos) {
        sudoku[linha][coluna] = valor;
        if (resolverComBacktracking()) {
            return true;
        }
        sudoku[linha][coluna] = 0;
    }
    
    return false;
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
    cout << "Celulas vazias: " << contarCelulasVazias() << "/81" << endl;
    
    int celulasPreenchidas = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] != 0)
                celulasPreenchidas++;
        }
    }
    cout << "Celulas preenchidas: " << celulasPreenchidas << "/81" << endl;
    cout << "Dificuldade estimada: ";
    
    int vazias = contarCelulasVazias();
    if (vazias <= 20) cout << "Facil" << endl;
    else if (vazias <= 35) cout << "Medio" << endl;
    else if (vazias <= 45) cout << "Dificil" << endl;
    else cout << "Muito Dificil" << endl;
    cout << endl;
}

void mostrarMenu() {
    cout << "=== RESOLVEDOR DE SUDOKU - TODAS AS SOLUCOES ===" << endl;
    cout << "Opcoes:" << endl;
    cout << "1 - Encontrar todas as solucoes (com otimizacao)" << endl;
    cout << "2 - Encontrar apenas a primeira solucao" << endl;
    cout << "3 - Encontrar todas as solucoes (sem otimizacao)" << endl;
    cout << "4 - Definir maximo de solucoes (atual: " << maxSolucoes << ")" << endl;
    cout << "0 - Sair" << endl;
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
    imprimirSudoku();
    
    analisarTabuleiro();
    
    do {
        mostrarMenu();
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        
        switch(opcao) {
            case 1: {
                memcpy(sudoku, sudokuOriginal, sizeof(sudoku));
                totalSolucoes = 0;
                totalChamadas = 0;
                
                cout << endl << "Buscando todas as solucoes (com otimizacao)..." << endl;
                cout << "Limite de " << maxSolucoes << " solucoes." << endl;
                cout << endl;
                
                resolverTodas();
                
                cout << endl;
                cout << "=== RESUMO ===" << endl;
                cout << "Total de solucoes encontradas: " << totalSolucoes << endl;
                cout << "Total de chamadas recursivas: " << totalChamadas << endl;
                break;
            }
            
            case 2: {
                memcpy(sudoku, sudokuOriginal, sizeof(sudoku));
                totalSolucoes = 0;
                
                cout << endl << "Buscando a primeira solucao..." << endl;
                cout << endl;
                
                if (resolverComBacktracking()) {
                    cout << endl << "Solucao encontrada!" << endl;
                } else {
                    cout << endl << "Nenhuma solucao encontrada!" << endl;
                }
                break;
            }
            
            case 3: {
                memcpy(sudoku, sudokuOriginal, sizeof(sudoku));
                totalSolucoes = 0;
                totalChamadas = 0;
                
                cout << endl << "Buscando todas as solucoes (sem otimizacao)..." << endl;
                cout << endl;
                
                resolverTodas();
                
                cout << endl;
                cout << "=== RESUMO ===" << endl;
                cout << "Total de solucoes encontradas: " << totalSolucoes << endl;
                cout << "Total de chamadas recursivas: " << totalChamadas << endl;
                break;
            }
            
            case 4: {
                cout << "Digite o novo limite maximo de solucoes: ";
                cin >> maxSolucoes;
                if (maxSolucoes < 1) maxSolucoes = 1;
                cout << "Limite atualizado para " << maxSolucoes << endl;
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
