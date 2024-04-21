/* 
Implemente uma tabela hash, utilizando tratamento de colisão por endereçamento aberto, para implementar uma lista de processos para uma repartição pública, utilizando como base o código fornecido. A estrutura deve possibilitar, pelo menos, as seguintes ações: inserção e remoção de um determinado item, localização de um processo na estrutura hash. A remoção ou busca deve escrever mensagem de erro na saída ("Erro: hash vazia!"), quando a hash estiver vazia. Na remoção ou na busca, caso a hash contenha elementos mas o item da busca não se encontra na tabela, o usuário deve ser informado da seguinte forma: ("Elemento inexistente!"). O enfileiramento também deve gerar mensagem de erro ("Erro: hash cheia!"), quanto todas as posições do vetor estiverem ocupadas. Os itens da lista de processos possuem os seguintes atributos: assunto (uma string sem espaços), nome do interessado(uma string sem espaços), tipo (um único caracter) e numero do processo (um inteiro). Além disso, essa repartição tem capacidade para trabalhar com apenas seis processos por vez.

Entradas:

O programa deve aceitar os seguintes comandos:

i seguido de uma string, um caracter e um inteiro: para inserir um item na lista de processos
r seguido de um inteiro: para retirar um item da lista de processos
l seguido de um inteiro: para localizar um item na hash
f: para finalizar a execução do programa
Saídas:

Todas as saídas de comandos já estão implementadas na função principal desse código exemplo fornecido. Ao terminar a execução do programa, todos os itens da hash são escritos.
*/ 

#include <iostream>
#include <exception>

using namespace std;

struct dado {
    string assunto; 
    string nomeInteressado;
    char tipo;
    int numeroProcesso;
};

bool operator==(const dado& d1, const dado& d2) {
    return (d1.nomeInteressado == d2.nomeInteressado and d1.nomeInteressado == d2.nomeInteressado);
}

bool operator!=(const dado& d1, const dado& d2) {
    return (d1.nomeInteressado != d2.nomeInteressado or d1.nomeInteressado != d2.nomeInteressado);
}


const int UMPRIMO = 13;
const dado INVALIDO = {"","",'1',-1};
const dado REMOVIDO = {"","",'2',-2};
const int POSINVALIDA = -1;

class hashEA {
    private:
        // Retorna a posição em que uma chave deveria ficar na estrutura
        // Usa função de hash para calcular a posição
        unsigned posicao(const string& chave);
        // Retorna a posicao em que uma chave está armazenada na estrutura
        // (retorna -1 caso chave não esteja presente)
        int buscarChave(const string& chave);
        // Vetor de dados
        dado* vetDados;
        unsigned capacidade;
        unsigned tamanho;
    public:
        hashEA(unsigned cap = 50); // usa valor default se não informado
        ~hashEA();
        // Mostra todos as posições de armazenamento da hash
        void imprimir();
        // Insere uma cópia do valor. Não permite inserção de chave repetida
        void inserir(const string& assunto, const string& interessado, const char& tipo, const int& valor);
        // Remove um item da hash associado com a chave dada
        void remover(const string& chave);
        // Retorna o valor associado a uma chave
        int consultar(const string& chave);
};


hashEA::hashEA(unsigned cap) {
    capacidade = cap;
    vetDados = new dado[cap]; 
    for (unsigned i = 0; i < cap; i++) 
        vetDados[i] = INVALIDO;
    tamanho = 0;
}

hashEA::~hashEA() {
    delete[] vetDados;
}

unsigned hashEA::posicao(const string& chave) {
    // Retorna a posição de armazenamento de uma chave, sem colisão 
    unsigned pos = 1;
    for (unsigned i = 0; i < chave.size(); i++)
        pos = UMPRIMO * pos + chave[i];
    return pos % capacidade;    
}

int hashEA::buscarChave(const string& chave) {
    // Retorna a posicao em que uma chave está armazenada na estrutura
    // Retorna POSINVALIDA quando chave não está na tabela hash 
    unsigned pos = posicao(chave);
    unsigned posFinal = pos;
    dado umDado;

    do {
        umDado = vetDados[pos];
        if (umDado == INVALIDO) return POSINVALIDA; 
        if (umDado.nomeInteressado == chave) return pos;
        pos = (pos + 1) % capacidade;
    } while (pos != posFinal); 

    // se chegou aqui é porque percorreu todo o vetor e não encontrou
    return POSINVALIDA;
}

void hashEA::inserir(const string& assunto, const string& interessado, const char& tipo, const int& valor) {
    // Insere uma cópia do valor. Não permite inserção de chave repetida.
    if (interessado.empty()) 
        throw invalid_argument("Chave inválida.");
    if (tamanho == capacidade) 
        throw runtime_error("Tabela hash cheia.");

    if (buscarChave(interessado) != POSINVALIDA)   
        throw runtime_error("Inserção de chave que já existe.");

    unsigned pos = posicao(interessado);
//    cout << "posição original: " << pos << endl;
    while ((vetDados[pos] != INVALIDO) and (vetDados[pos] != REMOVIDO))
        pos = (pos + 1) % capacidade;
//    cout << "posição final: " << pos << endl;
    vetDados[pos].assunto = assunto;
    vetDados[pos].nomeInteressado = interessado;
    vetDados[pos].tipo = tipo;
    vetDados[pos].numeroProcesso = valor;
    tamanho++;
}

void hashEA::imprimir() {
    // Mostra todos as posições de armazenamento da hash.
    for (unsigned i = 0; i < capacidade; ++i) {
        cout << '[' << i << ":";
        if (vetDados[i] != INVALIDO) {
            if (vetDados[i] == REMOVIDO)
                cout << "REMOVIDO";
            else
                cout << vetDados[i].nomeInteressado << '/' << vetDados[i].numeroProcesso;
        }
        cout << "] ";
    }
}

void hashEA::remover(const string& chave) {
    if (tamanho == 0) 
        throw runtime_error("Impossível remover de hash vazia.");
    
    int pos = buscarChave(chave);
    if (pos == POSINVALIDA) 
        throw runtime_error("Chave não encontrada para remoção.");

    vetDados[pos] = REMOVIDO;
    tamanho--;
}

int hashEA::consultar(const std::string& chave) {
    // Retorna o valor associado a uma chave.
    int pos = buscarChave(chave);
    if (pos == POSINVALIDA) 
        throw runtime_error("Chave não encontrada para consulta.");

    return vetDados[pos].numeroProcesso;
}

int main() {
    hashEA tabela(6);
    char operacao;

    string assunto, interessado;
    char tipo;
    int valor;
    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // inserir
                    cin >> assunto>> interessado >> tipo >> valor;
                    tabela.inserir(assunto, interessado, tipo, valor);
                    break;
                case 'r': // remover
                    cin >> interessado;
                    tabela.remover(interessado);
                    break;
                case 'l': // consultar
                    cin >> interessado;
                    valor = tabela.consultar(interessado);
                    cout << valor << endl;
                    break;
                case 'p': // debug (mostrar estrutura)
                    tabela.imprimir();
                    cout << endl;
                    break;
                case 'f': // finalizar
                    // vai testar depois
                    break;
                default:
                    cerr << "operação inválida" << endl;
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    } while (operacao != 'f'); 
    tabela.imprimir();
    return 0;
}