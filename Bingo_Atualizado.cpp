/*
Trabalho M1 de Algoritmos e Programa��o II: Bingo;
Professor: Rafael Ballottin Martins;
Integrantes:
    - Homero C�sar de Campos Pytlovanciw
    - Kevin Robert Elias
    - Thiago Marinho Solfo
    - Vinicius Jos�
*/

#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <iostream>
#include "codefun.h" /// Utiliza��o do codefun.h integral como passado no material did�tico;

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

/*  In�cio Main  -----------------------------------------------------------------------------------*/
int main() {
    setlocale(LC_ALL, "portuguese");
    srand(time(NULL));

    /// Inicializa��o de Vari�veis

    bool x, y, winners[SIZE], verify = true;
    const int tam = 75;
    int ListaCartelas[SIZE][SIZE][SIZE], vetorSorteio[tam], winner = -1;
    string jogadores[SIZE];

    telaInicial();

    inicializaJogadores(jogadores);

    /// La�o Principal do Bingo

    do {
        Sleep(2000);
        clrscr();
        ShowConsoleCursor(false);

        /*  La�o de verifica��o de igualdade entre cartelas */
        do {
            SorteioCartelas(ListaCartelas);
            verify = verificaCartelas(ListaCartelas);
        } while (verify);

        /*  Inicializa-se o vetor sorteio com os valores iguais a 100;
            Isso auxilia na l�gica de ordenar e exibir os valores sorteados;
        */
        inicializaLinha(vetorSorteio, 100, tam);

        PosicionaCartelas(ListaCartelas, vetorSorteio, jogadores);                      ///  Posiciona as cartelas pela primeira vez na tela;
        Sleep(1000);

        /*  La�o Interno de Sorteio dos N�meros */
        do {
            gotoxy(43, 23);
            cout << "Aperte a tecla espa�o para sortear novo n�mero";
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
        } while (winner == -1);                                                         /// Condi��o de parada para caso haja vencedores

        imprimeVencedores(winners, jogadores);                                          /// Imprime os vencedores na tela;
        ShowConsoleCursor(true);

        /*  Verifica��es para novo jogo */
        x = continuarJogando();                                                         /// Att da vari�vel de controle do loop principal;
        if (!x) {
            telaFinal();
            return 0;                                                                   /// Termina o programa caso o usu�rio n�o queira continuar jogando;
        }
        

        /*  Verifica se o usu�rio quer trocar os nomes do jogadores */
        y = trocarNomes();
        if (y)
            inicializaJogadores(jogadores);

        winner = -1;                                                                    /// Atualiza��o da vari�vel winner para o novo jogo;
    } while (x);

    return 0;                                                                           /// Cobertura;
}
/*  Fim Main  --------------------------------------------------------------------------------------*/

void telaInicial() {
    /*  Fun��o de in�cio do programa, mostrando os integrantes e do que se comp�e o jogo do bingo, e como jogar; */

    ShowConsoleCursor(false);
    cout << "**BINGO**\nTrabalho M1 de Algoritmos e Programa��o II, da turma 2022.2, do professor Rafael Ballottin, desenvolvido pelos alunos:";
    cout << "\n\n\t- Homero C�sar de Campos Pytlovanciw\n\t- Kevin Robert Elias\n\t- Thiago Marinho Solfo\n\t- Vin�cius Jos�";
    gotoxy(0, 8);
    Sleep(2000);
    cout << "Como Jogar:" << endl;
    Sleep(1000);
    cout << "\n\t1) Digite os nomes dos jogadores de cada cartela: 5 jogadores no total!";
    Sleep(1000);
    cout << "\n\t2) Aperte a tecla Espa�o para sortear os n�meros!";
    Sleep(1000);
    cout << "\n\t3) Seja um vencedor!\n" << endl;
    Sleep(1000);
    gotoxy(30, 14);
    system("pause");
    clrscr();
    ShowConsoleCursor(true);
}

void inicializaJogadores(string jogadores[SIZE]) {
    /*  Fun��o para dar nomes para os jogadores de cada cartela, necess�rio vetor como par�metro;    */

    cout << "Digite os nomes dos jogadores!\n" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << "Cartela " << i + 1 << ": ";
        cin >> jogadores[i];
    }
}

