/*Implemente uma classe para representar árvores AVL, que contém operações para inserir, buscar, remover e escrever a estrutura da árvore. O código fornecido contém a implementação para escrever a estrutura e também uma sugestão de atributos e métodos necessários. O atributo altura da classe nó é obrigatório e é usado no método de escrita. Também já está implementado o programa que usa a classe AVL.

Entradas:

O programa lê códigos de comandos a executar. Sempre um caractere identificando o comando, seguido dos parâmetros necessários para executar o comando, se houverem. Os códigos de comandos são:

i: para inserir um elemento (string / número real) à árvore, sendo que os dados são ordenados pela string;
b: para buscar um valor (número real) associado a uma chave (string);
r: para remover um elemento, seguido da chave (string) do elemento;
e: para escrever a estrutura da árvore.
Saídas:

Somente o comando para escrever produz saída no formato especificado, que já está implementado.*/

#include <iostream>
#include <queue>
#include <stdexcept>
using namespace std;

class objeto {
    private:
    string chave;
    double numero;

    public:
    objeto() {
        chave = "";
        numero = -1;
    }
    objeto(string c, double n) {
        chave = c;
        numero = n;
    }
    double getNumero() {
        return numero;
    }
    string getChave() {
        return chave;
    }
};

class noh {
    friend class AVL;
    friend std::ostream& operator<<(std::ostream& saida, noh* ptNoh);
    private:
    objeto elemento;
    noh* filhoEsquerda;
    noh* filhoDireita;
    int fatorB;
    int altura;
    public:
    noh(objeto o){
        elemento = o;
        filhoEsquerda = NULL;
        filhoDireita = NULL;
        fatorB = 0;
        altura = 1;
    }
};

class AVL{
    private:
    noh* raiz;
    void removerBusca(string c, noh*& atual, bool& diminuiu);
    void deletarNoh(noh*& atual, bool& diminuiu);
    void obterSucessor(objeto& objSucessor, noh* aux);

    public:
    AVL();
    ~AVL();
    void deletaTudo(noh* atual); 
    noh* getRaiz();
    bool vazia();
    void inserir(string c, double n);
    void remover(string c);
    bool buscar(string c, objeto& objRetorno);
    void imprimePreOrdem(noh* atual, int nivel);
    void imprimeEmOrdem(noh* atual, int nivel);
    void imprimePosOrdem(noh* atual, int nivel);
    void escreverNivelANivel(ostream& saida);
    void rotacaodireita(noh*& tree);
    void rotacaoesquerda(noh*& tree);  
    void rotacaoesquerdadireita(noh*& tree);
    void rotacaodireitaesquerda(noh*& tree);
    void realizarotacao(noh*& tree);
    void insererecursivo(noh*& atual, objeto o, bool& cresceu);
    int getAltura(noh* atual);
    void atualizaAltura(noh* atual);
};

AVL::AVL() {
    raiz = NULL;
}

AVL::~AVL() {
    deletaTudo(raiz);
}

void AVL::deletaTudo(noh* atual) {
    if (atual != NULL) {
        deletaTudo(atual->filhoEsquerda);
        deletaTudo(atual->filhoDireita);
        delete atual;
    }
}

noh* AVL::getRaiz(){
    return raiz;
}

bool AVL::vazia(){
    return raiz == NULL;
}

void AVL::inserir(string c, double n){
    objeto o(c, n);
    bool cresceu;
    insererecursivo(raiz, o, cresceu);
}

void AVL::insererecursivo(noh*& atual, objeto o, bool& cresceu){
        if (atual == NULL) {
            atual = new noh(o);            
            cresceu = true;
            return;
        }  
        if (o.getChave() < atual->elemento.getChave()) {
            insererecursivo(atual->filhoEsquerda, o, cresceu);
            if (cresceu){
                atual->fatorB-=1;   
            } 
        } else {
            insererecursivo(atual->filhoDireita, o, cresceu);
            if (cresceu){
                atual->fatorB+=1;
            }    
        }
        atualizaAltura(atual); 
        realizarotacao(atual);

        if (cresceu && atual->fatorB == 0){
            cresceu = false;
        }
    }

void AVL::remover(string c){
    bool diminuiu;
    removerBusca(c, raiz, diminuiu);
}

