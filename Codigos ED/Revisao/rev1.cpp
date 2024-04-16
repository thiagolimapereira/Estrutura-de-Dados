#include <iostream>
using namespace std;

int main () {
    int tamanhoA, tamanhoB, tamanhoC, posicaoC;
    bool igual = false;

    cin >> tamanhoA;

    tamanhoC = tamanhoA;
    posicaoC = tamanhoA;
    
    int *vetorA = new int[tamanhoA];

    for (int i = 0; i < tamanhoA; i++){
        cin >> vetorA[i];
    }

    cin >> tamanhoB;
    
     int *vetorB = new int[tamanhoB];

    for (int i = 0; i < tamanhoB; i++){
        cin >> vetorB[i];

        for (int j = 0; j < tamanhoA; j++){
            if (vetorB[i] == vetorA[j])
                igual = true;
        }

        if (!igual)
            tamanhoC++;
        
        igual = false;
    }

     int *vetorC = new int[tamanhoC];

    for (int i = 0; i < tamanhoA; i++)
        vetorC[i] = vetorA[i];

    for (int i = 0; i < tamanhoB; i++){
        for (int j = 0; j < tamanhoA; j++){
            if (vetorB[i] == vetorA[j])
                igual = true;
        }

        if (!igual){
            vetorC[posicaoC] = vetorB[i];
            posicaoC++;
        }
        
        igual = false;
    } 

     for (int i = 0; i < tamanhoC; i++){
        cout << vetorC[i] << " ";
     }

    delete[] vetorA;
    delete[] vetorB;
    delete[] vetorC;

    return 0;
}
