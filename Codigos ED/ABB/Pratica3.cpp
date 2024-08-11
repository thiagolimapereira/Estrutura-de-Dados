/*A partir do código fornecido, implemente os métodos que calculam a quantidade de nós folhas em uma árvore binária. Não é necessário manter o projeto do programa exemplo. Métodos auxiliares podem ser criados. Métodos da contagem de folhas que não forem usados devem ser apagados.

A quantidade de folhas numa árvore vazia é zero.

Entradas:

Número de valores a serem lidos.
Valores (inteiros) a inserir na árvore.
Saídas:

Quantidade de nós folha.*/

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
    int calculaAlturaAux(noh* atual);
    int calculaFolhasAux(noh* atual);

    public:
    ABB();
    ~ABB();
    void deletaTudo(noh* atual); 
    noh* getRaiz();
    bool vazia();
    void inserir(int n);
    void remover(int n);
    bool buscar(int n, objeto& objRetorno, int& altura);
    void imprimePreOrdem(noh* atual, int nivel);
    void imprimeEmOrdem(noh* atual, int nivel);
    void imprimePosOrdem(noh* atual, int nivel);
    int calculaAltura();
    bool existe(int n);
    int calculaFolhas();
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

bool ABB::buscar(int n, objeto& objRetorno, int& altura){
    if (vazia()){
        return false;
    }
    else{
        noh* aux = raiz;
        while(aux != NULL){
            if(n == aux->elemento.getNumero()){
                objRetorno = aux->elemento;
                altura = calculaAlturaAux(aux);
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

bool ABB::existe(int n){
    int altura;
    objeto objAux;
    return buscar(n, objAux, altura);
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

int ABB::calculaAltura() {
    //se a raiz estiver null, retorna 0
    //se não, enquanto tiver filho dir ou esq soma 1
    return calculaAlturaAux(raiz);
}

int ABB::calculaAlturaAux(noh* atual){
    if (atual == NULL){
        return 0;
    }        
    else{
        int alturaEsq = calculaAlturaAux(atual->filhoEsquerda);
        int alturaDir = calculaAlturaAux(atual->filhoDireita);        
        return max(alturaEsq, alturaDir)+1;
    }
}

int ABB::calculaFolhas(){
    return calculaFolhasAux(raiz);
}

int ABB::calculaFolhasAux(noh* atual){
    if(atual == NULL){
        return 0;
    }
    else if(atual->filhoEsquerda == NULL && atual->filhoDireita == NULL){
        return 1;
    }
    else{
        return calculaFolhasAux(atual->filhoEsquerda) + calculaFolhasAux(atual->filhoDireita);
    }
}


int main() {
    ABB abb;
    int qtdValores;
    cin >> qtdValores;
    int valor;
    
    for(int i = 0; i < qtdValores; i++){
        cin >> valor;
        abb.inserir(valor);
    }

    cout << abb.calculaFolhas() << endl;

    return 0;
}