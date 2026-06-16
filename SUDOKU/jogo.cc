/* --------------------------------------------------------------------------
Disciplina  : Lógica de Programação, turma IB, 2026S1
Nome        : Maria Eduarda de Carvalho Raimundo
Linguagem   : C++
Problema    : Projeto Sudoku - Jogo Interativo
Data        : 11/06/2026
Objetivo    : Permitir que o usuário jogue Sudoku no console realizando
              inserções de valores e verificando a validade das jogadas.
              Carrega o tabuleiro do arquivo input2.txt
Aprendizado : Matrizes, funções, validação de dados, interação com o
              usuário, manipulação de tabuleiros bidimensionais e
              leitura de arquivos.
-------------------------------------------------------------------------- */

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int sudoku[9][9];
int sudokuOriginal[9][9];

int sudokuPadrao[9][9] =
{
    {1,3,2,5,7,9,4,6,8},
    {4,0,8,2,6,1,3,7,5},
    {7,5,6,3,8,4,2,1,9},
    {6,4,3,0,5,8,7,9,2},
    {5,2,1,7,9,3,8,4,6},
    {9,8,7,4,2,6,5,3,0},
    {2,1,4,9,3,5,6,8,7},
    {3,6,5,8,1,7,9,2,4},
    {8,7,0,6,4,2,0,5,3}
};

bool carregarTabuleiro(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    
    if(!arquivo.is_open()) {
        cout << "Erro: Nao foi possivel abrir o arquivo " << nomeArquivo << endl;
        return false;
    }
    
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            arquivo >> sudoku[i][j];
        }
    }
    
    arquivo.close();
    
    memcpy(sudokuOriginal, sudoku, sizeof(sudoku));
    
    return true;
}
void mostrarTabuleiro() {
    cout << endl;
    cout << "    1 2 3   4 5 6   7 8 9" << endl;
    cout << "  +-------+-------+-------+" << endl;
    
    for(int i = 0; i < 9; i++) {
        cout << (i+1) << " | ";
        
        for(int j = 0; j < 9; j++) {
            if(j == 3 || j == 6) cout << "| ";
            
            if(sudoku[i][j] == 0)
                cout << ". ";
            else
                cout << sudoku[i][j] << " ";
        }
        
        cout << "|" << endl;
        
        if(i == 2 || i == 5) {
            cout << "  +-------+-------+-------+" << endl;
        }
    }
    
    cout << "  +-------+-------+-------+" << endl;
    cout << endl;
}
bool verificarJogada(int linha, int coluna, int valor) {
    for(int i = 0; i < 9; i++) {
        if(sudoku[linha][i] == valor)
            return false;
    }
    
    for(int i = 0; i < 9; i++) {
        if(sudoku[i][coluna] == valor)
            return false;
    }
    
    int inicioLinha = (linha / 3) * 3;
    int inicioColuna = (coluna / 3) * 3;
    
    for(int i = inicioLinha; i < inicioLinha + 3; i++) {
        for(int j = inicioColuna; j < inicioColuna + 3; j++) {
            if(sudoku[i][j] == valor)
                return false;
        }
    }
    
    return true;
}

bool validarEntrada(int linha, int coluna, int valor) {
    return (linha >= 1 && linha <= 9 && 
            coluna >= 1 && coluna <= 9 && 
            valor >= 1 && valor <= 9);
}

bool completo() {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(sudoku[i][j] == 0)
                return false;
        }
    }
    return true;
}

