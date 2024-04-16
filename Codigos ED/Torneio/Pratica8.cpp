#include <iostream>
#include <cstring>
#include <algorithm> 
using namespace std;

const int INVALIDO = -1;

class torneio{
private:
    int *heap; // Array para armazenar os participantes do torneio
    int tamanho; // Tamanho atual da heap
    int capacidade; // Capacidade total da heap
    int inicioDados; // Índice onde começam os dados reais na heap
    bool competirMaior; // Variável para alternar entre competir pelo maior ou menor valor
    inline int pai(int filho); // Função auxiliar para encontrar o pai de um nó na heap
    inline int esquerda(int getPai); // Função auxiliar para encontrar o filho esquerdo de um nó na heap
    inline int direita(int getPai); // Função auxiliar para encontrar o filho direito de um nó na heap
    void arruma(); // Método para organizar a heap
    void compete(int i, bool competirMaior); // Método para realizar a competição entre os elementos

public:
    torneio(int vet[], int tam); // Construtor da classe
    ~torneio(); // Destrutor da classe
    int viceCampeao(); // Método para encontrar o vice-campeão do torneio
};

// Construtor da classe
torneio::torneio(int vet[], int tam){
    // Inicialização das variáveis
    int numPais = 1;
    while (numPais < tam){
        numPais *= 2;
    }
    capacidade = numPais - 1 + tam;
    inicioDados = capacidade - tam;
    heap = new int [capacidade];
    memcpy(&heap[inicioDados], vet, sizeof(int) * tam);
    competirMaior = true;
    arruma(); // Organiza a heap após a inicialização
}

// Destrutor da classe
torneio::~torneio(){
    delete[] heap;
}

// Retorna a posição do pai de um determinado elemento na heap
int torneio::pai(int i){  
    return (i - 1) / 2;
}

// Retorna a posição do filho esquerdo de um determinado nó na heap
int torneio::esquerda(int i){ 
    return 2 * i + 1;
}

// Retorna a posição do filho direito de um determinado nó na heap
int torneio::direita(int i){ 
    return 2 * i + 2;
}

// Organiza a heap
void torneio::arruma(){
    // Variáveis para controlar a competição
    int tamanhoChave = (inicioDados + 1) / 2;
    int aux = tamanhoChave;

    // Percorre a heap para realizar as competições
    for (int i = inicioDados - 1; i >= 0; i--){        
        // Realiza a competição para o nó atual
        compete(i, competirMaior);

        // Atualiza as variáveis para alternar entre competir pelo maior ou menor valor
        aux--;
        if (aux == 0){
            competirMaior = !competirMaior;
            tamanhoChave /= 2;
            aux = tamanhoChave;
        }
    }
}

// Realiza a competição entre os elementos na heap
void torneio::compete(int i, bool competirMaior){ 
    int esq = esquerda(i);
    int dir = direita(i);

    // Verifica se a competição é para encontrar o maior valor
    if (competirMaior){
        // Se o filho esquerdo existe
        if (esq <= capacidade - 1){
            int maior;

            // Verifica se o filho direito também existe e qual deles é maior
            if (dir <= capacidade - 1 && heap[dir] > heap[esq])
                maior = dir;
            else
                maior = esq;
            
            // Atualiza o valor do nó atual com o valor do filho maior
            heap[i] = heap[maior];
        }
        else
            heap[i] = INVALIDO;    
    }
    else{ // Competição para encontrar o menor valor
        // Se o filho esquerdo existe
        if (esq <= capacidade - 1){
            int menor;

            // Verifica se o filho direito também existe e qual deles é menor
            if (dir <= capacidade - 1 && heap[dir] != INVALIDO && heap[dir] < heap[esq])
                menor = dir;
            else
                menor = esq;
            
            // Atualiza o valor do nó atual com o valor do filho menor
            heap[i] = heap[menor];
        }
        else
            heap[i] = INVALIDO;
    }        
}

// Método para encontrar o vice-campeão do torneio
int torneio::viceCampeao(){
    if (heap[1] == heap[0]){
        return heap[2];
    }
    else{
        return heap[1];
    }
}

// Função principal
int main(){
    int tam;
    cin >> tam;

    // Lê os valores dos participantes
    int vet[tam];
    for(int i = 0; i < tam; i++){
        cin >> vet[i];
    }

    // Cria um objeto torneio com os participantes e encontra o vice-campeão
    torneio participantes(vet, tam);
    cout << participantes.viceCampeao() << endl;

    return 0;
}
