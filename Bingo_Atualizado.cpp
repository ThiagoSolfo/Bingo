/*
Trabalho M1 de Algoritmos e Programação II: Bingo;
Professor: Rafael Ballottin Martins;
Integrantes:
    - Homero César de Campos Pytlovanciw
    - Kevin Robert Elias
    - Thiago Marinho Solfo
    - Vinicius José
*/

#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <iostream>
#include "codefun.h"

using namespace std;

#define SIZE 5

void telaInicial();

void inicializaJogadores(string jogadores[SIZE]);

bool trocarNomes();

bool pesquisaSequencial(int vet[], int valor, int tam);

void inicializaLinha(int vet[], int valor = 0, int tam = SIZE);

void bubblesort(int vet[], int tam = SIZE);

void preencheLinha(int vet[SIZE], int linha);

void preencheCartela(int vet[SIZE][SIZE]);

void SorteioCartelas(int Cartelas[SIZE][SIZE][SIZE]);

bool verificaCartelas(int Cartelas[SIZE][SIZE][SIZE]);

void PosicionaCartelas(int Cartelas[SIZE][SIZE][SIZE], int vet[], string jogadores[]);

void imprimeSorteio(int vet[75]);

void sorteioNumero(int Cartelas[SIZE][SIZE][SIZE], int vetor[75], string jogadores[]);

int procuraVencedor(int Cartelas[SIZE][SIZE][SIZE], int vetor[], bool vencedores[]);

void imprimeVencedores(bool vencedores[], string jogadores[]);

bool continuarJogando();

void ShowConsoleCursor(bool showFlag);

void telaFinal();

/*  Início Main  -----------------------------------------------------------------------------------*/
int main() {
    setlocale(LC_ALL, "portuguese");
    srand(time(NULL));

    /// Inicialização de Variáveis

    bool x, y, winners[SIZE], verify = true;
    const int tam = 75;
    int ListaCartelas[SIZE][SIZE][SIZE], vetorSorteio[tam], winner = -1;
    string jogadores[SIZE];

    telaInicial();

    inicializaJogadores(jogadores);

    /// Laço Principal do Bingo

    do {
        Sleep(2000);
        clrscr();
        ShowConsoleCursor(false);

        /*  Laço de verificação de igualdade entre cartelas */
        do {
            SorteioCartelas(ListaCartelas);
            verify = verificaCartelas(ListaCartelas);
        } while (verify);

        /*  Inicializa-se o vetor sorteio com os valores iguais a 100;
            Isso auxilia na lógica de ordenar e exibir os valores sorteados;
        */
        inicializaLinha(vetorSorteio, 100, tam);

        PosicionaCartelas(ListaCartelas, vetorSorteio, jogadores);                      ///  Posiciona as cartelas pela primeira vez na tela;
        Sleep(1000);

        /*  Laço Interno de Sorteio dos Números */
        do {
            gotoxy(43, 23);
            cout << "Aperte a tecla espaço para sortear novo número";
            if (_kbhit()) {
                char tecla = getch();
                switch (tecla) {
                    case ' ':
                        sorteioNumero(ListaCartelas, vetorSorteio, jogadores);          /// Sorteio, print do sorteio e att. das cartelas;
                        procuraVencedor(ListaCartelas, vetorSorteio, winners);          /// Procura vencedores e atualiza a var. de controle caso encontre;
                        for (int i = 0; i < SIZE; i++) {
                            if (winners[i])
                                winner = 0;
                        }
                }
            }
        } while (winner == -1);                                                         /// Condição de parada para caso haja vencedores

        imprimeVencedores(winners, jogadores);                                          /// Imprime os vencedores na tela;
        ShowConsoleCursor(true);

        /*  Verificações para novo jogo */
        x = continuarJogando();                                                         /// Att da variável de controle do loop principal;
        if (!x) {
            telaFinal();
            return 0;                                                                   /// Termina o programa caso o usuário não queira continuar jogando;
        }

        /*  Verifica se o usuário quer trocar os nomes do jogadores */
        y = trocarNomes();
        if (y)
            inicializaJogadores(jogadores);

        winner = -1;                                                                    /// Atualização da variável winner para o novo jogo;
    } while (x);

    return 0;                                                                           /// Cobertura;
}
/*  Fim Main  --------------------------------------------------------------------------------------*/

