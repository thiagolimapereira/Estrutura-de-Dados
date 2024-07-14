/* 
Utilizando como base o código que você desenvolveu na atividade "Hash com encadeamento - Inventário de itens de jogo", faça as alterações necessárias 
para que a tabela hash seja redimensionada em 3 posições caso a taxa de ocupação seja igual ou maior que 70%
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
        // verifica se a lista está vazia
        bool vazia() {return numElementos == 0;} 
        void removeNoInicio(string& c, char& t, int& v);
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
    numElementos++;
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

void lista::removeNoInicio(string& c, char& t, int& v) {
    noh* aux = primeiro;
    c = aux->chave;
    t = aux->tipo;
    v = aux->valor;
    primeiro = primeiro->proximo;
    delete aux;
    numElementos--;
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
        // redimensiona a tabela hash
        void redimensiona();
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
    if (tamanho/numPosicoes >= 0.7){
        cout << "\nÉ necessário redimensionar de " << numPosicoes << " para " << numPosicoes+3 << endl << endl;
        redimensiona();
    }
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

void tabelaHash::redimensiona() {
    numPosicoes += 3; // Aumenta o número de posições na tabela em 3
    lista* aux = new lista[numPosicoes]; // Cria uma nova tabela hash com o novo tamanho
    string c; // Variável para armazenar a chave
    char t; // Variável para armazenar o tipo
    int v; // Variável para armazenar o valor
    for(int i = 0; i<numPosicoes-3; i++){ // Percorre a tabela hash antiga
        while (!tabela[i].vazia()){ // Enquanto a lista na posição i não estiver vazia
            tabela[i].removeNoInicio(c, t, v); // Remove o primeiro elemento da lista e armazena em c, t e v
            unsigned posicao = funcaoHash(c, numPosicoes); // Calcula a nova posição na tabela hash
            aux[posicao].insere(c, t, v); // Insere o elemento na nova tabela hash
        }        
    }
    delete[] tabela; // Libera a memória ocupada pela tabela hash antiga
    tabela = aux; // Atribui a nova tabela hash à variável tabela
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