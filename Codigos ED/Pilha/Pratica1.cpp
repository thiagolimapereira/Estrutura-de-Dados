#include <iostream>
#include <stdexcept>

using namespace std;

struct Dado {
    string nome;
    char tipo;
    int valor;
};

// Imprime as informações de um dado qualquer
void imprimir_dado(const Dado& umDado) {
    cout << "Nome: " << umDado.nome << " ";
    cout << "Tipo: " << umDado.tipo << " ";
    cout << "Valor: " << umDado.valor << " ";
    cout << endl;
}

class Noh {
    friend class Pilha;
    private:
        Dado mDado; // poderia ser outro tipo de variável
        Noh* mProx;
    public:
        Noh(Dado v) {
            mDado = v;
            mProx = NULL;
        }        
};

class Pilha {
    public:
        // Constrói pilha vazia.
        Pilha();
        // Destrutor que desaloca memória.
        ~Pilha();
        // Retira e retorna o valor que estiver no mPtTopo da pilha.
        // Escreve uma mensagem de erro se não for possível desempilhar.
        Dado Desempilhar(); // retorna o mPtTopo da Pilha.
        // Insere um valor na pilha.
        void Empilhar(const Dado& d);
        // Apagar todos os dados da pilha.
        void LimparTudo();
        // Imprime o valor que está no mPtTopo sem desempilhar.
        inline void Topo();
        // Informa se a pilha está Vazia.
        inline bool Vazia();

        Dado getDado(){
            return mTopo -> mDado;
        }

    private:
        Noh* mTopo;
        int mTamanho;
};

Pilha::Pilha() {
    mTopo = NULL;
    mTamanho = 0;
}

Pilha::~Pilha() {
    LimparTudo();
}

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

void Pilha::Empilhar(const Dado& d) {
    Noh* novo = new Noh(d);
    novo -> mProx = mTopo;
    mTopo = novo;
    mTamanho++;
   
}

void Pilha::LimparTudo() {
    while (mTamanho>0){
        Desempilhar();
    }
}

void Pilha::Topo() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    else{
        imprimir_dado(mTopo -> mDado);
    }
}

bool Pilha::Vazia() {
    return (mTamanho == 0);
}

void removerAbaixo(int x, Pilha& pilha){
    Pilha pilhaAux;
    while (not pilha.Vazia()){
        if (pilha.getDado().valor < x){
            imprimir_dado(pilha.Desempilhar());
        }
        else {
            pilhaAux.Empilhar(pilha.getDado());
            pilha.Desempilhar();
        }
    }

    while (not pilhaAux.Vazia()){
        pilha.Empilhar(pilhaAux.getDado());
        pilhaAux.Desempilhar();
    }
    
}


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
                    pilha.Topo();
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                case 'x': // remover abaixo de determinado valor              
                    int x;
                    cin >> x;
                    removerAbaixo(x, pilha);
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