bool trocarNomes() {
    /*  Fun��o para verificar se o usu�rio deseja alterar o nome dos jogadores;  */

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
    /*  Fun��o que inicializa um vetor de tamanho 'tam' com todos os seus elementos iguais a 'valor';    */

    for (int i = 0; i < tam; i++) {
        vet[i] = valor;
    }
}

bool pesquisaSequencial(int vet[], int valor, int tam) {
    /*  Realiza a pesquisa sequencial em um vetor 'vet' e retorna se o 'valor' se encontra ou n�o no vetor;   */

    for (int k = 0; k < tam; k++) {
        if (valor == vet[k])
            return true;
    }
    return false;
}

void bubblesort(int vet[], int tam) {
    /*  Fun��o do BubbleSort */

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
    /*  Fun��o que realiza o preenchimento das linhas da cartela de acordo com o �ndice da 'linha';
        Os valores da linha s�o randomizados entre 1 e 15 + 'linha'*15, n�o podendo ser repetidos, e ent�o ordenados;
    */

    inicializaLinha(vet);
    int p;
    for (int i = 0; i < SIZE; i++) {
        do {
            p = rand() % 15 + (1 + linha * 15);
        } while (pesquisaSequencial(vet, p, i));                                        /// Verifica��o de repeti��o do valor aleatorizado na linha;
        vet[i] = p;
    }
    bubblesort(vet);
}

void preencheCartela(int vet[SIZE][SIZE]) {
    /*  Fun��o de preenchimento para uma cartela. Preenche as cartelas de acordo com a fun��o 'preencheLinha';   */

    int linha[SIZE];
    for (int i = 0; i < SIZE; i++) {
        preencheLinha(linha, i);
        for (int j = 0; j < SIZE; j++)
            vet[i][j] = linha[j];
    }
}

void SorteioCartelas(int Cartelas[SIZE][SIZE][SIZE]) {
    /*  Fun��o de preenchimento de todas as cartelas. Vetor tridimensional para abrigar o �ndice da cartela
        al�m dos valores de cada cartela.
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
    /*  Verifica se uma cartela � igual a alguma outra, comparando elemento por elemento;
        Funcionalidade: compara cartela 0 com 1, depois cartela 0 com 2, 0 com 3, 0 com 4, ent�o 1 com 2, 1 com 3 ...;
        At� chegar na compara��o 3 com 4. Se passar do �ndice 4, retorna falso. Se encontrar cartelas iguais, retorna verdadeiro;
    */

    int k = 0, cond = 0;                                                                /// Inicializa��o da vari�vel cond e a var de controle k;
    for (int ind = 0; ind < SIZE; ind++) {
        if (ind + 1 >= SIZE)                                                            /// Se chegar na �ltima cartela, n�o h� necessidade de novas compara��es;
            return false;
        k = 0;  /// reset da vari�vel de controle k;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                cond = 0;  /// reseta vari�vel cond para 0 (true);
                while (Cartelas[ind][i][j] != Cartelas[ind + k + 1][i][j] && k < SIZE - ind - 1) {
                    i = 0;
                    j = 0;                                                              /// reset dos iteradores e troca de cartela caso encontre 1 elemento diferente;
                    k++;                                                                /// se chegar em k onde k + ind + 1 > SIZE, pula-se para o pr�ximo �ndice de cartela;
                    cond = 1;                                                           /// cond = 1 caso as cartelas sejam diferentes;
                }
                if (ind + k + 1 >= SIZE) {                                              /// quando extrapolar o limite da matriz;
                    i = 5;
                    j = 5;                                                              /// N�o atualizar� a vari�vel cond pois n�o entrar� no loop j novamente;
                }
            }
        }
        if (cond == 0)                                                                  /// retornar� verdadeiro caso haja cartelas iguais;
            return true;
    }
    return true;                                                                        /// N�o deve chegar at� esse return, apenas cobertura;
}

void PosicionaCartelas(int Cartelas[SIZE][SIZE][SIZE], int vet[], string jogadores[SIZE]) {
    /*  Fun��o que realiza o posicionamento das cartelas no console;
        A pintura dos valores sorteados de cada cartela ocorre a cada sorteio de um novo n�mero (vide sorteioNumero);
        � tamb�m realizado a identifica��o de cada cartela com cada um dos jogadores abaixo de cada cartela;
    */

    for (int indice = 0; indice < SIZE; indice++) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                gotoxy(48 * (indice % 2) + j * 8, 5 + i + indice / 2 * 8);              /// L�gica de posicionamento dos valores das cartelas;

                /*  La�o de pesquisa para verificar se o valor da cartela j� saiu no vetor sorteio; */
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
        gotoxy(8 + (indice % 2) * 48, 10 + 8 * (indice / 2));                           /// L�gica de posicionamento dos �ndices dos jogadores
        cout << "jogador " << indice + 1 << ": " << jogadores[indice];
    }
}

