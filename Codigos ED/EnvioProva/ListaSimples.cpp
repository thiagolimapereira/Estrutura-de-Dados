/*
Implemente uma função que realize a remoção de um elemento no fim da lista. Para esta atividade você não poderá utilizar um ponteiro para o último elemento. Caso a lista não possua elementos imprima Lista vazia!.

Você pode (e deve!) utilizar o código que você desenvolveu na atividade "Lista Simplesmente Encadeada - Equipes de Maratona" como base.
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
    noh* ultimo; // Ponteiro para o último nó da lista
    int tamanho;   // Tamanho atual da lista

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
    void imprimeReverso();  // Imprime a lista de forma reversa

    bool vazia();           // Verifica se a lista está vazia
    int tamanhoSemV();      // Retorna o tamanho da lista sem o uso de uma variável para guardar o tamanho

    equipe removeNoFim();    // Remove o último elemento da lista
    equipe removeNoInicio(); // Remove o primeiro elemento da lista
    void removeEspecifico(string nome); // Remove um elemento específico da lista
};

// Construtor da lista (inicializa uma lista vazia)
lista::lista() {
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

// Construtor de cópia
lista::lista(const lista& umaLista) {
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
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

// ATENÇÃO!!! NECESSÁRIO ADAPTAR - Insere no final da lista sem usar a vantagem do ponteiro para o último elemento
// se for usar o ponteiro para o último elemento, o novo nó deve ser criado fora do if/else, não precisa do aux e do while,
// somente igualar o próximo do último para o novo nó e o último para o novo nó. Se não for usar o ponteiro para o último,
// apagar o último do if e do else. 
void lista::insereNoFim(equipe elenco) {
    if (vazia()) {
        // Se a lista estiver vazia, insere como único elemento
        primeiro = new noh(elenco);
        ultimo = primeiro;
    } else {
        // Caso contrário, insere após o último elemento
        noh* novo = new noh(elenco);
        noh* aux = primeiro;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        aux->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

// ATENÇÃO!!! NECESSÁRIO ADAPTAR - Insere no início da lista sem levar em conta o ponteiro para o último elemento
// se for usar o ponteiro para o último elemento, o novo nó deve ser criado fora do if/else, se não, apagar o último do if
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
    tamanho++;
}

// Insere em uma posição específica da lista
void lista::insereNaPosicao(int posicao, equipe elenco) {
    if (posicao < 0 || posicao > tamanho) {
       throw runtime_error("Posição Inexistente!");
    }

    if (posicao == 0) {
        insereNoInicio(elenco);
    } else if (posicao == tamanho) {
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
        tamanho++;
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

// ATENÇÃO!!! (remover se tiver variável tamanho)
// Retorna o tamanho da lista sem o uso de uma variável para guardar o tamanho
int lista::tamanhoSemV()
{
    if (vazia())
        return 0;

    noh *aux = primeiro;

    int tam = 0;

    while (aux != nullptr)
    {
        aux = aux->proximo;
        tam++;
    }
    return tam;
}

// ATENÇÃO!!! NECESSÁRIO ADAPTAR - Remove o último elemento da lista sem usar o ponteiro para o último elemento
// se for usar o ponteiro para o último elemento, só precisa do aux e do while, não precisa do anterior, só percorrer
// o aux até o próximo ser igual ao ultimo, deletar o último e igualar o ultimo ao aux. se não for usar o ponteiro
// para o último, apagar o ultimo do if e do else.
equipe lista::removeNoFim() {
    if (vazia()) {
        throw runtime_error("Remoção em lista vazia!");
    }
    equipe elenco;
    if (tamanho == 1) {
        elenco = primeiro->elenco;
        // Lista com apenas um elemento
        delete primeiro;
        primeiro = NULL;
        ultimo = NULL;
    }
    else{
        noh* aux = primeiro->proximo;
        noh* anterior = primeiro;
        while (aux->proximo != NULL) {
            anterior = aux;
            aux = aux->proximo;
        }
        elenco = aux->elenco;
        anterior->proximo = NULL;
        delete aux;
        ultimo = anterior;
    }
    tamanho--;
    return elenco;
}

// ATENÇÃO!!! (caso não for usar o ponteiro para o último elemento, remover o ultimo if)
// Remove o primeiro elemento da lista
equipe lista::removeNoInicio() {
    if (vazia()) {
        throw runtime_error("Remoção em lista vazia!");
    }

    noh* aux = primeiro;
    equipe elenco = aux->elenco;
    primeiro = primeiro->proximo;
    delete aux;
    tamanho--;
    return elenco;

    if (vazia()) {
        ultimo = NULL;
    }
}

void lista::removeEspecifico(string nome){
    int posicao = procura(nome);
    if (posicao != -1){
        if (posicao == 0) {
            removeNoInicio();
        } else if (posicao == tamanho - 1) {
            removeNoFim();
        } else {
            // remove na posição intermediária
            noh* anterior = primeiro;
            for (int i = 0; i < posicao-1; i++) {
                anterior = anterior->proximo;
            }
            noh* aux = anterior->proximo;
            anterior->proximo = aux->proximo;
            delete aux;
            tamanho--;
        }
    }
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
                case 's': // procurar por nome
                    cin >> nomeEquipe;
                    if (minhaLista.procura(nomeEquipe) != -1)
                        cout << minhaLista.procura(nomeEquipe) << endl;
                    else
                        cout << "Nao encontrado" << endl;
                    break;                    
                case 'r': // remover do início
                    minhaLista.removeNoInicio();
                    break;
                case 'a': // remover do fim
                    minhaLista.removeNoFim();
                    break;
                case 'x': // remover específico
                    cin >> nomeEquipe;
                    minhaLista.removeEspecifico(nomeEquipe);
                    break;                                   
                case 'p': // imprimir lista
                    minhaLista.imprime();
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