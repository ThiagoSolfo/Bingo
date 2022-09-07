/*
Define uma cartela ordenada do bingo.

Faltante:
    - "Não pode haver cartelas repetidas"

Integrantes:
    - Homero César de Campos
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
void inicializaJogadores(string jogadores[SIZE]);

bool trocarNomes();

bool SIS(int vet[SIZE], int valor, int tam);

void inicializaLinha(int vet[], int valor = 0, int tam = SIZE);

void bubblesort(int vet[], int tam = SIZE);

void preencheLinha(int vet[SIZE], int linha);

void preencheCartela(int vet[SIZE][SIZE]);

void SorteioCartelas(int Cartelas[SIZE][SIZE][SIZE]);

void PosicionaCartelas(int Cartelas[SIZE][SIZE][SIZE], int vet[], string jogadores[]);

void imprimeSorteio(int vet[75]);

void sorteioNumero(int Cartelas[SIZE][SIZE][SIZE], int vetor[75], string jogadores[]);

int procuraVencedor(int Cartelas[SIZE][SIZE][SIZE], int vetor[], bool vencedores[]);

void imprimeVencedores(bool vencedores[], string jogadores[]);

bool continuarJogando();

int main() {
    setlocale(LC_ALL, "portuguese");
    srand(time(NULL));
    bool x, y, winners[SIZE];
    const int tam = 75;
    int ListaCartelas[SIZE][SIZE][SIZE], vetorSorteio[tam];
    int winner = -1;
    string jogadores[SIZE];
    inicializaJogadores(jogadores);

    do {
        Sleep(2000);
        clrscr();
        ShowConsoleCursor(false);  // Chamada de função inexistente

        SorteioCartelas(ListaCartelas);

        inicializaLinha(vetorSorteio, 100, tam);
        PosicionaCartelas(ListaCartelas, vetorSorteio, jogadores);
        Sleep(1000);

        do {
            gotoxy(58, 23);
            cout << "Aperte a tecla espaço para sortear novo número";
            if (_kbhit()) {
                char tecla = getch();
                switch (tecla) {
                    case ' ':
                        sorteioNumero(ListaCartelas, vetorSorteio, jogadores);
                        procuraVencedor(ListaCartelas, vetorSorteio, winners);
                        for (int i = 0; i < SIZE; i++) {
                            if (winners[i])
                                winner = 0;
                        }
                }
            }
        } while (winner == -1);
        Sleep(1000);
        imprimeVencedores(winners, jogadores);
        ShowConsoleCursor(true);
        x = continuarJogando();
        if (!x) {
            return 0;
        }
        y = trocarNomes();
        if (y)
            inicializaJogadores(jogadores);
        winner = -1;
    } while (x);
    return 0;
}

void inicializaJogadores(string jogadores[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        cout << "Digite o nome do jogador da cartela " << i + 1 << ": ";
        cin >> jogadores[i];
    }
}

bool trocarNomes() {
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
    for (int i = 0; i < tam; i++) {
        vet[i] = valor;
    }
}

bool SIS(int vet[SIZE], int valor, int tam) {
    for (int k = 0; k < tam; k++) {
        if (valor == vet[k])
            return true;
    }
    return false;
}

void bubblesort(int vet[], int tam) {  // bubble sort
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
    inicializaLinha(vet);
    int p;
    for (int i = 0; i < SIZE; i++) {
        do {
            p = rand() % 15 + (1 + linha * 15);
        } while (SIS(vet, p, i));
        vet[i] = p;
    }
    bubblesort(vet);
}

void preencheCartela(int vet[SIZE][SIZE]) {
    int linha[SIZE];
    for (int i = 0; i < SIZE; i++) {
        preencheLinha(linha, i);
        for (int j = 0; j < SIZE; j++)
            vet[i][j] = linha[j];
    }
}

void SorteioCartelas(int Cartelas[SIZE][SIZE][SIZE]) {
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

void PosicionaCartelas(int Cartelas[SIZE][SIZE][SIZE], int vet[], string jogadores[SIZE]) {
    for (int indice = 0; indice < SIZE; indice++) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                gotoxy(48 * (indice % 2) + j * 8, 5 + i + indice / 2 * 8);
                int k = 0;
                while (vet[k] != 100) {
                    if (Cartelas[indice][i][j] == vet[k])
                        textcolor(3, 0);
                    k++;
                }
                cout << Cartelas[indice][i][j];
                textcolor(7, 0);
            }
        }
        gotoxy(8 + (indice % 2) * 48, 10 + 8 * (indice / 2));
        cout << "jogador " << indice + 1 << ": " << jogadores[indice];
    }
}

void imprimeSorteio(int vet[75]) {
    int i = 0;
    while (vet[i] != 100 && i < 75) {
        textcolor(2, 0);
        gotoxy(5 + 3 * (i % 25), 1 + (i / 25));
        cout << vet[i];
        i++;
    }
    textcolor(7, 0);
}

void sorteioNumero(int Cartelas[SIZE][SIZE][SIZE], int vetor[75], string jogadores[SIZE]) {
    int num;
    do {
        num = rand() % 75 + 1;
    } while (SIS(vetor, num, 75));
    vetor[74] = num;
    bubblesort(vetor, 75);
    gotoxy(35, 0);
    Sleep(10);
    clrscr();
    cout << "Número Sorteado: " << num;
    PosicionaCartelas(Cartelas, vetor, jogadores);
    imprimeSorteio(vetor);
}

int procuraVencedor(int Cartelas[SIZE][SIZE][SIZE], int vetor[], bool vencedores[]) {
    for (int i = 0; i < SIZE; i++)
        vencedores[i] = false;
    for (int ind = 0; ind < SIZE; ind++) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                int k = 0;
                while (vetor[k] != 100) {
                    k++;
                    if (!SIS(vetor, Cartelas[ind][i][j], 75)) {
                        k = 0;
                        i = 0;
                        j = 0;
                        ind++;
                        if (ind >= 5)
                            return -1;
                    }
                }
            }
        }
        vencedores[ind] = true;
    }
    return -1;
}

void imprimeVencedores(bool vencedores[], string jogadores[]) {
    int cont = 0;
    for (int i = 0; i < SIZE; i++) {
        if (vencedores[i]) {
            gotoxy(58, 23 + cont);
            cout << "Vencedor " << cont + 1 << ": " << jogadores[i];
            cont++;
        }
    }
}

bool continuarJogando() {
    Sleep(5000);
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
        }
    } while (p != 'Y' || p != 'y' || p != 'n' || p != 'N');
}