void AVL::removerBusca(string c, noh*& atual, bool& diminuiu){
    if (c < atual->elemento.getChave()){
        removerBusca(c, atual->filhoEsquerda, diminuiu);
        if (diminuiu){
            atual->fatorB+=1;
        }
    } else if (c > atual->elemento.getChave()){
        removerBusca(c, atual->filhoDireita, diminuiu);
        if (diminuiu){
            atual->fatorB-=1;
        }
    } else{
        deletarNoh(atual, diminuiu);
    }
    if (atual != NULL){
        atualizaAltura(atual);
        realizarotacao(atual);
        if (diminuiu && atual->fatorB != 0){
            diminuiu = false;
        }
    }
}

void AVL::deletarNoh(noh*& atual, bool& diminuiu){
    noh* aux = atual;
    if(atual->filhoEsquerda == NULL){
        atual = atual->filhoDireita;
        diminuiu = true;
        delete aux;
    }
    else if(atual->filhoDireita == NULL){
        atual = atual->filhoEsquerda;
        diminuiu = true;
        delete aux;
    }
    else{
        objeto objSucessor; 
        obterSucessor(objSucessor, atual);
        atual->elemento = objSucessor;
        removerBusca(objSucessor.getChave(), atual->filhoDireita, diminuiu);
        if (diminuiu){
            atual->fatorB-=1;
        }
    }    
}

void AVL::obterSucessor(objeto& objSucessor, noh* aux){
    aux = aux->filhoDireita;
    while(aux->filhoEsquerda != NULL){
        aux = aux->filhoEsquerda;
    }
    objSucessor = aux->elemento; 
}  

bool AVL::buscar(string c, objeto& objRetorno){
    if (vazia()){
        return false;
    }
    else{
        noh* aux = raiz;
        while(aux != NULL){
            if(c == aux->elemento.getChave()){
                objRetorno = aux->elemento;
                return true;
            }
            else if(c < aux->elemento.getChave()){
                aux = aux->filhoEsquerda;
            }
            else{
                aux = aux->filhoDireita;
            }
        }
        return false;
    }   
}

void AVL::imprimePreOrdem(noh* atual, int nivel){
    if(atual != NULL){
        cout << atual->elemento.getChave() << "/" << nivel << " ";
        imprimePreOrdem(atual->filhoEsquerda, nivel+1);
        imprimePreOrdem(atual->filhoDireita, nivel+1);
    }
}

void AVL::imprimeEmOrdem(noh* atual, int nivel){
    if(atual != NULL){
        imprimeEmOrdem(atual->filhoEsquerda, nivel+1);
        cout << atual->elemento.getChave() << "/" << nivel << " ";
        imprimeEmOrdem(atual->filhoDireita, nivel+1);
    }
}

void AVL::imprimePosOrdem(noh* atual, int nivel){
    if(atual != NULL){
        imprimePosOrdem(atual->filhoEsquerda, nivel+1);
        imprimePosOrdem(atual->filhoDireita, nivel+1);
        cout << atual->elemento.getChave() << "/" << nivel << " ";
    }
}

ostream& operator<<(ostream& saida, noh* ptNoh) {
    if (ptNoh == NULL)
        saida << "[]";
    else
        saida << '[' << ptNoh->altura << ':' << ptNoh->elemento.getChave() << '/' << ptNoh->elemento.getNumero() << ']';
    return saida;
}

// Escreve o conteúdo da árvore nível a nível, na saída de dados informada.
// Usado para conferir se a estrutra da árvore está correta.
void AVL::escreverNivelANivel(ostream& saida) {
    queue<noh*> filhos;
    noh* fimDeNivel = new noh(objeto()); // nó especial para marcar fim de um nível
    filhos.push(raiz);
    filhos.push(fimDeNivel);
    while (not filhos.empty()) {
        noh* ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel) {
            saida << "\n";
            if (not filhos.empty())
                filhos.push(fimDeNivel);
        }
        else {
            cout<< ptNoh << ' ';
            if (ptNoh != NULL) {
                filhos.push(ptNoh->filhoEsquerda);
                filhos.push(ptNoh->filhoDireita);
            }
        }
    }
    delete fimDeNivel;
}

int AVL::getAltura(noh* atual){
    if(atual == NULL){
        return 0;
    }
    else{
        return atual->altura;
    }
}

void AVL::atualizaAltura(noh* atual){
    if(atual != NULL){
        int altEsq = getAltura(atual->filhoEsquerda);
        int altDir = getAltura(atual->filhoDireita);
        atual->altura = 1 + max(altEsq, altDir);
    }
}

