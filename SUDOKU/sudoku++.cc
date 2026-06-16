/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C++
Problema    : Projeto Sudoku++ - Verificador
Data        : 14/06/2026
Objetivo    : Verificar uma grade Sudoku contendo símbolos de 1 a 10,
              analisando linhas, colunas e quadrantes.
              O tabuleiro pode ter tamanho variável (N x N).
Aprendizado : Matrizes, conjuntos (set), strings, validação de dados,
              alocação dinâmica e generalização de algoritmos.
-------------------------------------------------------------------------- */

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<string>> sudoku;
int tamanho;

bool validarValores() {
    for(int i = 0; i < tamanho; i++) {
        for(int j = 0; j < tamanho; j++) {
            try {
                int valor = stoi(sudoku[i][j]);
                if(valor < 1 || valor > 10) {
                    cout << "Valor invalido na posicao (" << i+1 << "," << j+1 
                         << "): " << sudoku[i][j] << " (deve estar entre 1 e 10)" << endl;
                    return false;
                }
            } catch (...) {
                cout << "Valor invalido na posicao (" << i+1 << "," << j+1 
                     << "): " << sudoku[i][j] << " (nao eh um numero)" << endl;
                return false;
            }
        }
    }
    return true;
}
bool verificarElementosUnicos(const vector<string>& elementos) {
    set<string> conjunto;
    
    for(const string& elem : elementos) {
        if(elem != "0" && elem != ".") {
            if(conjunto.find(elem) != conjunto.end()) {
                return false; 
            }
            conjunto.insert(elem);
        }
    }
    
    return true;
}
bool verificaLinha(int linha) {
    vector<string> elementos;
    
    for(int coluna = 0; coluna < tamanho; coluna++) {
        if(sudoku[linha][coluna] != "0" && sudoku[linha][coluna] != ".") {
            elementos.push_back(sudoku[linha][coluna]);
        }
    }
    
    return verificarElementosUnicos(elementos);
}
bool verificaColuna(int coluna) {
    vector<string> elementos;
    
    for(int linha = 0; linha < tamanho; linha++) {
        if(sudoku[linha][coluna] != "0" && sudoku[linha][coluna] != ".") {
            elementos.push_back(sudoku[linha][coluna]);
        }
    }
    
    return verificarElementosUnicos(elementos);
}

bool verificaQuadrante(int bloco) {
    vector<string> elementos;
    
    int tamanhoQuadrante = sqrt(tamanho);
    
    if(tamanhoQuadrante * tamanhoQuadrante != tamanho) {
        for(int j = 0; j < tamanho; j++) {
            if(sudoku[bloco][j] != "0" && sudoku[bloco][j] != ".") {
                elementos.push_back(sudoku[bloco][j]);
            }
        }
    } else {
        int linhaInicial = tamanhoQuadrante * (bloco / tamanhoQuadrante);
        int colunaInicial = tamanhoQuadrante * (bloco % tamanhoQuadrante);
        
        for(int i = 0; i < tamanhoQuadrante; i++) {
            for(int j = 0; j < tamanhoQuadrante; j++) {
                string valor = sudoku[linhaInicial + i][colunaInicial + j];
                if(valor != "0" && valor != ".") {
                    elementos.push_back(valor);
                }
            }
        }
    }
    
    return verificarElementosUnicos(elementos);
}
bool verificarSudoku() {
    if(!validarValores()) {
        return false;
    }
    for(int i = 0; i < tamanho; i++) {
        if(!verificaLinha(i)) {
            cout << "Erro na linha " << i+1 << ": elementos duplicados" << endl;
            return false;
        }
    }
    
    for(int j = 0; j < tamanho; j++) {
        if(!verificaColuna(j)) {
            cout << "Erro na coluna " << j+1 << ": elementos duplicados" << endl;
            return false;
        }
    }
    
    int numQuadrantes = tamanho;
    if(sqrt(tamanho) * sqrt(tamanho) == tamanho) {
        numQuadrantes = tamanho;
    }
    
    for(int b = 0; b < numQuadrantes; b++) {
        if(!verificaQuadrante(b)) {
            cout << "Erro no quadrante " << b+1 << ": elementos duplicados" << endl;
            return false;
        }
    }
    
    return true;
}
void exibirTabuleiro() {
    cout << "\nTabuleiro " << tamanho << "x" << tamanho << ":" << endl;
    cout << "  ";
    for(int j = 0; j < tamanho; j++) {
        cout << " " << j+1;
    }
    cout << endl;
    
    for(int i = 0; i < tamanho; i++) {
        cout << (i+1) << " ";
        for(int j = 0; j < tamanho; j++) {
            cout << " " << sudoku[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
bool lerTabuleiro() {
    if(!(cin >> tamanho)) {
        cout << "Erro: Nao foi possivel ler o tamanho do tabuleiro" << endl;
        return false;
    }
    if(tamanho < 1 || tamanho > 10) {
        cout << "Erro: Tamanho do tabuleiro deve estar entre 1 e 10" << endl;
        return false;
    }
    sudoku.resize(tamanho);
    for(int i = 0; i < tamanho; i++) {
        sudoku[i].resize(tamanho);
    }
    for(int i = 0; i < tamanho; i++) {
        for(int j = 0; j < tamanho; j++) {
            cin >> sudoku[i][j];
        }
    }
    
    return true;
}
int main() {
    cout << "=== VERIFICADOR SUDOKU++ ===" << endl;
    cout << "Valores permitidos: 1 a 10" << endl;
    cout << "Use '0' ou '.' para celulas vazias" << endl;
    cout << "Primeiro digite o tamanho do tabuleiro (N), depois os NxN valores" << endl;
    cout << endl;
    
    if(!lerTabuleiro()) {
        return 1;
    }
    
    exibirTabuleiro();
    
    bool valido = verificarSudoku();
    
    cout << endl;
    cout << "=== RESULTADO ===" << endl;
    if(valido) {
        cout << "Sudoku++ valido!" << endl;
        cout << "Parabens! Todas as regras foram respeitadas." << endl;
    } else {
        cout << "Sudoku++ invalido!" << endl;
        cout << "O tabuleiro nao atende as regras do Sudoku++." << endl;
    }
    cout << endl;
    
    return 0;
}
