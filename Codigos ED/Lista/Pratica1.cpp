/*
Implemente uma função que realize a contabilidade dos elementos de uma lista simplesmente encadeada. Para esta atividade você não poderá utilizar a variável tamanho, ou qualquer outra que contabilize o número de elementos na lista, na sua estrutura. Ou seja, a verificação do tamanho deverá ser feita contando os elementos da lista. Caso a lista não possua elementos imprima 0.

Você pode (e deve!) utilizar o código que você desenvolveu na atividade "Lista Simplesmente Encadeada - Equipes de Maratona" como base.

Com essa finalidade, você deverá adicionar mais um comando, como segue:

t : imprime a quantidade de elementos existentes na lista.
Saídas:

Todas as saídas de comandos já estão implementadas na função principal código entregue, somente falta implementar a chamada para a calcular o tamanho da lista. Ao terminar a execução do programa, todos os itens da listas são escritos.
*/

#include <iostream>
#include <cstdlib>

using namespace std;

// Estrutura que representa uma equipe
struct equipe {
    string nomeEquipe;
    string lider;
    string linguagem;
    int qtdMembros;
};

// Função auxiliar para imprimir uma equipe
void imprimeEquipe(equipe elenco) {
    cout << "(" << elenco.nomeEquipe << ", " << elenco.lider << ", " << elenco.linguagem << ", " << elenco.qtdMembros << ")\n";
}

// Definição da classe nó da lista encadeada
class noh {
    friend class lista;
private:
    equipe elenco; // Dados armazenados no nó
    noh* proximo;  // Ponteiro para o próximo nó na lista
public:
    noh(equipe d); // Construtor que inicializa um nó com uma equipe
};

// Construtor da classe nó
noh::noh(equipe d) {
    elenco = d;
    proximo = NULL;
}

// Definição da classe lista encadeada
class lista {
private:
    noh* primeiro; // Ponteiro para o primeiro nó da lista
    noh* ultimo;   // Ponteiro para o último nó da lista

    void removeTodos(); // Remove todos os elementos da lista

public:
    lista();                  // Construtor padrão da lista
    lista(const lista& umaLista); // Construtor de cópia
    ~lista();                 // Destrutor da lista

    lista& operator=(const lista& umaLista); // Sobrecarga do operador de atribuição

    void insereNoFim(equipe elenco);        // Insere no final da lista
    void insereNoInicio(equipe elenco);     // Insere no início da lista
    void insereNaPosicao(int posicao, equipe elenco); // Insere em uma posição específica

    int procura(string valor); // Procura uma equipe pelo nome

    void imprime();         // Imprime todos os elementos da lista
    bool vazia();           // Verifica se a lista está vazia

    equipe removeNoFim();    // Remove o último elemento da lista
    equipe removeNoInicio(); // Remove o primeiro elemento da lista

    int verificarTamanho(); // contabiliza e retorna o tamanho da lista
};

// Construtor da lista (inicializa uma lista vazia)
lista::lista() {
    primeiro = NULL;
    ultimo = NULL;
}

// Construtor de cópia
lista::lista(const lista& umaLista) {
    primeiro = NULL;
    ultimo = NULL;
    noh* aux = umaLista.primeiro;

    // Copia os elementos da lista umaLista para a nova lista
    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;
    }
}

// Destrutor da lista (chama a função auxiliar para remover todos os elementos)
lista::~lista() {
    removeTodos();
}

// Remove todos os elementos da lista
void lista::removeTodos() {
    while (!vazia()) {
        removeNoFim();
    }
}

// Sobrecarga do operador de atribuição
lista& lista::operator=(const lista& umaLista) {
    // Limpa a lista atual
    removeTodos();

    // Copia os elementos da lista umaLista para a lista atual
    noh* aux = umaLista.primeiro;
    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;
    }

    return *this;
}

// Insere no final da lista
void lista::insereNoFim(equipe elenco) {
    if (vazia()) {
        // Se a lista estiver vazia, insere como único elemento
        primeiro = new noh(elenco);
        ultimo = primeiro;
    } else {
        // Caso contrário, insere após o último elemento
        noh* novo = new noh(elenco);
        ultimo->proximo = novo;
        ultimo = novo;
    }
}

