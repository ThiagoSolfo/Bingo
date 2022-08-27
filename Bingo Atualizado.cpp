/*
Define uma cartela ordenada do bingo.
Última Alteração em 25/08/2022 por Homero.
Faltante:
        - Menu de Interação do Usuário;
        - Loop com o jogo completo no main***;
        - Verificar caso para mais de 1 ganhador.
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

bool menu(int &escolher);

bool SIS(int vet[SIZE], int valor, int tam);

void inicializaLinha(int vet[], int valor = 0, int tam = SIZE);

void bubblesort(int vet[], int tam = SIZE);

void preencheLinha(int vet[SIZE], int linha);

void preencheCartela(int vet[SIZE][SIZE]);

void SorteioCartelas(int Cartelas[SIZE][SIZE][SIZE]);

void PosicionaCartelas(int Cartelas[SIZE][SIZE][SIZE], int vet[]);

void imprimeSorteio(int vet[75]);

void sorteioNumero(int Cartelas[SIZE][SIZE][SIZE], int vetor[75]);

int procuraVencedor(int Cartelas[SIZE][SIZE][SIZE], int vetor[]);

bool continuarJogando();

int main() {
    setlocale(LC_ALL, "portuguese");
    srand(time(NULL));

    int escolher;
    bool x;
    int tam = 75;
    int ListaCartelas[SIZE][SIZE][SIZE], vetorSorteio[tam];
    int winner = -1;
    do {
        while (!menu(escolher))
            cout << "Cartela inexistente\n\n";
        Sleep(2000);
        clrscr();

        SorteioCartelas(ListaCartelas);

        inicializaLinha(vetorSorteio, 100, tam);
        PosicionaCartelas(ListaCartelas, vetorSorteio);
        Sleep(1000);

        do {
            sorteioNumero(ListaCartelas, vetorSorteio);
            winner = procuraVencedor(ListaCartelas, vetorSorteio);
        } while (winner == -1);
        Sleep(2000);
        gotoxy(58, 23);
        cout << "Vencedor: Cartela " << winner << "!";
        x = continuarJogando();
        winner = -1;
    } while (x);
    return 0;
}

bool menu(int &escolher) {
    cout << "Escolha uma cartela:\n";

    cout << "Cartela 1\n"
         << "Cartela 2\n"
         << "Cartela 3\n"
         << "Cartela 4\n"
         << "Cartela 5\n\n";
    cin >> escolher;
    switch (escolher) {
        cout << "\n\n";
        case 1:
            cout << "Cartela 1\n";
            break;
        case 2:
            cout << "Cartela 2\n";
            break;
        case 3:
            cout << "cartela 3\n";
            break;
        case 4:
            cout << "cartela 4\n";
            break;
        case 5:
            cout << "cartela 5\n";
            break;
    }
    if (escolher > 0 && escolher <= 5) {
        return true;
    } else {
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

void PosicionaCartelas(int Cartelas[SIZE][SIZE][SIZE], int vet[]) {
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
        gotoxy(13 + (indice % 2) * 48, 10 + 8 * (indice / 2));
        cout << "Cartela " << indice + 1;
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

void sorteioNumero(int Cartelas[SIZE][SIZE][SIZE], int vetor[75]) {
    int num;
    do {
        num = rand() % 75 + 1;
    } while (SIS(vetor, num, 75));
    vetor[74] = num;
    bubblesort(vetor, 75);
    gotoxy(35, 0);
    cout << "Número Sorteado: " << num;
    Sleep(10);
    clrscr();
    PosicionaCartelas(Cartelas, vetor);
    imprimeSorteio(vetor);
}

int procuraVencedor(int Cartelas[SIZE][SIZE][SIZE], int vetor[]) {
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
        if (ind >= 5)
            return -1;
        else
            return ind + 1;
    }
}

bool continuarJogando() {
    char p;
    do {
        cout << "Deseja continuar jogando? (Y or N): ";
        cin >> p;
        switch (p) {
            case 'Y':
                return true;
            case 'N':
                return false;
        }
    } while (p != 'Y' || p != 'N');
}