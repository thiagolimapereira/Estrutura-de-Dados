#include <iostream>
#include <stdexcept>

using namespace std;

struct Dado {
    string nome;
    string premio;
    char tipo;
    int tempo;
};

// Imprime as informações de um dado qualquer
void imprimir_dado(const Dado& umDado) {
    cout << "Nome: " << umDado.nome << " ";
    cout << "Premio: " << umDado.premio << " ";
    cout << "Tipo: " << umDado.tipo << " ";
    cout << "tempo: " << umDado.tempo;
    cout << endl;
}

class Noh {
    friend class Fila;
    private:
        Dado mDado; // poderia ser outro tipo de variável
        Noh* mProx;
    public:
        Noh(Dado v) {
            mDado = v;
            mProx = NULL;
        }        
};

class Fila {
    public:
        // Constrói Fila vazia.
        Fila();
        // Destrutor que desaloca memória.
        ~Fila();
        // Retira e retorna o elemento que estiver na frente da Fila.
        // Escreve uma mensagem de erro se não for possível desenfileirar.
        Dado Desenfileirar(); 
        // Insere um elemento na Fila.
        void Enfileirar(const Dado& d);
        // Apagar todos os dados da Fila.
        void LimparTudo();
        // Retorna o elemento que está na frente da Fila, sem desenfileirar.
        inline void Primeiro();
        // Informa se a Fila está Vazia.
        inline bool Vazia();

        int imprimirTempoTipo (char tipo);

        int getTamanho(){
            return tamanho;
        }
    private:
        Noh* mPtPrimeiro;
        Noh* mPtrUltimo;
        int tamanho;
};

Fila::Fila() { 
    mPtPrimeiro = mPtrUltimo = NULL;
    tamanho=0;  
}

Fila::~Fila() {
    LimparTudo();
}

Dado Fila::Desenfileirar() {
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");
    else{
        Noh* aux = mPtPrimeiro;
        Dado valor = mPtPrimeiro->mDado;
        mPtPrimeiro = mPtPrimeiro->mProx;
        delete aux;
        tamanho--;
        if (tamanho==0) mPtrUltimo=NULL;
        return valor;
    }
}

void Fila::Enfileirar(const Dado& d) {
   Noh* novo = new Noh(d);
   if (mPtPrimeiro == NULL){
    mPtPrimeiro = novo;
   }
   else{
    mPtrUltimo->mProx = novo;
   }
   mPtrUltimo = novo;
   tamanho++;      
}

void Fila::LimparTudo() {
    while (!Vazia()){
        Desenfileirar();
    }
}

void Fila::Primeiro() {
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");
    imprimir_dado(mPtPrimeiro->mDado);
}

bool Fila::Vazia() {
    return tamanho == 0;
}

int Fila::imprimirTempoTipo (char tipo){
    int soma = 0;
    Fila aux;
    int tamanhoAux = tamanho;
    for (int i = 0; i < tamanhoAux; i++){
        Dado dado = Desenfileirar();
        if (dado.tipo == tipo){
            soma += dado.tempo;
            Enfileirar(dado);
        }
        else{
            aux.Enfileirar(dado);
        }
    }

    tamanhoAux = aux.getTamanho();
    for (int i = 0; i < tamanhoAux; i++){
        Enfileirar(aux.Desenfileirar());
    }

    return soma;    
}


int main() {
    Fila fila;
    Dado info;
    char comando;
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.premio >> info.tipo >> info.tempo;
                    fila.Enfileirar(info);
                    break;
                case 'r': // remover
                    imprimir_dado(fila.Desenfileirar());
                    break;
                case 'l': // limpar tudo
                    fila.LimparTudo();
                    break;
                case 'e': // espiar                
                    fila.Primeiro();
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                case 'a': // espiar  
                    char tipoAtividade;
                    cin>>tipoAtividade;              
                    cout<<fila.imprimirTempoTipo(tipoAtividade)<<endl;
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    while (not fila.Vazia()) {
        imprimir_dado(fila.Desenfileirar());
    }
    cout << endl;
    return 0;
}