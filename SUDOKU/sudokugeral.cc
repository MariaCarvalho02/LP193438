/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C++
Problema    : Projeto SudokuGeral - Verificador Universal
Data        : 11/06/2026
Objetivo    : Verificar uma grade Sudoku genérica onde os valores podem
              ser quaisquer símbolos (números, letras, palavras, etc.).
              O tabuleiro pode ter tamanho variável (N x N).
Aprendizado : Matrizes, conjuntos (set), strings, alocação dinâmica,
              generalização de algoritmos e tratamento de dados variados.
-------------------------------------------------------------------------- */

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

vector<vector<string>> sudoku;
int tamanho;
set<string> valoresUnicos;

bool isCelulaVazia(const string& valor) {
    string temp = valor;
    temp.erase(remove_if(temp.begin(), temp.end(), ::isspace), temp.end());
    
    return temp.empty() || temp == "0" || temp == "." || 
           temp == "-" || temp == "_" || temp == "null" ||
           temp == "vazio" || temp == "empty";
}

void extrairValoresDoTabuleiro() {
    valoresUnicos.clear();
    
    for(int i = 0; i < tamanho; i++) {
        for(int j = 0; j < tamanho; j++) {
            if(!isCelulaVazia(sudoku[i][j])) {
                valoresUnicos.insert(sudoku[i][j]);
            }
        }
    }
}

