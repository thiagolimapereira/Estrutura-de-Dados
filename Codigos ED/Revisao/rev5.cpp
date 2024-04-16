#include <iostream>
#include <fstream>
using namespace std;

float media (float x, float y);

int main () {
    string nomeArquivo;
    cin >> nomeArquivo;

    ifstream arq (nomeArquivo);

    int tamanho;
    arq >> tamanho;

    float* vetor = new float[tamanho];

    for (int i = 0; i < tamanho; i++)
    {
        arq >> vetor[i];
    }   

    arq.close();

    if (tamanho%2 != 0)
    {
        tamanho--;
        cout << vetor[tamanho] << " ";
    }

    while (tamanho > 0)
    {
        cout << media(vetor[tamanho - 1], vetor[tamanho - 2]) << " ";

        tamanho -= 2;
    }
    
    delete[] vetor;

    return 0;
}

float media (float x, float y){
    return (x + y)/2; 
}