void imprimeSorteio(int vet[75]) {
    /*  Fun��o que faz a impress�o do vetor sorteio ordenado;
        Realiza a impress�o apenas dos valores que j� foram sorteados;
    */

    int i = 0;
    while (vet[i] != 100 && i < 75) {
        textcolor(2, 0);                                                                /// Cor 'GREEN';
        gotoxy(5 + 3 * (i % 25), 1 + (i / 25));                                         /// L�gica de posicionamento do vetor sorteio na tela;
        cout << vet[i];
        i++;
    }
    textcolor(7, 0);                                                                    /// Cor 'WHITE' (reset);
}

void sorteioNumero(int Cartelas[SIZE][SIZE][SIZE], int vetor[75], string jogadores[SIZE]) {
    /*  Fun��o que realiza o sorteio de um novo n�mero entre 1 e 75, e o guarda no 'vetor';
        A l�gica da fun��o realiza a verifica��o para que cada n�mero sorteado seja �nico;
        Realiza o posicionamento das cartelas como os respectivos valores sorteados j� pintados;
    */

    int num;
    do {
        num = rand() % 75 + 1;
    } while (pesquisaSequencial(vetor, num, 75));

    vetor[74] = num;                                                                    /// Guarda na �ltima posi��o para n�o sobrescrever valores;
    bubblesort(vetor, 75);                                                              /// Ordena��o do vetor (Valores sorteados v�o para o come�o do vetor);
    clrscr();
    cout << "N�mero Sorteado: " << num;
    PosicionaCartelas(Cartelas, vetor, jogadores);                                      /// Posiciona novamente as cartelas p�s clear screen;
    imprimeSorteio(vetor);                                                              /// Imprime o vetor sorteio;
}

int procuraVencedor(int Cartelas[SIZE][SIZE][SIZE], int vetor[], bool vencedores[]) {
    /*  Fun��o que procura vencedores de acordo com o �ndice das cartelas;
        Caso encontre um vencedor, ele atualiza o vetor 'vencedores' com true para o �ndice relativo a cartela vencedora;
    */

    for (int i = 0; i < SIZE; i++)
        vencedores[i] = false;  /// Inicializa��o do vetor vencedores;
    for (int ind = 0; ind < SIZE; ind++) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                /* La�o de pesquisa para verificar se cada valor da cartela se encontra j� sorteado */
                int k = 0;
                while (vetor[k] != 100) {
                    k++;
                    if (!pesquisaSequencial(vetor, Cartelas[ind][i][j], 75)) {          /// Se n�o encontrado o valor no vetor
                        k = 0;                                                          /// a cartela n�o est� 100% preenchida;
                        i = 0;
                        j = 0;
                        ind++;                                                          /// logo n�o � vencedor e pula-se para o pr�ximo jogador (ind++);
                        if (ind >= 5)
                            return -1;                                                  /// Se todas as cartelas foram verificadas, sai da fun��o;
                    }
                }
            }
        }
        vencedores[ind] = true;                                                         /// Atualiza caso haja um vencedor;
    }
    return -1;                                                                          /// Cobertura;
}

void imprimeVencedores(bool vencedores[], string jogadores[]) {
    /*  Fun��o que realiza a impress�o na tela de um ou mais vencedores na tela de acordo com o vetor 'vencedores'; */

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
    /*  Fun��o que verifica se o usu�rio deseja continuar jogando ou n�o; */

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
                cout << "Valor inv�lido, digite Y ou N" << endl;
                Sleep(500);
        }
    } while (true);
}

void ShowConsoleCursor(bool showFlag) {
    /*  Fun��o que define se o cursor do console deve ser mostrado ou n�o (produzido por Thiago Felski Pereira)*/
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;  /// set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void telaFinal() {
    /*  Tela de finaliza��o do jogo;*/

    ShowConsoleCursor(false);
    clrscr();
    Sleep(500);
    gotoxy(45, 12);
    cout << "OBRIGADO POR JOGAR!!!";
    Sleep(1000);
    clrscr();
}