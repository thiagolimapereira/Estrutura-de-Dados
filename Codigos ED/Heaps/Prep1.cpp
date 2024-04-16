#include <iostream>
#include <utility> // para usar swap
#include <stdexcept> // para usar exceção com runtime_error

using namespace std;

struct dado {
    string nomeTarefa;
    char tipoTarefa;
    int energiaGasta;
    int tempoEstimado;
    int prioridade;
};

bool operator>(dado d1, dado d2) {
    return d1.energiaGasta > d2.energiaGasta;
}

bool operator<(dado d1, dado d2) {
    return d1.energiaGasta < d2.energiaGasta;
}

ostream& operator<<(ostream& output,const dado& d) {
    output << "[" << d.nomeTarefa << "/" << d.tipoTarefa << "/" << d.energiaGasta << "/" << d.tempoEstimado << "/" << d.prioridade <<"]"; 
    return output;
}

class MaxHeap {
private:
    dado* heap;
    int capacidade;
    int tamanho;
    inline int pai(int i);
    inline int esquerdo(int i);
    inline int direito(int i); 
    void corrigeDescendo(int i); 
    void corrigeSubindo(int i);
public:
    MaxHeap(int cap);
    ~MaxHeap();
    void imprime();
    dado retiraRaiz();
    void insere(dado d);
    int getTamanho();
};

MaxHeap::MaxHeap(int cap) {
    capacidade=cap;
    tamanho=0;
    heap = new dado[cap];
}

MaxHeap::~MaxHeap() {
   delete[] heap;
}

int MaxHeap::pai(int i) {
    return (i-1)/2;
}
    
int MaxHeap::esquerdo(int i) {
    return 2*i+1;
}
    
int MaxHeap::direito(int i) {
    return 2*i+2;
}
    
void MaxHeap::corrigeDescendo(int i) {
    int maior = i;
    int esquerda = esquerdo(i);
    int direita = direito(i);
    if (esquerda<tamanho and heap[esquerda]>heap[maior]){
        maior = esquerda;
    }
    if (direita<tamanho and heap[direita]>heap[maior]){
        maior = direita;
    }
    if (maior != i){
        swap(heap[i], heap[maior]);
        corrigeDescendo(maior);
    }    
}

void MaxHeap::corrigeSubindo(int i) {
    int mPai = pai(i);
    if (heap[i]>heap[mPai]){
        swap(heap[mPai], heap[i]);
        corrigeSubindo(mPai);
    }
}
        
void MaxHeap::imprime() {
    if (tamanho > 0){
        for (int i=0; i<tamanho; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
    else{
        cout<<"Heap vazia!\n";
    }
}

dado MaxHeap::retiraRaiz() {
    dado aux = heap[0];
    swap (heap[0], heap[tamanho-1]);
    tamanho--;
    corrigeDescendo(0);
    return aux;        
}


void MaxHeap::insere(dado d){
    if (tamanho<capacidade){
        heap[tamanho] = d;
        corrigeSubindo(tamanho);
        tamanho++;
    }
    else{
        cout<<"Erro ao inserir\n";
    }    
}

int MaxHeap::getTamanho(){
    return tamanho;
}


int main() {
    int capacidade;
    dado info;
    char comando;

    cin >> capacidade;
    MaxHeap meuHeap(capacidade);

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nomeTarefa >> info.tipoTarefa >> info.energiaGasta >> info.tempoEstimado >> info.prioridade;
                    meuHeap.insere(info);
                    break;
                case 'r': // remover
                    if (meuHeap.getTamanho()>0){
                        cout << meuHeap.retiraRaiz().nomeTarefa << endl;
                    }
                    else {
                        cout << "Erro ao retirar raiz\n";
                    }
                    break;
                case 'p': // limpar tudo
                    meuHeap.imprime();
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    cout << endl;
    return 0;
}