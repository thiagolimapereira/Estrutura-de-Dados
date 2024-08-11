/*Esse é um código de uma árvore binária de busca (ABB) que possui as seguintes funções úteis:
    - Inserir(i): insere um elemento na árvore
    - Remover(r): remove um elemento da árvore
    - Imprimir em ordem(o): imprime a árvore em ordem
    - Imprimir pré-ordem(p): imprime a árvore em pré-ordem
    - Imprimir pós-ordem(z): imprime a árvore em pós-ordem
    - Buscar(b): busca um elemento na árvore, retornando o elemento e a altura do nó
    - Calcular altura(a): calcula a altura da árvore
    - Calcular folhas(c): calcula a quantidade de folhas da árvore
    - Finalizar(f): finaliza a execução do programa
*/

#include <iostream>
using namespace std;

// Classe objeto representa o conteúdo armazenado em cada nó da árvore
class objeto {
    private:
    int numero; // valor armazenado no objeto

    public:
    // Construtor padrão, inicializa numero com -1
    objeto() {
        numero = -1;
    }
    // Construtor que inicializa numero com o valor fornecido
    objeto(int n) {
        numero = n;
    }
    // Retorna o valor armazenado no objeto
    int getNumero() {
        return numero;
    }
};

// Classe noh representa cada nó na árvore binária de busca
class noh {
    // Declara ABB como classe amiga para acessar os membros privados de noh
    friend class ABB;
    private:
    objeto elemento; // objeto armazenado no nó
    noh* filhoEsquerda; // ponteiro para o filho esquerdo
    noh* filhoDireita; // ponteiro para o filho direito
    
    public:
    // Construtor que inicializa o nó com um objeto e filhos como NULL
    noh(objeto o){
        elemento = o;
        filhoEsquerda = NULL;
        filhoDireita = NULL;
    }
};

// Classe ABB representa uma Árvore Binária de Busca
class ABB{
    private:
    noh* raiz; // ponteiro para a raiz da árvore
    void removerBusca(int n, noh*& atual); // função auxiliar para remover um nó
    void deletarNoh(noh*& atual); // função auxiliar para deletar um nó específico
    void obterSucessor(objeto& objSucessor, noh* aux); // obtém o sucessor de um nó
    int calculaAlturaAux(noh* atual); // função auxiliar para calcular a altura da árvore
    int calculaFolhasAux(noh* atual); // função auxiliar para contar o número de folhas
    
    public:
    // Construtor que inicializa a árvore com raiz nula
    ABB();
    // Destrutor que deleta todos os nós da árvore
    ~ABB();
    // Função auxiliar para deletar todos os nós a partir de um nó específico
    void deletaTudo(noh* atual); 
    // Retorna a raiz da árvore
    noh* getRaiz();
    // Verifica se a árvore está vazia
    bool vazia();
    // Insere um novo valor na árvore
    void inserir(int n);
    // Remove um valor da árvore
    void remover(int n);
    // Busca um valor na árvore e retorna o objeto e a altura do nó
    bool buscar(int n, objeto& objRetorno, int& altura);
    // Imprime a árvore em pré-ordem
    void imprimePreOrdem(noh* atual, int nivel);
    // Imprime a árvore em ordem
    void imprimeEmOrdem(noh* atual, int nivel);
    // Imprime a árvore em pós-ordem
    void imprimePosOrdem(noh* atual, int nivel);
    // Calcula a altura da árvore
    int calculaAltura();
    // Verifica se um valor existe na árvore
    bool existe(int n);
    // Conta o número de folhas na árvore
    int calculaFolhas();
};

// Implementação do construtor que inicializa a raiz como NULL
ABB::ABB() {
    raiz = NULL;
}

// Implementação do destrutor que deleta todos os nós da árvore
ABB::~ABB() {
    deletaTudo(raiz);
}

// Deleta todos os nós a partir de um nó específico
void ABB::deletaTudo(noh* atual) {
    if (atual != NULL) {
        deletaTudo(atual->filhoEsquerda);
        deletaTudo(atual->filhoDireita);
        delete atual;
    }
}

// Retorna a raiz da árvore
noh* ABB::getRaiz(){
    return raiz;
}

// Verifica se a árvore está vazia
bool ABB::vazia(){
    return raiz == NULL;
}