void AVL::rotacaodireita(noh*& pai){
    noh* novopai = pai->filhoEsquerda;
    pai->filhoEsquerda = novopai->filhoDireita;
    novopai->filhoDireita = pai;
    atualizaAltura(pai);
    atualizaAltura(novopai);
    pai = novopai;
}

void AVL::rotacaoesquerda(noh*& pai){
    noh* novopai = pai->filhoDireita;
    pai->filhoDireita = novopai->filhoEsquerda;
    novopai->filhoEsquerda = pai;
    atualizaAltura(pai);
    atualizaAltura(novopai);
    pai = novopai;
}

void AVL::rotacaoesquerdadireita(noh*& pai){
    noh* filho = pai->filhoEsquerda;
    rotacaoesquerda(filho);
    pai->filhoEsquerda = filho;
    rotacaodireita(pai);
}


void AVL::rotacaodireitaesquerda(noh*& pai){
    noh* filho = pai->filhoDireita;
    rotacaodireita(filho);
    pai->filhoDireita = filho;
    rotacaoesquerda(pai);
}

void AVL::realizarotacao(noh*& pai){
    noh* filho;
    noh* neto; // Caso precise da rotação dupla

    if (pai->fatorB == -2){ //rotaciona para a direita

    filho = pai->filhoEsquerda;

    if (filho->fatorB == -1){ // Simples para a direita
        pai->fatorB = 0;
        filho->fatorB = 0;
        rotacaodireita(pai);
    } else if (filho->fatorB == 0){ // Simples para a direita
        pai->fatorB = -1;
        filho->fatorB = 1;
        rotacaodireita(pai);
    } else if (filho->fatorB == 1){ // Rotação dupla
        neto = filho->filhoDireita;
        if (neto->fatorB == -1){
            pai->fatorB = 1;
            filho->fatorB = 0;
        } else if (neto->fatorB == 0){
            pai->fatorB = 0;
            filho->fatorB = 0;                
        } else if (neto->fatorB == 1){
            pai->fatorB = 0;
            filho->fatorB = -1;                
        }
        neto->fatorB = 0; 
        rotacaodireitaesquerda(pai);            
    }

    } else if(pai->fatorB == 2){ //rotaciona para a esquerda
        filho = pai->filhoDireita;
        if (filho->fatorB == 1) { // Simples para a esquerda
            pai->fatorB = 0;
            filho->fatorB = 0;
            rotacaoesquerda(pai);
        } else if (filho->fatorB == 0){ // Simples para a esquerda         
            pai->fatorB = 1;
            filho->fatorB = -1;
            rotacaoesquerda(pai);
        } else if (filho->fatorB == -1){ // Rotacao dupla
            neto = filho->filhoEsquerda;
            if (neto->fatorB == -1){
                pai->fatorB =  0;
                filho->fatorB = 1; 
            } else if (neto->fatorB == 0){
                pai->fatorB =  0;
                filho->fatorB = 0; 
            } else if (neto->fatorB == 1){
                pai->fatorB =  -1;
                filho->fatorB = 0; 
            }
            neto->fatorB = 0;
            rotacaodireitaesquerda(pai);
        }
    }
}   


int main() {
    AVL avl;
    objeto objAux;
    char comando;
    string chave;
    double valor = -1;    
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> chave;
                    cin >> valor;
                    avl.inserir(chave, valor);
                    break;
                case 'r': // remover
                    cin >> chave;
                    if(avl.buscar(chave, objAux)){
                        avl.remover(chave);
                    }
                    else{
                        cout << "ERRO" << endl;
                    }
                    break;
                case 'o': 
                    avl.imprimeEmOrdem(avl.getRaiz(), 0);
                    break;
                case 'p': 
                    avl.imprimePreOrdem(avl.getRaiz(), 0);
                    break;
                case 'z': 
                    avl.imprimePosOrdem(avl.getRaiz(), 0);
                    break;
                case 'b': // buscar
                    cin >> chave;
                    if(avl.buscar(chave, objAux)){
                        cout << objAux.getNumero() << endl;
                    }
                    else{
                        cout << "Objeto não encontrado!" << endl;
                    }
                    break; 
                case 'e': // escrever nível a nível
                    avl.escreverNivelANivel(cout);
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