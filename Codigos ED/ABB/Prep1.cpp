/*Implemente uma Árvore Binária de Busca (ABB) com operações para inserir, remover e escrever os elementos de duas formas (em ordem e pré-ordem). A árvore criada deve ser capaz de armazenar um único tipo de informação (chave). As chaves no programa serão números inteiros, porém, quando mais independente for a classe, melhor. A estratégia a respeito de como lidar com chaves repetidas não é importante.

As operações para escrever elementos devem sempre escrever a chave, uma barra e o nível na árvore em que a chave está. Isso vai ajudar a determinar a estrutura da árvore ao testar o programa. Não devem ser colocados espaços antes nem depois da barra.

Caso tentem remover uma chave que não está na árvore, o programa deverá escrever "ERRO" (letras maiúsculas, sem as aspas) na saída padrão. A operação de escrita deve estar na função principal (programa) e não em algum método.

A estratégia de remoção de nó com dois filhos deve ser a de substituir pelo sucessor.

O programa deverá ler comandos identificados por letras minúsculas e seus parâmetros (quando necessário). Os comandos possíveis devem ser:

A letra i, seguida de uma chave para inserir uma chave na árvore.
A letra r, seguida de uma chave para remover uma chave da árvore.
A letra o para escrever os elementos em ordem, no formato descrito acima.
A letra p para escrever os elementos em pré-ordem, no formato descrito acima.
A letra f para finalizar a execução do programa.
Entradas:

Uma sequência de comandos, conforme especificado acima.

Saídas:

Somente os comandos para escrever produzem saída, conforme formato explicado acima.*/

#include <iostream>
using namespace std;

class objeto {
    private:
    int numero;

    public:
    objeto() {
        numero = -1;
    }
    objeto(int n) {
        numero = n;
    }
    int getNumero() {
        return numero;
    }
};

class noh {
    friend class ABB;
    private:
    objeto elemento;
    noh* filhoEsquerda;
    noh* filhoDireita;
    public:
    noh(objeto o){
        elemento = o;
        filhoEsquerda = NULL;
        filhoDireita = NULL;
    }
};

class ABB{
    private:
    noh* raiz;
    void removerBusca(int n, noh*& atual);
    void deletarNoh(noh*& atual);
    void obterSucessor(objeto& objSucessor, noh* aux);

    public:
    ABB();
    ~ABB();
    void deletaTudo(noh* atual); 
    noh* getRaiz();
    bool vazia();
    void inserir(int n);
    void remover(int n);
    bool buscar(int n, objeto& objRetorno);
    void imprimePreOrdem(noh* atual, int nivel);
    void imprimeEmOrdem(noh* atual, int nivel);
    void imprimePosOrdem(noh* atual, int nivel);
};

ABB::ABB() {
    raiz = NULL;
}

ABB::~ABB() {
    deletaTudo(raiz);
}

void ABB::deletaTudo(noh* atual) {
    if (atual != NULL) {
        deletaTudo(atual->filhoEsquerda);
        deletaTudo(atual->filhoDireita);
        delete atual;
    }
}

noh* ABB::getRaiz(){
    return raiz;
}

bool ABB::vazia(){
    return raiz == NULL;
}

void ABB::inserir(int n){
    noh* novo = new noh(objeto(n));
    if(vazia()){
        raiz = novo;
    }
    else{
        noh* aux = raiz;
        while(aux != NULL){
            if(n < aux->elemento.getNumero()){
                if (aux->filhoEsquerda == NULL){
                    aux->filhoEsquerda = novo;
                    aux = NULL;
                }
                else{
                    aux = aux->filhoEsquerda;
                }                    
            }
            else{
                if (aux->filhoDireita == NULL){
                    aux->filhoDireita = novo;
                    aux = NULL;
                }
                else{
                    aux = aux->filhoDireita;
                }
            }                
        }
    }
}

void ABB::remover(int n){
    removerBusca(n, raiz);
}

void ABB::removerBusca(int n, noh*& atual){
    if(n == atual->elemento.getNumero()){
        deletarNoh(atual);
    }
    else if(n < atual->elemento.getNumero()){
        removerBusca(n, atual->filhoEsquerda);
    }
    else{
        removerBusca(n, atual->filhoDireita);
    }
}

void ABB::deletarNoh(noh*& atual){
    noh* aux = atual;
    if(atual->filhoEsquerda == NULL){
        atual = atual->filhoDireita;
        delete aux;
    }
    else if(atual->filhoDireita == NULL){
        atual = atual->filhoEsquerda;
        delete aux;
    }
    else{
        objeto objSucessor; 
        obterSucessor(objSucessor, atual);
        atual->elemento = objSucessor;
        removerBusca(objSucessor.getNumero(), atual->filhoDireita);
    }    
}

void ABB::obterSucessor(objeto& objSucessor, noh* aux){
    aux = aux->filhoDireita;
    while(aux->filhoEsquerda != NULL){
        aux = aux->filhoEsquerda;
    }
    objSucessor = aux->elemento; 
}  

bool ABB::buscar(int n, objeto& objRetorno){
    if (vazia()){
        return false;
    }
    else{
        noh* aux = raiz;
        while(aux != NULL){
            if(n == aux->elemento.getNumero()){
                objRetorno = aux->elemento;
                return true;
            }
            else if(n < aux->elemento.getNumero()){
                aux = aux->filhoEsquerda;
            }
            else{
                aux = aux->filhoDireita;
            }
        }
        return false;
    }   
}

void ABB::imprimePreOrdem(noh* atual, int nivel){
    if(atual != NULL){
        cout << atual->elemento.getNumero() << "/" << nivel << " ";
        imprimePreOrdem(atual->filhoEsquerda, nivel+1);
        imprimePreOrdem(atual->filhoDireita, nivel+1);
    }
}

void ABB::imprimeEmOrdem(noh* atual, int nivel){
    if(atual != NULL){
        imprimeEmOrdem(atual->filhoEsquerda, nivel+1);
        cout << atual->elemento.getNumero() << "/" << nivel << " ";
        imprimeEmOrdem(atual->filhoDireita, nivel+1);
    }
}

void ABB::imprimePosOrdem(noh* atual, int nivel){
    if(atual != NULL){
        imprimePosOrdem(atual->filhoEsquerda, nivel+1);
        imprimePosOrdem(atual->filhoDireita, nivel+1);
        cout << atual->elemento.getNumero() << "/" << nivel << " ";
    }
}


int main() {
    ABB abb;
    objeto objAux;
    char comando;
    int valor = -1;    
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> valor;
                    abb.inserir(valor);
                    break;
                case 'r': // remover
                    cin >> valor;
                    if(abb.buscar(valor, objAux)){
                        abb.remover(valor);
                    }
                    else{
                        cout << "ERRO" << endl;
                    }
                    break;
                case 'o': 
                    abb.imprimeEmOrdem(abb.getRaiz(), 0);
                    break;
                case 'p': 
                    abb.imprimePreOrdem(abb.getRaiz(), 0);
                    break;
                case 'z': 
                    abb.imprimePosOrdem(abb.getRaiz(), 0);
                    break;
                case 'b': // buscar
                    cin >> valor;
                    if(abb.buscar(valor, objAux)){
                        cout << objAux.getNumero() << endl;
                    }
                    else{
                        cout << "Objeto não encontrado!" << endl;
                    }
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
    return 0;
}