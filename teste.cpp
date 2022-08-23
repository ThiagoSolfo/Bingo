/*

Define uma cartela ordenada do bingo.
Última Alteração em 23/08/2022 por Homero.

Faltante: 
        - Criar 5 cartelas, cada uma com seu índice (Matriz com 3 dimensões);
        - Criar a Mecânica de Bingo em si;
        - Realizar a associação do número de saída com cada cartela;
        - Verificação de ganhador do Bingo;
        - Menu de Interação do Usuário;
        - Interface com as cartelas atualizando a medida que os números vão saindo;
        - Loop com o jogo completo no main.

*/

#include <iostream>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define SIZE 5

void inicializaLinha(int vet[SIZE]){
    for (int i = 0; i<SIZE; i++)
        vet[i] = 0;  
}

bool SIS(int vet[SIZE], int valor, int tam){
    for (int k = 0;k<tam;k++){
        if(valor == vet[k])
            return true;
        
    }
    return false;
}

void sort(int vet[]) {              //bubble sort
    int i, j, cond, temp;
    cond = 1;
    for (i=SIZE-1; (i >= 1) && (cond == 1); i--) {
        cond = 0;
        for (j=0; j < i ;j++) {
            if (vet[j+1] < vet[j]) {
                temp = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = temp;
                cond = 1;
            }
        }
    }
}

void preencheLinha(int vet[SIZE],int linha){
    inicializaLinha(vet);
    int p;
    for (int i = 0;i<SIZE;i++){
        do{
            p = rand()%15+(1+linha*15);
        } while(SIS(vet,p,i));
        vet[i] = p;
    } 
    sort(vet);   
}

void preencheCartela(int vet[SIZE][SIZE]){
    int linha[SIZE];
    for (int i = 0;i<SIZE;i++){
        preencheLinha(linha,i);
        for (int j = 0;j<SIZE;j++)
            vet[i][j] = linha[j];
    }    
 }

 void imprimeCartela(int vet[SIZE][SIZE]){
    for (int i = 0;i<SIZE;i++){
        cout << endl;
        for (int j = 0;j<SIZE;j++){
            cout << vet[i][j] << " ";
        }
    }
 }

int main(){
    setlocale(LC_ALL,"portuguese");
    srand(time(NULL));
    int Cartela1[SIZE][SIZE];
    preencheCartela(Cartela1);
    imprimeCartela(Cartela1);
    return 0;
}