int contarCelulasPreenchidas() {
    int count = 0;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(sudoku[i][j] != 0)
                count++;
        }
    }
    return count;
}
void darDica() {
    bool encontrou = false;
    
    for(int i = 0; i < 9 && !encontrou; i++) {
        for(int j = 0; j < 9 && !encontrou; j++) {
            if(sudoku[i][j] == 0) {
                cout << "Dica para a celula (" << (i+1) << "," << (j+1) << "): ";
                
                int possiveis[9], qtd = 0;
                for(int v = 1; v <= 9; v++) {
                    if(verificarJogada(i, j, v)) {
                        possiveis[qtd++] = v;
                    }
                }
                
                if(qtd == 0) {
                    cout << "Nenhum valor possivel!" << endl;
                } else {
                    cout << "{ ";
                    for(int k = 0; k < qtd; k++) {
                        cout << possiveis[k];
                        if(k < qtd-1) cout << ", ";
                    }
                    cout << " }" << endl;
                }
                
                encontrou = true;
            }
        }
    }
    
    if(!encontrou) {
        cout << "O tabuleiro ja esta completo!" << endl;
    }
}

int main() {
    int opcao;
    bool tabuleiroCarregado = false;
    
    if(carregarTabuleiro("input2.txt")) {
        cout << "Tabuleiro carregado do arquivo input2.txt com sucesso!" << endl;
        tabuleiroCarregado = true;
    } else {
        cout << "Usando tabuleiro padrao." << endl;
        memcpy(sudoku, sudokuPadrao, sizeof(sudoku));
        memcpy(sudokuOriginal, sudoku, sizeof(sudoku));
    }
    
    do {
        mostrarTabuleiro();
        
        cout << "Celulas preenchidas: " << contarCelulasPreenchidas() << "/81" << endl;
        cout << "Tabuleiro: " << (tabuleiroCarregado ? "input2.txt" : "padrao") << endl;
        cout << endl;
        
        cout << "=== MENU ===" << endl;
        cout << "1 - Inserir valor" << endl;
        cout << "2 - Verificar conclusao" << endl;
        cout << "3 - Dica" << endl;
        cout << "4 - Reiniciar jogo" << endl;
        cout << "0 - Sair" << endl;
        cout << endl;
        cout << "Opcao: ";
        cin >> opcao;
        
        switch(opcao) {
            case 1: {
                int linha, coluna, valor;
                
                cout << "Linha (1-9): ";
                cin >> linha;
                
                cout << "Coluna (1-9): ";
                cin >> coluna;
                
                cout << "Valor (1-9): ";
                cin >> valor;
                
                if(!validarEntrada(linha, coluna, valor)) {
                    cout << "Valores invalidos! Use linha/coluna (1-9) e valor (1-9)." << endl;
                    break;
                }
                
                linha--;
                coluna--;
                
                if(sudokuOriginal[linha][coluna] != 0) {
                    cout << "Esta celula faz parte do tabuleiro original e nao pode ser alterada!" << endl;
                    break;
                }
                
                if(sudoku[linha][coluna] != 0) {
                    cout << "Posicao ja preenchida." << endl;
                    break;
                }
                
                if(verificarJogada(linha, coluna, valor)) {
                    sudoku[linha][coluna] = valor;
                    cout << "Jogada aceita!" << endl;
                    
                    if(completo()) {
                        cout << endl;
                        cout << "PARABENS! Voce completou o Sudoku!" << endl;
                        mostrarTabuleiro();
                    }
                } else {
                    cout << "Jogada invalida! Este valor conflita com as regras do Sudoku." << endl;
                }
                break;
            }
            
            case 2: {
                if(completo()) {
                    cout << "PARABENS! O Sudoku esta completo!" << endl;
                } else {
                    cout << "Ainda existem " << (81 - contarCelulasPreenchidas()) 
                         << " espacos vazios." << endl;
                }
                break;
            }
            
            case 3: {
                darDica();
                break;
            }
            
            case 4: {
                memcpy(sudoku, sudokuOriginal, sizeof(sudoku));
                cout << "Jogo reiniciado!" << endl;
                break;
            }
            
            case 0: {
                cout << "Saindo do jogo..." << endl;
                break;
            }
            
            default: {
                cout << "Opcao invalida! Tente novamente." << endl;
                break;
            }
        }
        
        cout << endl;
        system("pause"); 
        
    } while(opcao != 0);
    
    return 0;
}
