/* 
Versão alternativa que atende melhor o que o Dredd pede

Implemente uma tabela hash, utilizando tratamento de colisão por encadeamento de nós, para implementar um inventário de itens em um jogo digital. A estrutura deve possibilitar, pelo menos, as seguintes ações: inserção e remoção de itens, localizar um item na estrutura hash. A remoção e busca devem escrever mensagem de erro na saída ("Erro: hash vazia!"), quando a hash estiver vazia. Na remoção ou na busca, caso a hash contenha elementos mas o item da busca não se encontra na tabela, o usuário deve ser informado da seguinte forma: ("Elemento inexistente!") . Os itens do inventários possuem os seguintes atributos: nome (uma string sem espaços), tipo (um único caracter) e valor (um inteiro).

Para essa atividade você pode utilizar as seguintes opções de código fonte base: código fornecido 1 ou código fornecido2.

No início da execução, o programa lê o tamanho da tabela hash.

Entradas:

O programa deve aceitar os seguintes comandos:

i: seguido de uma string, um caracter e um inteiro: para inserir um item no inventário. Caso exista colisão, a inserção na lista deve ser no ínicio.
r seguido de um string: para retirar um item do inventário
l seguido de um string: para localizar o determinado item no inventário
p: imprimir toda a tabela hash
f: para finalizar a execução do programa
*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int UMPRIMO = 7;

// Um noh guarda um par (chave / valor) 
class noh {
    friend class lista;
    friend class tabelaHash;
    private:
        string chave;
        char tipo;
        int valor;
        noh* proximo;
        noh(const string& c = "", const char& t = 'a', const int& v=0, noh* prox = NULL):
            chave(c), tipo(t), valor(v), proximo(prox) { }
};

// Uma lista guarda todos os Nos cuja chave foi mapeada na mesma posição.
class lista {
    friend class tabelaHash;
    private:
        noh* primeiro; // primeiro nó da lista
        unsigned short numElementos; // quantidade de valores na lista
    public:
        lista(); // Construtor
        ~lista(); // Destrutor
        unsigned short tamanho() { return numElementos; } // Consulta do Tamanho
        // Adiciona um novo par (chave, valor) na lista
        // Insere no início, para não precisar de ponteiro para o fim
        void insere(const string& c, const char& t,const int& v);
        // Remove o noh com dada chave da lista.
        // Se a chave não existe, retorna informação.
        bool remove(const string& c);
        // Busca um elemento na lista, retorna falso se não encontrado
        // o valor buscado é retornado por passagem por referência
        // na variável valorBuscado
        bool busca(const string& c, char& tipoBuscado, int& valorBuscado);
        // Verifica se já tem algum dado na lista com 
        // uma dada chave
        bool verificaOcorrencia(const string& c);
        // Imprime o conteúdo da lista, para fins de depuração
        void imprime() {
            noh* atual = primeiro;
            while (atual != NULL) {
                    cout << "[" << atual->chave << "/"
                         << atual->valor << "]";
                    atual = atual->proximo;
            }
        }
};

lista::lista() {
    primeiro = NULL;
    numElementos = 0;
}

lista::~lista(){
    while (numElementos > 0) {
        noh* aux = primeiro;
        primeiro = primeiro->proximo;
        delete aux;
        numElementos--;
    }
}

void lista::insere(const string& c, const char& t, const int& v) {
    noh* novo = new noh(c, t, v, primeiro);
    novo->proximo = primeiro;
    primeiro = novo;
}

bool lista::remove(const string& c) {
    noh* anterior = NULL;
    noh* aux = primeiro;
    while ((aux != NULL) and (aux->chave != c)) {
        anterior = aux;
        aux = aux->proximo;
    }
    if (aux == NULL) {
        return false;
    } 
    else {
        if (anterior == NULL) {
            primeiro = aux->proximo;
        } 
        else {
            anterior->proximo = aux->proximo;
        }
        delete aux;
        numElementos--;
        return true;
    }    
}

bool lista::busca(const string& c, char& tipoBuscado, int& valorBuscado) {
    noh* aux = primeiro;
    while ((aux != NULL) and (aux->chave != c)) {
        aux = aux->proximo;
    }
    if (aux == NULL) {
        return false;
    } 
    else {
        tipoBuscado = aux->tipo;
        valorBuscado = aux->valor;
        return true;
    }
}

bool lista::verificaOcorrencia(const string& c) {
    noh* aux = primeiro;
    while ((aux != NULL) and (aux->chave != c)) {
        aux = aux->proximo;
    }
    if (aux == NULL) {
        return false;
    } 
    else {
        return true;
    }
}  

class tabelaHash {
    private:
        // vetor de ponteiros para lista
        lista* tabela;
        // quantidade de posições na tabela hash
        unsigned numPosicoes;
        // quantidade de elementos já inseridos na tabela
        unsigned tamanho;
        // converte uma chave (string) num endereço da tabela 
        // - versão simples
        unsigned funcaoHash(const string& s) {
            return funcaoHash(s, numPosicoes);
        } 
        // converte uma chave (string) num endereço da tabela 
        // - versão para redimensionamento
        unsigned funcaoHash(const string& s, int cap) {
            unsigned pos = 0;
            for (unsigned int i = 0; i < s.size(); ++i)
                pos = (UMPRIMO * pos + s[i]) % cap;
            return pos;
        }
    public:
        // construtor padrão
        tabelaHash(unsigned cap = 100);
        ~tabelaHash();
        // Insere um nó com dada chave e valor.
        bool insere(const string& c, char& t, const int& v);
        // Retorna um valor associado a uma dada chave.
        // Se a chave não existe, retorna "NÃO ENCONTRADO!".
        bool valor(const string& c, char& tipoBuscado, int& valorRetorno);
        // Retira do hash um nó com dada chave.
        bool remove(const string& c);
        // Retorna se a tabela está vazia
        bool vazia() { return tamanho == 0; }
        // Imprime o conteúdo interno do hash (para fins de depuração)
        void imprime() {
            for (unsigned i = 0; i < numPosicoes; i++) {
                cout << i << ": ";
                tabela[i].imprime();
                cout << endl;
            }
        }
};

tabelaHash::tabelaHash(unsigned cap) {
    numPosicoes = cap;
    tabela = new lista[numPosicoes];
    tamanho = 0;
}

tabelaHash::~tabelaHash() {
    delete[] tabela;
}

bool tabelaHash::insere(const string& c, char& t, const int& v) {
    unsigned posicao = funcaoHash(c);
    if (tabela[posicao].verificaOcorrencia(c)) {
        return false;
    } 
    tabela[posicao].insere(c, t, v);
    tamanho++;
    cout << "chave '" << c << "' inserida na posição " << posicao << endl;
    return true;
}

bool tabelaHash::valor(const string& c, char& tipoBuscado, int& valorRetorno) {
    unsigned posicao = funcaoHash(c);
    return tabela[posicao].busca(c, tipoBuscado, valorRetorno);
}

bool tabelaHash::remove(const string& c) {
    unsigned posicao = funcaoHash(c);
    if (tabela[posicao].remove(c)) {
        tamanho--;
        return true;
    }
    return false;
}

int main() {
    int tamanhoTH;
    cin >> tamanhoTH;
    tabelaHash tabela(tamanhoTH);
    char comando;
    string chave;
    char tipo = 'a';
    int valor = -1;    
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> chave >> tipo>> valor;
                    if (not tabela.insere(chave, tipo, valor))
                        cout << "Erro na inserção: chave já existente!" << endl;
                    break;
                case 'r': // remover
                    cin >> chave;
                    if (not tabela.remove(chave))
                        cout << "Erro na remoção: chave não encontrada!" << endl;
                    break;
                case 'l': // remover
                    cin >> chave;
                    if (not tabela.valor(chave,tipo,valor))
                        cout << "Erro na busca: chave não encontrada!" << endl;
                    else
                        cout << "Tipo: " << tipo << " Valor: " << valor << endl;
                    break;
                case 'p': // mostrar estrutura
                    tabela.imprime();
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
    tabela.imprime();
    cout << endl;
    return 0;
}