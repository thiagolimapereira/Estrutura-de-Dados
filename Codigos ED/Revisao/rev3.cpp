#include <iostream>
#include <fstream>
using namespace std;

int main () {
    int vetor[100] = {0}, contador = 0;

    ifstream arqEntrada ("entrada.txt");

    while (arqEntrada >> vetor[contador]) {
        contador++;
    }

    arqEntrada.close();

    ofstream arqSaida ("saida.txt");

    for (int i = contador-1; i >= 0; i--)
    {
        arqSaida << vetor[i] << " ";
    }

    arqSaida.close();
    
    return 0;
}