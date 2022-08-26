/*
Define uma cartela ordenada do bingo.
�ltima Altera��o em 23/08/2022 por Homero.

Integrantes:
  - Homero C�sar de Campos
  - Kevin Robert Elias
  - Thiago Marinho Solfo
  - Vinicius Jos�

Faltante:
  - Criar 5 cartelas, cada uma com seu �ndice (Matriz com 3 dimens�es);
  - Criar a Mec�nica de Bingo em si;
  - Realizar a associa��o do n�mero de sa�da com cada cartela;
  - Verifica��o de ganhador do Bingo;
  - Menu de intera��o do usu�rio;
  - Interface com as cartelas atualizando a medida que os n�meros v�o saindo;
  - Loop com o jogo completo no main.

Como usar texto colorido:
  - Use a fun��o textcolor(numero, numero) escolhendo a numera��o da cor no arquivo codefun.h (o primeiro � o texto e o segundo o background - n�o esque�a de resetar depois porque isso se aplica a todo o console!!)
  Ex: textcolor(4,0) - texto vermelho e fundo preto
*/

#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "codefun.h"

using namespace std;

#define SIZE 5

// Substitu�do por vet[SIZE] = {}
//
// void inicializaLinha(int vet[SIZE]) {
//     for (int i = 0; i < SIZE; i++)
//         vet[i] = 0;
// }

bool SIS(int vet[SIZE], int valor, int tam) {
    for (int k = 0; k < tam; k++) {
        if (valor == vet[k])
            return true;
    }
    return false;
}

void sort(int vet[]) {  // bubble sort
    int i, j, cond, temp;
    cond = 1;
    for (i = SIZE - 1; (i >= 1) && (cond == 1); i--) {
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
    // inicializaLinha(vet);
    int p;
    for (int i = 0; i < SIZE; i++) {
        do {
            p = rand() % 15 + (1 + linha * 15);
        } while (SIS(vet, p, i));
        vet[i] = p;
    }
    sort(vet);
}

void preencheCartela(int vet[SIZE][SIZE]) {
    int linha[SIZE];
    for (int i = 0; i < SIZE; i++) {
        preencheLinha(linha, i);
        for (int j = 0; j < SIZE; j++)
            vet[i][j] = linha[j];
    }
}

void imprimeCartela(int vet[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        cout << endl;
        for (int j = 0; j < SIZE; j++) {
            cout << vet[i][j] << "\t";
        }
    }
}

int main() {
    int vet[SIZE] = {};
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    int Cartela1[SIZE][SIZE];
    preencheCartela(Cartela1);
    imprimeCartela(Cartela1);

    // Testes com textos coloridos
    textcolor(4, 0);
    cout << "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum sed odio euismod, sollicitudin mauris a, maximus nisi.";
    textcolor(11, 0);
    cout << "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum sed odio euismod, sollicitudin mauris a, maximus nisi.";
    textcolor(9, 0);
    cout << "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum sed odio euismod, sollicitudin mauris a, maximus nisi.";

    return 0;
}