void telaInicial() {
    /*  Função de início do programa, mostrando os integrantes e do que se compõe o jogo do bingo, e como jogar; */

    ShowConsoleCursor(false);
    cout << "**BINGO**\nTrabalho M1 de Algoritmos e Programação II, da turma 2022.2, do professor Rafael Ballottin, desenvolvido pelos alunos:";
    cout << "\n\n\t- Homero César de Campos Pytlovanciw\n\t- Kevin Robert Elias\n\t- Thiago Marinho Solfo\n\t- Vinícius José";
    gotoxy(0, 8);
    Sleep(2000);
    cout << "Como Jogar:" << endl;
    Sleep(1000);
    cout << "\n\t1) Digite os nomes dos jogadores de cada cartela: 5 jogadores no total!";
    Sleep(1000);
    cout << "\n\t2) Aperte a tecla Espaço para sortear os números!";
    Sleep(1000);
    cout << "\n\t3) Seja um vencedor!\n" << endl;
    Sleep(1000);
    gotoxy(30, 14);
    system("pause");
    clrscr();
    ShowConsoleCursor(true);
}

void inicializaJogadores(string jogadores[SIZE]) {
    /*  Função para dar nomes para os jogadores de cada cartela, necessário vetor como parâmetro;    */

    cout << "Digite os nomes dos jogadores!\n" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << "Cartela " << i + 1 << ": ";
        cin >> jogadores[i];
    }
}

bool trocarNomes() {
    /*  Função para verificar se o usuário deseja alterar o nome dos jogadores;  */

    char p;
    clrscr();
    cout << "Deseja alterar o(s) nome(s) do(s) jogador(es)? ";
    cin >> p;
    switch (p) {
        case 'Y':
            return true;
        case 'N':
            return false;
        case 'y':
            return true;
        case 'n':
            return false;
        default:
            return false;
    }
}

void inicializaLinha(int vet[], int valor, int tam) {
    /*  Função que inicializa um vetor de tamanho 'tam' com todos os seus elementos iguais a 'valor';    */

    for (int i = 0; i < tam; i++) {
        vet[i] = valor;
    }
}

bool pesquisaSequencial(int vet[], int valor, int tam) {
    /*  Realiza a pesquisa sequencial em um vetor 'vet' e retorna se o 'valor' se encontra ou não no vetor;   */

    for (int k = 0; k < tam; k++) {
        if (valor == vet[k])
            return true;
    }
    return false;
}

void bubblesort(int vet[], int tam) {
    /*  Função do BubbleSort */

    int i, j, cond, temp;
    cond = 1;
    for (i = tam - 1; (i >= 1) && (cond == 1); i--) {
        cond = 0;
        for (j = 0; j < i; j++) {
            if (vet[j + 1] < vet[j]) {
                temp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = temp;
                cond = 1;
            }
        }
    }
}

void preencheLinha(int vet[SIZE], int linha) {
    /*  Função que realiza o preenchimento das linhas da cartela de acordo com o índice da 'linha';
        Os valores da linha são randomizados entre 1 e 15 + 'linha'*15, não podendo ser repetidos, e então ordenados;
    */

    inicializaLinha(vet);
    int p;
    for (int i = 0; i < SIZE; i++) {
        do {
            p = rand() % 15 + (1 + linha * 15);
        } while (pesquisaSequencial(vet, p, i));                                        /// Verificação de repetição do valor aleatorizado na linha;
        vet[i] = p;
    }
    bubblesort(vet);
}

void preencheCartela(int vet[SIZE][SIZE]) {
    /*  Função de preenchimento para uma cartela. Preenche as cartelas de acordo com a função 'preencheLinha';   */

    int linha[SIZE];
    for (int i = 0; i < SIZE; i++) {
        preencheLinha(linha, i);
        for (int j = 0; j < SIZE; j++)
            vet[i][j] = linha[j];
    }
}

