#include <iostream>
#include <utility> // para usar swap
#include <stdexcept> // para usar exceção com runtime_error
#include <cstring> // para usar memcpy

using namespace std;

// Definição da estrutura de dados para armazenar informações de uma tarefa
struct dado {
    string nomeTarefa;
    char tipoTarefa;
    int energiaGasta;
    int tempoEstimado;
    int prioridade;
};

// Sobrecarga do operador > para comparar dados
bool operator>(dado d1, dado d2) {
    return ((d1.prioridade > d2.prioridade) or ((d1.prioridade == d2.prioridade) and (d1.energiaGasta < d2.energiaGasta)));   
}

// Sobrecarga do operador < para comparar dados
bool operator<(dado d1, dado d2) {
    return ((d1.prioridade < d2.prioridade) or ((d1.prioridade == d2.prioridade) and (d1.energiaGasta > d2.energiaGasta))); 
}

// Sobrecarga do operador de saída para imprimir informações de uma tarefa
ostream& operator<<(ostream& output,const dado& d) {
    output << "[" << d.nomeTarefa << "/" << d.tipoTarefa << "/" << d.energiaGasta << "/" << d.tempoEstimado << "/" << d.prioridade <<"]"; 
    return output;
}

// Classe Heap
class Heap {
private:
    dado* heap; // Array para armazenar os dados
    int capacidade; // Capacidade máxima da heap
    int tamanho; // Tamanho atual da heap
    inline int pai(int i); // Método para retornar o índice do pai de um nó
    inline int esquerdo(int i); // Método para retornar o índice do filho esquerdo de um nó
    inline int direito(int i); // Método para retornar o índice do filho direito de um nó
    void corrigeDescendo(int i); // Método para corrigir a heap descendo a partir do índice fornecido
    void corrigeSubindo(int i); // Método para corrigir a heap subindo a partir do índice fornecido
    void arruma(); // Método para arrumar a heap
public:
    Heap(int cap); // Construtor da classe
    ~Heap(); // Destrutor da classe
    void imprime(); // Método para imprimir a heap
    dado retiraRaiz(); // Método para retirar a raiz da heap
    void insere(dado d); // Método para inserir um dado na heap
    int getTamanho(); // Método para retornar o tamanho atual da heap
    void altPrioridade(string nomeTarefa, int novaPrioridade); // Método para alterar a prioridade de uma tarefa
};

// Implementação dos métodos da classe Heap

Heap::Heap(int cap) {
    capacidade = cap;
    tamanho = 0;
    heap = new dado[cap];
}

Heap::~Heap() {
    delete[] heap;
}

int Heap::pai(int i) {
    return (i-1)/2;
}

int Heap::esquerdo(int i) {
    return 2*i+1;
}

int Heap::direito(int i) {
    return 2*i+2;
}

void Heap::corrigeDescendo(int i) {
    int menor = i;
    int esquerda = esquerdo(i);
    int direita = direito(i);
    if (esquerda < tamanho and heap[esquerda] < heap[menor]) {
        menor = esquerda;
    }
    if (direita < tamanho and heap[direita] < heap[menor]) {
        menor = direita;
    }
    if (menor != i) {
        swap(heap[i], heap[menor]);
        corrigeDescendo(menor);
    }    
}

void Heap::corrigeSubindo(int i) {
    int mPai = pai(i);
    if (heap[i] < heap[mPai]) {
        swap(heap[mPai], heap[i]);
        corrigeSubindo(mPai);
    }
}

void Heap::imprime() {
    if (tamanho > 0) {
        for (int i = 0; i < tamanho; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Heap vazia!\n";
    }
}

dado Heap::retiraRaiz() {
    dado aux = heap[0];
    swap (heap[0], heap[tamanho-1]);
    tamanho--;
    corrigeDescendo(0);
    return aux;        
}

void Heap::insere(dado d) {
    if (tamanho < capacidade) {
        heap[tamanho] = d;
        corrigeSubindo(tamanho);
        tamanho++;
    } else {
        cout << "Erro ao inserir\n";
    }    
}

int Heap::getTamanho() {
    return tamanho;
}

void Heap::arruma() {
    for (int i = tamanho/2 - 1; i >= 0; i--) {
        corrigeDescendo(i);
    }
}

// Pode ter algum trecho perigoso de código aqui, mas não achei nada que pudesse ser melhorado
void Heap::altPrioridade(string nomeTarefa, int novaPrioridade) {
    Heap aux(tamanho);
    dado auxDado;
    while(tamanho > 0) {
        auxDado = retiraRaiz();
        if (auxDado.nomeTarefa == nomeTarefa) {
            auxDado.prioridade = novaPrioridade;
        }
        aux.insere(auxDado);
    }
    memcpy(heap, aux.heap, sizeof(dado) * aux.tamanho);
    tamanho = aux.tamanho;
}

// Função principal
int main() {
    int capacidade;
    dado info;
    char comando;
    string nomeTarefa;

    // Leitura da capacidade da heap
    cin >> capacidade;
    Heap meuHeap(capacidade);

    do {
        try {
            // Leitura do comando
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    // Leitura das informações da tarefa
                    cin >> info.nomeTarefa >> info.tipoTarefa >> info.energiaGasta >> info.tempoEstimado >> info.prioridade;
                    // Inserção da tarefa na heap
                    meuHeap.insere(info);
                    break;
                case 'r': // remover
                    // Remoção da raiz da heap e impressão do nome da tarefa removida
                    if (meuHeap.getTamanho() > 0) {
                        cout << meuHeap.retiraRaiz().nomeTarefa << endl;
                    } else {
                        cout << "Erro ao retirar raiz\n";
                    }
                    break;
                case 'p': // limpar tudo
                    // Impressão de todas as tarefas na heap
                    meuHeap.imprime();
                    break;
                case 'a': // alterar prioridade
                    int novaPrioridade;
                    // Leitura do nome da tarefa e da nova prioridade
                    cin >> nomeTarefa >> novaPrioridade;
                    // Alteração da prioridade da tarefa
                    meuHeap.altPrioridade(nomeTarefa, novaPrioridade);
                    break;
                case 'f': // finalizar
                    // Finaliza a execução do programa
                    break;
                default:
                    // Comando inválido
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            // Tratamento de exceção
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    cout << endl;
    return 0;
}
