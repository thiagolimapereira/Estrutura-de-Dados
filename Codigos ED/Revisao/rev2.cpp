#include <iostream>
using namespace std;

int multiplicaMatriz (int i, int j, int matrizA[][5], int matrizB[][2]);

int main () {
    int matrizA[4][5], matrizB[5][2], matrizC[4][2];

    for (int i=0; i<4; i++){
        for (int j=0; j<5; j++){
            cin >> matrizA[i][j];
        }
    }

    for (int i=0; i<5; i++){
        for (int j=0; j<2; j++){
            cin >> matrizB[i][j];
        }
    }

    for (int i=0; i<4; i++){
        for (int j=0; j<2; j++){
            matrizC[i][j] = multiplicaMatriz(i, j, matrizA, matrizB) ;
        }
    }

    for (int i=0; i<4; i++){
        for (int j=0; j<2; j++){
            cout << matrizC[i][j] << " ";
        }
        
        cout << endl;
    }

    return 0;
}

int multiplicaMatriz (int i, int j, int matrizA[][5], int matrizB[][2]){
    int resultado = 0;

    for (int k=0; k<5; k++){
        resultado += matrizA[i][k] * matrizB[k][j];
    }

    return resultado;
}