void SorteioCartelas(int Cartelas[SIZE][SIZE][SIZE]) {
    /*  Função de preenchimento de todas as cartelas. Vetor tridimensional para abrigar o índice da cartela
        além dos valores de cada cartela.
    */

    int Cartela[SIZE][SIZE];
    for (int indice = 0; indice < SIZE; indice++) {
        preencheCartela(Cartela);
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                Cartelas[indice][i][j] = Cartela[i][j];
            }
        }
    }
}

bool verificaCartelas(int Cartelas[SIZE][SIZE][SIZE]) {
    /*  Verifica se uma cartela é igual a alguma outra, comparando elemento por elemento;
        Funcionalidade: compara cartela 0 com 1, depois cartela 0 com 2, 0 com 3, 0 com 4, então 1 com 2, 1 com 3 ...;
        Até chegar na comparação 3 com 4. Se passar do índice 4, retorna falso. Se encontrar cartelas iguais, retorna verdadeiro;
    */

    int k = 0, cond = 0;                                                                /// Inicialização da variável cond e a var de controle k;
    for (int ind = 0; ind < SIZE; ind++) {
        if (ind + 1 >= SIZE)                                                            /// Se chegar na última cartela, não há necessidade de novas comparações;
            return false;
        k = 0;  /// reset da variável de controle k;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                cond = 0;  /// reseta variável cond para 0 (true);
                while (Cartelas[ind][i][j] != Cartelas[ind + k + 1][i][j] && k < SIZE - ind - 1) {
                    i = 0;
                    j = 0;                                                              /// reset dos iteradores e troca de cartela caso encontre 1 elemento diferente;
                    k++;                                                                /// se chegar em k onde k + ind + 1 > SIZE, pula-se para o próximo índice de cartela;
                    cond = 1;                                                           /// cond = 1 caso as cartelas sejam diferentes;
                }
                if (ind + k + 1 >= SIZE) {                                              /// quando extrapolar o limite da matriz;
                    i = 5;
                    j = 5;                                                              /// Não atualizará a variável cond pois não entrará no loop j novamente;
                }
            }
        }
        if (cond == 0)                                                                  /// retornará verdadeiro caso haja cartelas iguais;
            return true;
    }
    return true;                                                                        /// Não deve chegar até esse return, apenas cobertura;
}

void PosicionaCartelas(int Cartelas[SIZE][SIZE][SIZE], int vet[], string jogadores[SIZE]) {
    /*  Função que realiza o posicionamento das cartelas no console;
        A pintura dos valores sorteados de cada cartela ocorre a cada sorteio de um novo número (vide sorteioNumero);
        É também realizado a identificação de cada cartela com cada um dos jogadores abaixo de cada cartela;
    */

    for (int indice = 0; indice < SIZE; indice++) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                gotoxy(48 * (indice % 2) + j * 8, 5 + i + indice / 2 * 8);              /// Lógica de posicionamento dos valores das cartelas;

                /*  Laço de pesquisa para verificar se o valor da cartela já saiu no vetor sorteio; */
                int k = 0;
                while (vet[k] != 100) {
                    if (Cartelas[indice][i][j] == vet[k])
                        textcolor(3, 0);                                                /// Troca a cor do cursor para 'AQUA';
                    k++;
                }

                cout << Cartelas[indice][i][j];
                textcolor(7, 0);  /// Retorna a cor do cursor para 'WHITE' novamente;
            }
        }
        gotoxy(8 + (indice % 2) * 48, 10 + 8 * (indice / 2));                           /// Lógica de posicionamento dos índices dos jogadores
        cout << "jogador " << indice + 1 << ": " << jogadores[indice];
    }
}

void imprimeSorteio(int vet[75]) {
    /*  Função que faz a impressão do vetor sorteio ordenado;
        Realiza a impressão apenas dos valores que já foram sorteados;
    */

    int i = 0;
    while (vet[i] != 100 && i < 75) {
        textcolor(2, 0);                                                                /// Cor 'GREEN';
        gotoxy(5 + 3 * (i % 25), 1 + (i / 25));                                         /// Lógica de posicionamento do vetor sorteio na tela;
        cout << vet[i];
        i++;
    }
    textcolor(7, 0);                                                                    /// Cor 'WHITE' (reset);
}

