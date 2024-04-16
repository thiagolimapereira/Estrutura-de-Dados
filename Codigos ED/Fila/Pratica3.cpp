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
    cout << "Tempo: " << umDado.tempo << " ";
    cout << endl;
}

class Noh {
    friend class Fila;
    private:
        Dado mDado; 
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
        // Informa se a Fila está Vazia.
        inline bool Vazia();
        // Realiza as tarefas de acordo com o tempo
        void realizarTarefas(int tempo);
        // Retorna o elemento que está na frente da Fila, sem desenfileirar.    
        inline Dado Primeiro(); 
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

// Retira e retorna o elemento que estiver na frente da Fila.
// Escreve uma mensagem de erro se não for possível desenfileirar.
Dado Fila::Desenfileirar() {
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");
    else{
        Noh* aux = mPtPrimeiro;
        Dado valor = mPtPrimeiro->mDado;
        mPtPrimeiro = mPtPrimeiro->mProx;
        delete aux;
        tamanho--;
        return valor;
    }
}

// Insere um elemento na Fila.
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

// Apagar todos os dados da Fila.
void Fila::LimparTudo() {
    while (!Vazia()){
        Desenfileirar();
    }
}

// Informa se a Fila está Vazia.
bool Fila::Vazia() {
    return tamanho == 0;
}

// Retorna o elemento que está na frente da Fila, sem desenfileirar.
Dado Fila::Primeiro() {
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");
    return mPtPrimeiro->mDado;
}

// Realiza as tarefas de acordo com o menor tempo até o tempo limite
void Fila::realizarTarefas(int tempo){
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");
    int soma = 0;
    int menorTempo;
    int tamanhoAux = tamanho;
    Dado aux;
    while (soma < tempo and !Vazia()){
        menorTempo = Primeiro().tempo;
        // Encontrar o menor tempo
        for (int i = 0; i < tamanho; i++){
            aux = Desenfileirar();
            Enfileirar(aux);
            if (aux.tempo < menorTempo){
                menorTempo = aux.tempo;
            }
        }
        soma += menorTempo;
        // Verifica se é possivel realizar a tarefa
        if (soma < tempo){
            int i = 0;
            bool removeu = false;
            // Procura a tarefa para retirar
            while (i<tamanhoAux){
                aux = Desenfileirar();
                if (!removeu and aux.tempo == menorTempo){
                    imprimir_dado(aux);
                    removeu = true;
                }
                else{
                    Enfileirar(aux);
                }
                i++;
            } 
            tamanhoAux = tamanho;
        }
    }    
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
                    imprimir_dado(fila.Primeiro());
                    break;
                case 't': // realizar tarefas
                    int tempo; 
                    cin >> tempo;
                    fila.realizarTarefas(tempo);
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
    while (not fila.Vazia()) {
        imprimir_dado(fila.Desenfileirar());
    }
    cout << endl;
    return 0;
}