// Insere no início da lista
void lista::insereNoInicio(equipe elenco) {
    if (vazia()) {
        // Se a lista estiver vazia, insere como único elemento
        primeiro = new noh(elenco);
        ultimo = primeiro;
    } else {
        // Caso contrário, insere antes do primeiro elemento
        noh* novo = new noh(elenco);
        novo->proximo = primeiro;
        primeiro = novo;
    }
}

// Insere em uma posição específica da lista
void lista::insereNaPosicao(int posicao, equipe elenco) {
    if (posicao < 0 || posicao > verificarTamanho()) {
        cout << "Posição Inexistente!\n";
        return;
    }

    if (posicao == 0) {
        insereNoInicio(elenco);
    } else if (posicao == verificarTamanho()) {
        insereNoFim(elenco);
    } else {
        // Insere na posição intermediária
        noh* novo = new noh(elenco);
        noh* aux = primeiro;
        for (int i = 0; i < posicao - 1; i++) {
            aux = aux->proximo;
        }
        novo->proximo = aux->proximo;
        aux->proximo = novo;
    }
}

// Procura um elemento na lista e retorna a posição
int lista::procura(string valor) {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    }
    int posicao = 0;
    noh* aux = primeiro;
    while (aux != NULL) {
        if (aux->elenco.nomeEquipe == valor) {
            return posicao;
        }
        aux = aux->proximo;
        posicao++;
    }
    return -1;
}

// Imprime todos os elementos da lista
void lista::imprime() {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    }

    noh* aux = primeiro;
    while (aux != NULL) {
        imprimeEquipe(aux->elenco);
        aux = aux->proximo;
    }
}

// Verifica se a lista está vazia
bool lista::vazia() {
    return (primeiro == NULL);
}

// Remove o último elemento da lista
equipe lista::removeNoFim() {
    if (vazia()) {
        throw runtime_error("Remoção em lista vazia!");
    }

    equipe elenco = ultimo->elenco;
    if (primeiro == ultimo) {
        // Lista com apenas um elemento
        delete primeiro;
        primeiro = NULL;
        ultimo = NULL;
    } else {
        // Lista com mais de um elemento
        noh* aux = primeiro;
        while (aux->proximo != ultimo) {
            aux = aux->proximo;
        }
        delete ultimo;
        ultimo = aux;
        ultimo->proximo = NULL;
    }
    return elenco;
}

// Remove o primeiro elemento da lista
equipe lista::removeNoInicio() {
    if (vazia()) {
        throw runtime_error("Remoção em lista vazia!");
    }

    noh* aux = primeiro;
    equipe elenco = aux->elenco;
    primeiro = primeiro->proximo;
    delete aux;
    if (vazia()) {
        ultimo = NULL;
    }
    return elenco;
}

int lista::verificarTamanho(){
    noh* aux = primeiro;
    int tamanho = 0;

    while (aux != NULL){
        tamanho++;
        aux = aux->proximo;
    }

    return tamanho;   
}

// Função principal (main)
int main() {
    lista minhaLista; // Criação de uma lista vazia
    equipe info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando; // Leitura do comando
            switch (comando) {
                case 'i': // inserir no início
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h': // inserir no fim
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoFim(info);
                    break;             
                case 'm': // inserir em posição específica
                    cin >> posicao;
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNaPosicao(posicao, info);
                    break;             
                case 's': // procurar
                    cin >> nomeEquipe;
                    posicao = minhaLista.procura(nomeEquipe);
                    if(posicao == -1)
                        cout << "Nao encontrado"<< endl;
                    else
                        cout << posicao << endl;
                    break;                    
                case 'r': // remover do início
                    minhaLista.removeNoInicio();
                    break;
                case 'a': // remover do fim
                    minhaLista.removeNoFim();
                    break;                                   
                case 'p': // imprimir lista
                    minhaLista.imprime();
                    break;
                case 't': // imprimir tamanho
                    cout<<minhaLista.verificarTamanho()<<endl;
                    break;
                case 'f': // finalizar execução
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // Loop até o comando 'f' (finalizar)

    return 0;
}