void sorteioNumero(int Cartelas[SIZE][SIZE][SIZE], int vetor[75], string jogadores[SIZE]) {
    /*  Função que realiza o sorteio de um novo número entre 1 e 75, e o guarda no 'vetor';
        A lógica da função realiza a verificação para que cada número sorteado seja único;
        Realiza o posicionamento das cartelas como os respectivos valores sorteados já pintados;
    */

    int num;
    do {
        num = rand() % 75 + 1;
    } while (pesquisaSequencial(vetor, num, 75));

    vetor[74] = num;                                                                    /// Guarda na última posição para não sobrescrever valores;
    bubblesort(vetor, 75);                                                              /// Ordenação do vetor (Valores sorteados vão para o começo do vetor);
    clrscr();
    cout << "Número Sorteado: " << num;
    PosicionaCartelas(Cartelas, vetor, jogadores);                                      /// Posiciona novamente as cartelas pós clear screen;
    imprimeSorteio(vetor);                                                              /// Imprime o vetor sorteio;
}

int procuraVencedor(int Cartelas[SIZE][SIZE][SIZE], int vetor[], bool vencedores[]) {
    /*  Função que procura vencedores de acordo com o índice das cartelas;
        Caso encontre um vencedor, ele atualiza o vetor 'vencedores' com true para o índice relativo a cartela vencedora;
    */

    for (int i = 0; i < SIZE; i++)
        vencedores[i] = false;  /// Inicialização do vetor vencedores;
    for (int ind = 0; ind < SIZE; ind++) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                /* Laço de pesquisa para verificar se cada valor da cartela se encontra já sorteado */
                int k = 0;
                while (vetor[k] != 100) {
                    k++;
                    if (!pesquisaSequencial(vetor, Cartelas[ind][i][j], 75)) {          /// Se não encontrado o valor no vetor
                        k = 0;                                                          /// a cartela não está 100% preenchida;
                        i = 0;
                        j = 0;
                        ind++;                                                          /// logo não é vencedor e pula-se para o próximo jogador (ind++);
                        if (ind >= 5)
                            return -1;                                                  /// Se todas as cartelas foram verificadas, sai da função;
                    }
                }
            }
        }
        vencedores[ind] = true;                                                         /// Atualiza caso haja um vencedor;
    }
    return -1;                                                                          /// Cobertura;
}

void imprimeVencedores(bool vencedores[], string jogadores[]) {
    /*  Função que realiza a impressão na tela de um ou mais vencedores na tela de acordo com o vetor 'vencedores'; */

    int cont = 0;
    for (int i = 0; i < SIZE; i++) {
        if (vencedores[i]) {
            gotoxy(54, 23 + cont);
            cout << "Vencedor " << cont + 1 << ": " << jogadores[i] << " (cartela " << i + 1 << ")";
            cont++;
        }
    }
    gotoxy(43, 24 + cont);
    Sleep(2000);
    system("pause");
}

bool continuarJogando() {
    /*  Função que verifica se o usuário deseja continuar jogando ou não; */

    clrscr();
    char p;
    do {
        cout << "Deseja continuar jogando? (Y or N): ";
        cin >> p;
        switch (p) {
            case 'Y':
                return true;
            case 'N':
                return false;
            case 'y':
                return true;
            case 'n':
                return false;
            default:
                cout << "Valor inválido, digite Y ou N" << endl;
                Sleep(500);
        }
    } while (true);
}

void ShowConsoleCursor(bool showFlag) {
    /*  Função que define se o cursor do console deve ser mostrado ou não (produzido por Thiago Felski Pereira)*/
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;  /// set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void telaFinal() {
    /*  Tela de finalização do jogo;*/

    ShowConsoleCursor(false);
    clrscr();
    Sleep(500);
    gotoxy(45, 12);
    cout << "OBRIGADO POR JOGAR!!!";
    Sleep(1000);
    clrscr();
}