// Insere um novo valor na árvore
void ABB::inserir(int n){
    noh* novo = new noh(objeto(n)); // cria um novo nó com o valor fornecido
    if(vazia()){
        raiz = novo; // se a árvore estiver vazia, o novo nó se torna a raiz
    }
    else{
        noh* aux = raiz;
        while(aux != NULL){
            if(n < aux->elemento.getNumero()){
                // se o valor for menor que o valor do nó atual, vai para o filho esquerdo
                if (aux->filhoEsquerda == NULL){
                    aux->filhoEsquerda = novo;
                    aux = NULL;
                }
                else{
                    aux = aux->filhoEsquerda;
                }                    
            }
            else{
                // se o valor for maior ou igual ao valor do nó atual, vai para o filho direito
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

// Remove um valor da árvore
void ABB::remover(int n){
    removerBusca(n, raiz);
}

// Função auxiliar para remover um nó específico
void ABB::removerBusca(int n, noh*& atual){
    if(n == atual->elemento.getNumero()){
        deletarNoh(atual); // se encontrar o nó, deleta-o
    }
    else if(n < atual->elemento.getNumero()){
        removerBusca(n, atual->filhoEsquerda); // continua a busca na subárvore esquerda
    }
    else{
        removerBusca(n, atual->filhoDireita); // continua a busca na subárvore direita
    }
}

// Função auxiliar que deleta um nó específico
void ABB::deletarNoh(noh*& atual){
    noh* aux = atual;
    if(atual->filhoEsquerda == NULL){
        atual = atual->filhoDireita; // substitui o nó removido pelo filho direito
        delete aux;
    }
    else if(atual->filhoDireita == NULL){
        atual = atual->filhoEsquerda; // substitui o nó removido pelo filho esquerdo
        delete aux;
    }
    else{
        objeto objSucessor; 
        obterSucessor(objSucessor, atual); // encontra o sucessor para substituir o nó removido
        atual->elemento = objSucessor;
        removerBusca(objSucessor.getNumero(), atual->filhoDireita); // remove o nó sucessor da sua posição original
    }    
}

// Função auxiliar que encontra o sucessor de um nó
void ABB::obterSucessor(objeto& objSucessor, noh* aux){
    aux = aux->filhoDireita;
    while(aux->filhoEsquerda != NULL){
        aux = aux->filhoEsquerda; // o sucessor é o nó mais à esquerda na subárvore direita
    }
    objSucessor = aux->elemento; 
}  

// Função que busca um valor na árvore e retorna o objeto e a altura do nó
bool ABB::buscar(int n, objeto& objRetorno, int& altura){
    if (vazia()){
        return false;
    }
    else{
        noh* aux = raiz;
        while(aux != NULL){
            if(n == aux->elemento.getNumero()){
                objRetorno = aux->elemento;
                altura = calculaAlturaAux(aux); // calcula a altura do nó encontrado
                return true;
            }
            else if(n < aux->elemento.getNumero()){
                aux = aux->filhoEsquerda;
            }
            else{
                aux = aux->filhoDireita;
            }
        }
        return false; // retorna false se o valor não for encontrado
    }   
}

// Verifica se um valor existe na árvore
bool ABB::existe(int n){
    int altura;
    objeto objAux;
    return buscar(n, objAux, altura);
}

// Imprime a árvore em pré-ordem
void ABB::imprimePreOrdem(noh* atual, int nivel){
    if(atual != NULL){
        cout << atual->elemento.getNumero() << "/" << nivel << " ";
        imprimePreOrdem(atual->filhoEsquerda, nivel+1);
        imprimePreOrdem(atual->filhoDireita, nivel+1);
    }
}

// Imprime a árvore em ordem
void ABB::imprimeEmOrdem(noh* atual, int nivel){
    if(atual != NULL){
        imprimeEmOrdem(atual->filhoEsquerda, nivel+1);
        cout << atual->elemento.getNumero() << "/" << nivel << " ";
        imprimeEmOrdem(atual->filhoDireita, nivel+1);
    }
}

// Imprime a árvore em pós-ordem
void ABB::imprimePosOrdem(noh* atual, int nivel){
    if(atual != NULL){
        imprimePosOrdem(atual->filhoEsquerda, nivel+1);
        imprimePosOrdem(atual->filhoDireita, nivel+1);
        cout << atual->elemento.getNumero() << "/" << nivel << " ";
    }
}

// Calcula a altura da árvore
int ABB::calculaAltura() {
    return calculaAlturaAux(raiz);
}

// Função auxiliar que calcula a altura da árvore a partir de um nó específico
int ABB::calculaAlturaAux(noh* atual){
    if (atual == NULL){
        return 0;
    }        
    else{
        int alturaEsq = calculaAlturaAux(atual->filhoEsquerda);
        int alturaDir = calculaAlturaAux(atual->filhoDireita);        
        return max(alturaEsq, alturaDir)+1; // retorna a maior altura entre os filhos esquerdo e direito
    }
}

// Conta o número de folhas na árvore
int ABB::calculaFolhas(){
    return calculaFolhasAux(raiz);
}

// Função auxiliar que conta o número de folhas a partir de um nó específico
int ABB::calculaFolhasAux(noh* atual){
    if(atual == NULL){
        return 0;
    }
    else if(atual->filhoEsquerda == NULL && atual->filhoDireita == NULL){
        return 1; // se o nó não tiver filhos, é uma folha
    }
    else{
        return calculaFolhasAux(atual->filhoEsquerda) + calculaFolhasAux(atual->filhoDireita); // soma as folhas dos filhos esquerdo e direito
    }
}

int main() {
    ABB abb; // cria uma árvore binária de busca
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
                    if(abb.existe(valor)){
                        abb.remover(valor);
                    }
                    else{
                        cout << "ERRO" << endl;
                    }
                    break;
                case 'o': // imprimir em ordem
                    abb.imprimeEmOrdem(abb.getRaiz(), 0);
                    break;
                case 'p': // imprimir em pré-ordem
                    abb.imprimePreOrdem(abb.getRaiz(), 0);
                    break;
                case 'z': // imprimir em pós-ordem
                    abb.imprimePosOrdem(abb.getRaiz(), 0);
                    break;
                case 'b': // buscar
                    cin >> valor;
                    int altura;
                    if(abb.buscar(valor, objAux, altura)){
                        cout << objAux.getNumero() << " - altura: " << altura-1 << endl;
                    }
                    else{
                        cout << "Objeto não encontrado!" << endl;
                    }
                    break;
                case 'a': // calcular altura
                    cout << abb.calculaAltura() << endl;
                    break;
                case 'c': // calcular folhas
                    cout << abb.calculaFolhas() << endl;
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