#include <iostream>
#include <stdexcept>

using namespace std;

// Definição da estrutura de dado armazenada na pilha
struct Dado {
    string nome;
    char tipo;
    int valor;
};

// Função para imprimir as informações de um dado
void imprimir_dado(const Dado& umDado) {
    cout << "Nome: " << umDado.nome << " ";
    cout << "Tipo: " << umDado.tipo << " ";
    cout << "Valor: " << umDado.valor << " ";
    cout << endl;
}

// Classe para o nó da pilha
class Noh {
    friend class Pilha;
    private:
        Dado mDado; // Dado armazenado no nó
        Noh* mProx; // Ponteiro para o próximo nó
    public:
        // Construtor do nó
        Noh(Dado v) {
            mDado = v;
            mProx = NULL;
        }        
};

// Classe para a pilha
class Pilha {
    public:
        // Construtor da pilha
        Pilha();
        // Destrutor da pilha
        ~Pilha();
        // Desempilha o elemento do topo da pilha
        Dado Desempilhar(); // retorna o mPtTopo da Pilha.
        // Empilha um dado na pilha
        void Empilhar(const Dado& d);
        // Limpa todos os elementos da pilha
        void LimparTudo();
        // Ordena os elementos da pilha
        void ordenar();
        // Retorna o dado no topo da pilha
        Dado espiar();
        // Informa se a pilha está vazia
        inline bool Vazia();

    private:
        Noh* mTopo; // Ponteiro para o topo da pilha
        int mTamanho; // Tamanho atual da pilha
};

// Construtor da pilha
Pilha::Pilha() {
    mTopo = NULL;
    mTamanho = 0;
}

// Destrutor da pilha
Pilha::~Pilha() {
    LimparTudo();
}

// Desempilha o elemento do topo da pilha e retorna o valor
Dado Pilha::Desempilhar() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    
    else{
        Dado valor = mTopo -> mDado;
        Noh* aux = mTopo;
        mTopo = mTopo -> mProx;
        delete aux;
        mTamanho--;
        return valor;
    }
}

// Empilha um dado na pilha
void Pilha::Empilhar(const Dado& d) {
    Noh* novo = new Noh(d);
    novo -> mProx = mTopo;
    mTopo = novo;
    mTamanho++;
}

// Limpa todos os elementos da pilha
void Pilha::LimparTudo() {
    while (mTamanho>0){
        Desempilhar();
    }
}

// Informa se a pilha está vazia
bool Pilha::Vazia() {
    return (mTamanho == 0);
}

// Ordena os elementos da pilha
void Pilha::ordenar(){
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    else{
        // Cria uma pilha auxiliar
        Pilha* pilhaAux = new Pilha();
        Dado dadoAux, dadoPrincipal;
        
        // Transfere os elementos da pilha original para a pilha auxiliar
        while (!Vazia()){
            pilhaAux->Empilhar(Desempilhar());
            
            // Verifica se a pilha auxiliar e a pilha original não estão vazias
            if(!pilhaAux->Vazia() and !Vazia()){
                dadoAux = pilhaAux->espiar();
                dadoPrincipal = espiar();
                
                // Compara os nomes dos dados na pilha auxiliar e na pilha original
                // Se o nome na pilha auxiliar for menor, realiza a troca
                if (dadoAux.nome < dadoPrincipal.nome){
                    dadoAux = pilhaAux->Desempilhar();
                    pilhaAux->Empilhar(Desempilhar());
                    Empilhar(dadoAux);
                    
                    // Transfere os elementos restantes da pilha auxiliar para a pilha original
                    while (!pilhaAux->Vazia()){
                        Empilhar(pilhaAux->Desempilhar());
                    }                    
                }
                
            }
        }
        
        // Atualiza o topo e o tamanho da pilha original com os valores da pilha auxiliar
        mTopo = pilhaAux->mTopo;
        mTamanho = pilhaAux->mTamanho;
    }    
}

// Retorna o dado no topo da pilha sem remover
Dado Pilha::espiar(){
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    else{
        return mTopo->mDado;
    }
}

// Função principal
int main() {
    Pilha pilha;
    Dado info;
    char comando;
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.tipo >> info.valor;
                    pilha.Empilhar(info);
                    break;
                case 'r': // remover
                    imprimir_dado(pilha.Desempilhar());
                    break;
                case 'l': // limpar tudo
                    pilha.LimparTudo();
                    break;
                case 'e': // espiar                
                    imprimir_dado(pilha.espiar());
                    break;
                case 'o': // ordenar                
                    pilha.ordenar();
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
    while (not pilha.Vazia()) {
        imprimir_dado(pilha.Desempilhar());
    }
    cout << endl;
    return 0;
}
