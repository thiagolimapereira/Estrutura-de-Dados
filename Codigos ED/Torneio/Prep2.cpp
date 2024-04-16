#include <iostream>
#include <cstring>
#include <algorithm> 
using namespace std;

const int INVALIDO = -1;

class torneio{
private:
	int *heap;
	int tamanho;
	int capacidade;
    int inicioDados;
	inline int pai(int filho);
	inline int esquerda(int getPai);
	inline int direita(int getPai);
	void arruma();
	void compete(int i);
    

public:
	torneio(int vet[], int tam);
	~torneio();
    int campeao();
};

//Construtor da classe
torneio::torneio(int vet[], int tam){
    int numPais = 1;
    while (numPais<tam){
        numPais*=2;
    }
    capacidade = numPais-1 + tam;
    inicioDados = capacidade - tam;
    heap = new int [capacidade];
    memcpy(&heap[inicioDados], vet, sizeof(int)*tam);
    arruma();
}

// Destrutor da classe
torneio::~torneio(){
    delete[] heap;
}

// Retorno a posição do nó pai de um determinado elemento
int torneio::pai(int i){  
    return (i-1)/2;
}

// Retorna o filho à esquerda de um determinado nó
int torneio::esquerda(int i){ 
    return 2*i+1;
}

// Retorna o filho à direita do nó pai
int torneio::direita(int i){ 
    return 2*i+2;
}

// Faz a competição por cada posição vencedora no vetor e imprime o vencedor
void torneio::arruma(){
    for (int i = inicioDados-1; i>=0; i--){
        compete(i);
    }
}

// Faz a competição entre os elementos
void torneio::compete(int i){ 
    int esq = esquerda(i);
    int dir = direita(i);
    if (esq<=capacidade-1){
        int maior;
        if (dir<=capacidade-1 and heap[dir]>heap[esq])
            maior = dir;
        else
            maior = esq;
        
        heap[i] = heap[maior];
    }
    else
        heap[i] = INVALIDO;    
}

int torneio::campeao(){
    return heap[0];
}

int main(){
    int tam;
    cin >> tam;

    int vet[tam];
    for(int i = 0; i < tam; i++){
        cin >> vet[i];
    }

    torneio participantes(vet, tam);

    cout<<participantes.campeao()<<endl;

    return 0;
}