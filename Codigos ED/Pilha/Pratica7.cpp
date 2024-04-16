#include <iostream>

using namespace std;

const int PILHAVAZIA = -1;
const int TAMANHOPILHA = 6;

struct Dado {
    string nome;
    char tipo;
    int valor;
};

void imprimir_dado(const Dado& umDado){
    cout<< "Nome: " << umDado.nome << " ";
    cout<< "Tipo: " << umDado.tipo << " ";
    cout<< "Valor: " << umDado.valor << endl;
}

class Pilha {
    private:
        Dado* mPilha;
        int posTopo;
    public:
        Pilha(); // Construtor da classe Pilha
        ~Pilha(); // Destrutor da classe Pilha
        Dado Desempilhar(); // Desempilha um elemento da pilha
        void Empilhar(const Dado& d); // Empilha um elemento na pilha
        void LimparTudo(); // Limpa todos os elementos da pilha
        inline void Topo(); // Imprime o elemento do topo da pilha
        inline bool Vazia(); // Verifica se a pilha está vazia
        inline bool Cheia(); // Verifica se a pilha está cheia
};

Pilha::Pilha(){
    mPilha = new Dado[6]; // Aloca espaço para a pilha
    posTopo = -1; // Inicializa a posição do topo da pilha
}

Pilha::~Pilha() {
    delete[] mPilha; // Libera a memória alocada para a pilha
}

Dado Pilha::Desempilhar() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!"); // Verifica se a pilha está vazia
    
    else{
        Dado d = mPilha[posTopo]; // Armazena o elemento do topo da pilha
        posTopo--; // Atualiza a posição do topo da pilha
        return d; // Retorna o elemento desempilhado
    }
}

void Pilha::Empilhar(const Dado& d) {
    if (this->Cheia()){ // Verifica se a pilha está cheia
        Pilha aux; // Cria uma pilha auxiliar
        
        // Desempilha todos os elementos da pilha original e empilha na pilha auxiliar
        while(not this->Vazia()){
            aux.Empilhar(this->Desempilhar());
        }
        
        imprimir_dado(aux.Desempilhar()); // Imprime o elemento desempilhado da pilha auxiliar
        
        // Empilha todos os elementos da pilha auxiliar de volta na pilha original
        while(not aux.Vazia()){
            this->Empilhar(aux.Desempilhar());
        }
    }

    posTopo++; // Atualiza a posição do topo da pilha
    mPilha[posTopo] = d; // Empilha o elemento na pilha
}

void Pilha::LimparTudo() {
    while (not Vazia()){ // Enquanto a pilha não estiver vazia
        Desempilhar(); // Desempilha um elemento
    }
}

void Pilha::Topo() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!"); // Verifica se a pilha está vazia
    
    else{
        imprimir_dado(mPilha[posTopo]); // Imprime o elemento do topo da pilha
    }     
}

bool Pilha::Vazia() {
    return posTopo == -1; // Retorna true se a pilha estiver vazia, caso contrário, retorna false
}

bool Pilha::Cheia() {
    return posTopo == 5; // Retorna true se a pilha estiver cheia, caso contrário, retorna false
}


int main() {
    Pilha pilha; // Cria um objeto da classe Pilha
    Dado info; // Cria um objeto da struct Dado
    char comando; // Variável para armazenar o comando do usuário
    
    do {
        try {
            cin >> comando; // Lê o comando do usuário
            switch (comando) {
                case 'i': // Comando para empilhar um elemento
                    cin >> info.nome >> info.tipo >> info.valor; // Lê as informações do elemento
                    pilha.Empilhar(info); // Empilha o elemento na pilha
                    break;
                case 'r': // Comando para desempilhar um elemento
                    imprimir_dado(pilha.Desempilhar()); // Imprime o elemento desempilhado
                    break;
                case 'l': // Comando para limpar a pilha
                    pilha.LimparTudo(); // Limpa todos os elementos da pilha
                    break;
                case 'e': // Comando para imprimir o elemento do topo da pilha
                    if(!pilha.Vazia())               
                        pilha.Topo(); // Imprime o elemento do topo da pilha
                    else
                        cout << " Pilha vazia!"<< endl; // Mensagem de pilha vazia
                    break;
                case 'f': // Comando para finalizar o programa
                    break;
                default:
                    cerr << "comando inválido\n"; // Mensagem de comando inválido
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl; // Imprime a mensagem de erro
        }
    } while (comando != 'f'); // Repete o loop até o comando 'f' ser digitado
    
    while (not pilha.Vazia()) { // Enquanto a pilha não estiver vazia
        imprimir_dado(pilha.Desempilhar()); // Desempilha e imprime um elemento
    }
    
    cout << endl;
    return 0;
}