bool verificarElementosUnicos(const vector<string>& elementos) {
    set<string> conjunto;
    
    for(const string& elem : elementos) {
        if(!isCelulaVazia(elem)) {
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
        if(!isCelulaVazia(sudoku[linha][coluna])) {
            elementos.push_back(sudoku[linha][coluna]);
        }
    }
    
    return verificarElementosUnicos(elementos);
}

bool verificaColuna(int coluna) {
    vector<string> elementos;
    
    for(int linha = 0; linha < tamanho; linha++) {
        if(!isCelulaVazia(sudoku[linha][coluna])) {
            elementos.push_back(sudoku[linha][coluna]);
        }
    }
    
    return verificarElementosUnicos(elementos);
}

bool verificaQuadranteGeral(int bloco) {
    vector<string> elementos;
    
    if(tamanho == 1) {
        return true;
    }
    
    int tamanhoQuadrante = (int)sqrt(tamanho);
    
    if(tamanhoQuadrante * tamanhoQuadrante != tamanho) {
        if(tamanho <= 9) {
            for(int i = 0; i < tamanho; i++) {
                for(int j = 0; j < tamanho; j++) {
                    if(!isCelulaVazia(sudoku[i][j])) {
                        elementos.push_back(sudoku[i][j]);
                    }
                }
            }
        } else {
            for(int j = 0; j < tamanho; j++) {
                if(!isCelulaVazia(sudoku[bloco][j])) {
                    elementos.push_back(sudoku[bloco][j]);
                }
            }
        }
    } else {
        int linhaInicial = tamanhoQuadrante * (bloco / tamanhoQuadrante);
        int colunaInicial = tamanhoQuadrante * (bloco % tamanhoQuadrante);
        
        for(int i = 0; i < tamanhoQuadrante; i++) {
            for(int j = 0; j < tamanhoQuadrante; j++) {
                string valor = sudoku[linhaInicial + i][colunaInicial + j];
                if(!isCelulaVazia(valor)) {
                    elementos.push_back(valor);
                }
            }
        }
    }
    
    return verificarElementosUnicos(elementos);
}

bool verificarSudokuGeral() {
    extrairValoresDoTabuleiro();
    
    cout << "Valores encontrados no tabuleiro: ";
    for(const string& v : valoresUnicos) {
        cout << "\"" << v << "\" ";
    }
    cout << endl << endl;
    
    cout << "Verificando linhas..." << endl;
    for(int i = 0; i < tamanho; i++) {
        if(!verificaLinha(i)) {
            cout << "  Erro na linha " << i+1 << ": elementos duplicados" << endl;
            return false;
        }
        cout << "  Linha " << i+1 << " OK" << endl;
    }
    
    cout << "Verificando colunas..." << endl;
    for(int j = 0; j < tamanho; j++) {
        if(!verificaColuna(j)) {
            cout << "  Erro na coluna " << j+1 << ": elementos duplicados" << endl;
            return false;
        }
        cout << "  Coluna " << j+1 << " OK" << endl;
    }
    
    cout << "Verificando quadrantes..." << endl;
    int numQuadrantes;
    
    int tamanhoQuadrante = (int)sqrt(tamanho);
    if(tamanhoQuadrante * tamanhoQuadrante == tamanho && tamanho > 1) {
        numQuadrantes = tamanho;
    } else {
        numQuadrantes = tamanho;
    }
    
    for(int b = 0; b < numQuadrantes; b++) {
        if(!verificaQuadranteGeral(b)) {
            cout << "  Erro no quadrante " << b+1 << ": elementos duplicados" << endl;
            return false;
        }
        cout << "  Quadrante " << b+1 << " OK" << endl;
    }
    
    return true;
}

bool lerTabuleiroGeral() {
    string linha;
    
    if(!(cin >> tamanho)) {
        cout << "Erro: Nao foi possivel ler o tamanho do tabuleiro" << endl;
        return false;
    }
    
    if(tamanho < 1) {
        cout << "Erro: Tamanho do tabuleiro deve ser maior que 0" << endl;
        return false;
    }
    
    if(tamanho > 20) {
        cout << "Aviso: Tabuleiro muito grande (" << tamanho << "x" << tamanho 
             << "). A verificacao pode ser lenta." << endl;
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

void exibirTabuleiroGeral() {
    int larguraMax = 2;
    for(int i = 0; i < tamanho; i++) {
        for(int j = 0; j < tamanho; j++) {
            if((int)sudoku[i][j].length() + 1 > larguraMax) {
                larguraMax = sudoku[i][j].length() + 1;
            }
        }
    }
    
    cout << "\nTabuleiro " << tamanho << "x" << tamanho << ":" << endl;
    
    cout << "   ";
    for(int j = 0; j < tamanho; j++) {
        cout << " " << j+1;
        for(int k = 0; k < larguraMax - 1; k++) cout << " ";
    }
    cout << endl;
    
    cout << "  +";
    for(int j = 0; j < tamanho; j++) {
        for(int k = 0; k < larguraMax; k++) cout << "-";
        if(j < tamanho-1) cout << "+";
    }
    cout << endl;
    
    for(int i = 0; i < tamanho; i++) {
        cout << (i+1) << " |";
        for(int j = 0; j < tamanho; j++) {
            string valor = sudoku[i][j];
            if(isCelulaVazia(valor)) {
                cout << " .";
                for(int k = 0; k < larguraMax - 1; k++) cout << " ";
            } else {
                cout << " " << valor;
                for(int k = 0; k < larguraMax - valor.length(); k++) cout << " ";
            }
            if(j < tamanho-1) cout << "|";
        }
        cout << "|" << endl;
        
        if(tamanho > 1 && i < tamanho-1) {
            int tamanhoQuadrante = (int)sqrt(tamanho);
            if(tamanhoQuadrante * tamanhoQuadrante == tamanho && 
               (i+1) % tamanhoQuadrante == 0) {
                cout << "  +";
                for(int j = 0; j < tamanho; j++) {
                    for(int k = 0; k < larguraMax; k++) cout << "-";
                    if(j < tamanho-1) cout << "+";
                }
                cout << endl;
            }
        }
    }
    
    cout << "  +";
    for(int j = 0; j < tamanho; j++) {
        for(int k = 0; k < larguraMax; k++) cout << "-";
        if(j < tamanho-1) cout << "+";
    }
    cout << endl;
    cout << endl;
}

void analisarTabuleiro() {
    int celulasVazias = 0;
    int celulasPreenchidas = 0;
    set<string> valoresEncontrados;
    
    for(int i = 0; i < tamanho; i++) {
        for(int j = 0; j < tamanho; j++) {
            if(isCelulaVazia(sudoku[i][j])) {
                celulasVazias++;
            } else {
                celulasPreenchidas++;
                valoresEncontrados.insert(sudoku[i][j]);
            }
        }
    }
    
    cout << "=== ANALISE DO TABULEIRO ===" << endl;
    cout << "Tamanho: " << tamanho << "x" << tamanho << endl;
    cout << "Celulas preenchidas: " << celulasPreenchidas << endl;
    cout << "Celulas vazias: " << celulasVazias << endl;
    cout << "Valores distintos encontrados: " << valoresEncontrados.size() << endl;
    cout << "Valores: ";
    for(const string& v : valoresEncontrados) {
        cout << "\"" << v << "\" ";
    }
    cout << endl << endl;
}

int main() {
    cout << "=========================================" << endl;
    cout << "     VERIFICADOR SUDOKU GERAL           " << endl;
    cout << "=========================================" << endl;
    cout << "Caracteristicas:" << endl;
    cout << "  - Valores podem ser NUMEROS, LETRAS, PALAVRAS" << endl;
    cout << "  - Celulas vazias: 0, ., -, _, vazio, empty" << endl;
    cout << "  - Tamanho variavel: N x N" << endl;
    cout << "  - Validacao de linhas, colunas e quadrantes" << endl;
    cout << endl;
    cout << "Formato de entrada:" << endl;
    cout << "  Primeiro: tamanho N" << endl;
    cout << "  Depois: N linhas com N valores cada" << endl;
    cout << endl;
    cout << "Exemplo de entrada:" << endl;
    cout << "  4" << endl;
    cout << "  A B C D" << endl;
    cout << "  B C D A" << endl;
    cout << "  C D A B" << endl;
    cout << "  D A B C" << endl;
    cout << endl;
    cout << "=========================================" << endl;
    cout << endl;
    
    if(!lerTabuleiroGeral()) {
        cout << "Erro ao ler o tabuleiro." << endl;
        return 1;
    }
    
    exibirTabuleiroGeral();
    
    analisarTabuleiro();
    
    cout << "=== INICIANDO VERIFICACAO ===" << endl;
    bool valido = verificarSudokuGeral();
    
    cout << endl;
    cout << "=========================================" << endl;
    cout << "           RESULTADO FINAL               " << endl;
    cout << "=========================================" << endl;
    if(valido) {
        cout << "  ✅ SUDOKU GERAL VALIDO!" << endl;
        cout << "  O tabuleiro atende todas as regras." << endl;
    } else {
        cout << "  ❌ SUDOKU GERAL INVALIDO!" << endl;
        cout << "  O tabuleiro nao atende as regras." << endl;
    }
    cout << "=========================================" << endl;
    cout << endl;
    
    return 0;
}
