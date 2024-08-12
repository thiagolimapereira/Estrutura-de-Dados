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

// Classe objeto que representa um elemento a ser armazenado na árvore AVL
class objeto {
    private:
    string chave; // Chave de busca (string)
    double numero; // Valor associado à chave (número real)

    public:
    // Construtor padrão que inicializa a chave como uma string vazia e o número como -1
    objeto() {
        chave = "";
        numero = -1;
    }

    // Construtor que inicializa a chave e o número com os valores fornecidos
    objeto(string c, double n) {
        chave = c;
        numero = n;
    }

    // Método que retorna o valor associado à chave
    double getNumero() {
        return numero;
    }

    // Método que retorna a chave
    string getChave() {
        return chave;
    }
};

// Classe noh que representa um nó da árvore AVL
class noh {
    // Permite que a classe AVL acesse os membros privados da classe noh
    friend class AVL;
    // Sobrecarga do operador de saída para facilitar a impressão de um nó
    friend std::ostream& operator<<(std::ostream& saida, noh* ptNoh);
    private:
    objeto elemento; // Elemento armazenado no nó (objeto)
    noh* filhoEsquerda; // Ponteiro para o filho à esquerda
    noh* filhoDireita; // Ponteiro para o filho à direita
    int fatorB; // Fator de balanceamento do nó
    int altura; // Altura do nó

    public:
    // Construtor que inicializa o nó com um objeto e define os ponteiros como NULL
    noh(objeto o){
        elemento = o;
        filhoEsquerda = NULL;
        filhoDireita = NULL;
        fatorB = 0;
        altura = 1;
    }
};

// Classe AVL que representa a árvore AVL
class AVL{
    private:
    noh* raiz; // Ponteiro para a raiz da árvore
    // Métodos auxiliares privados
    void removerBusca(string c, noh*& atual, bool& diminuiu);
    void deletarNoh(noh*& atual, bool& diminuiu);
    void obterSucessor(objeto& objSucessor, noh* aux);
    void rotacaodireita(noh*& tree);
    void rotacaoesquerda(noh*& tree);  
    void rotacaoesquerdadireita(noh*& tree);
    void rotacaodireitaesquerda(noh*& tree);
    void realizarotacao(noh*& tree);
    void insererecursivo(noh*& atual, objeto o, bool& cresceu);
    void deletaTudo(noh* atual);
    void atualizaAltura(noh* atual); 

    public:
    // Construtor que inicializa a árvore como vazia
    AVL();
    // Destrutor que deleta todos os nós da árvore
    ~AVL();    
    noh* getRaiz(); // Retorna a raiz da árvore
    bool vazia(); // Verifica se a árvore está vazia
    void inserir(string c, double n); // Insere um elemento na árvore
    void remover(string c); // Remove um elemento da árvore
    bool buscar(string c, objeto& objRetorno); // Busca um elemento na árvore
    void imprimePreOrdem(noh* atual, int nivel); // Imprime a árvore em pré-ordem
    void imprimeEmOrdem(noh* atual, int nivel); // Imprime a árvore em ordem
    void imprimePosOrdem(noh* atual, int nivel); // Imprime a árvore em pós-ordem
    void escreverNivelANivel(ostream& saida); // Escreve a árvore nível a nível
    int getAltura(noh* atual); // Retorna a altura de um nó
    objeto maximo(); // Retorna o objeto com a maior chave
    objeto minimo(); // Retorna o objeto com a menor chave
};

// Implementação do construtor da classe AVL
AVL::AVL() {
    raiz = NULL;
}

// Implementação do destrutor da classe AVL
AVL::~AVL() {
    deletaTudo(raiz);
}

// Função recursiva que deleta todos os nós da árvore
void AVL::deletaTudo(noh* atual) {
    if (atual != NULL) {
        deletaTudo(atual->filhoEsquerda);
        deletaTudo(atual->filhoDireita);
        delete atual;
    }
}

// Retorna o ponteiro para a raiz da árvore
noh* AVL::getRaiz(){
    return raiz;
}

// Verifica se a árvore está vazia
bool AVL::vazia(){
    return raiz == NULL;
}

// Insere um novo objeto na árvore AVL
void AVL::inserir(string c, double n){
    objeto o(c, n);
    bool cresceu;
    insererecursivo(raiz, o, cresceu);
}

// Função recursiva para inserir um novo nó na árvore AVL
void AVL::insererecursivo(noh*& atual, objeto o, bool& cresceu){
    // Se o nó atual é nulo, insere o novo nó aqui
    if (atual == NULL) {
        atual = new noh(o);            
        cresceu = true;
        return;
    }  
    // Se a chave do objeto a ser inserido é menor que a chave do nó atual, insere à esquerda
    if (o.getChave() < atual->elemento.getChave()) {
        insererecursivo(atual->filhoEsquerda, o, cresceu);
        if (cresceu){
            atual->fatorB-=1;   
        } 
    } else {
        // Caso contrário, insere à direita
        insererecursivo(atual->filhoDireita, o, cresceu);
        if (cresceu){
            atual->fatorB+=1;
        }    
    }
    atualizaAltura(atual); // Atualiza a altura do nó atual
    realizarotacao(atual); // Realiza as rotações necessárias para manter o balanceamento da AVL

    if (cresceu && atual->fatorB == 0){
        cresceu = false;
    }
}

// Remove um elemento da árvore com a chave especificada
void AVL::remover(string c){
    objeto objAux;
    if (vazia() || !buscar(c, objAux)){
        throw runtime_error("ERRO");
    }

    bool diminuiu;
    removerBusca(c, raiz, diminuiu);
}

// Função recursiva para buscar e remover um elemento da árvore
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

// Função que deleta o nó atual da árvore AVL
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

// Função que obtém o sucessor de um nó na árvore
void AVL::obterSucessor(objeto& objSucessor, noh* aux){
    aux = aux->filhoDireita;
    while(aux->filhoEsquerda != NULL){
        aux = aux->filhoEsquerda;
    }
    objSucessor = aux->elemento; 
}  

// Função para buscar um elemento na árvore AVL
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

// Função para buscar o objeto com a maior chave na árvore
objeto AVL::maximo(){
    if (vazia()){
        throw runtime_error("ERRO");
    }
    else{
        noh* aux = raiz;
        while(aux->filhoDireita != NULL){
            aux = aux->filhoDireita;
        }
        return aux->elemento;
    }
}

// Função para buscar o objeto com a menor chave na árvore
objeto AVL::minimo(){
    if (vazia()){
        throw runtime_error("ERRO");
    }
    else{
        noh* aux = raiz;
        while(aux->filhoEsquerda != NULL){
            aux = aux->filhoEsquerda;
        }
        return aux->elemento;
    }
}

// Função para imprimir a árvore em pré-ordem (raiz, esquerda, direita)
void AVL::imprimePreOrdem(noh* atual, int nivel){
    if(atual != NULL){
        cout << atual->elemento.getChave() << "/" << nivel << " ";
        imprimePreOrdem(atual->filhoEsquerda, nivel+1);
        imprimePreOrdem(atual->filhoDireita, nivel+1);
    }
}

// Função para imprimir a árvore em ordem (esquerda, raiz, direita)
void AVL::imprimeEmOrdem(noh* atual, int nivel){
    if(atual != NULL){
        imprimeEmOrdem(atual->filhoEsquerda, nivel+1);
        cout << atual->elemento.getChave() << "/" << nivel << " ";
        imprimeEmOrdem(atual->filhoDireita, nivel+1);
    }
}

// Função para imprimir a árvore em pós-ordem (esquerda, direita, raiz)
void AVL::imprimePosOrdem(noh* atual, int nivel){
    if(atual != NULL){
        imprimePosOrdem(atual->filhoEsquerda, nivel+1);
        imprimePosOrdem(atual->filhoDireita, nivel+1);
        cout << atual->elemento.getChave() << "/" << nivel << " ";
    }
}

// Sobrecarga do operador de saída para imprimir o nó
ostream& operator<<(ostream& saida, noh* ptNoh) {
    if (ptNoh == NULL)
        saida << "[]";
    else
        saida << '[' << ptNoh->altura << ':' << ptNoh->elemento.getChave() << '/' << ptNoh->elemento.getNumero() << ']';
    return saida;
}

// Escreve o conteúdo da árvore nível a nível, na saída de dados informada.
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

// Função que retorna a altura de um nó
int AVL::getAltura(noh* atual){
    if(atual == NULL){
        return 0;
    }
    else{
        return atual->altura;
    }
}

// Atualiza a altura de um nó com base na altura dos seus filhos
void AVL::atualizaAltura(noh* atual){
    if(atual != NULL){
        int altEsq = getAltura(atual->filhoEsquerda);
        int altDir = getAltura(atual->filhoDireita);
        atual->altura = 1 + max(altEsq, altDir);
    }
}

// Rotação simples à direita
void AVL::rotacaodireita(noh*& pai){
    noh* novopai = pai->filhoEsquerda;
    pai->filhoEsquerda = novopai->filhoDireita;
    novopai->filhoDireita = pai;
    atualizaAltura(pai);
    atualizaAltura(novopai);
    pai = novopai;
}

// Rotação simples à esquerda
void AVL::rotacaoesquerda(noh*& pai){
    noh* novopai = pai->filhoDireita;
    pai->filhoDireita = novopai->filhoEsquerda;
    novopai->filhoEsquerda = pai;
    atualizaAltura(pai);
    atualizaAltura(novopai);
    pai = novopai;
}

// Rotação dupla à direita (esquerda-direita)
void AVL::rotacaoesquerdadireita(noh*& pai){
    noh* filho = pai->filhoEsquerda;
    rotacaoesquerda(filho);
    pai->filhoEsquerda = filho;
    rotacaodireita(pai);
}

// Rotação dupla à esquerda (direita-esquerda)
void AVL::rotacaodireitaesquerda(noh*& pai){
    noh* filho = pai->filhoDireita;
    rotacaodireita(filho);
    pai->filhoDireita = filho;
    rotacaoesquerda(pai);
}

// Função que realiza as rotações necessárias para manter o balanceamento da árvore AVL
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
        } else if (filho->fatorB == -1){ // Rotação dupla
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
                    avl.remover(chave);
                    break;
                case 'm': // máximo
                    cout << avl.maximo().getChave() << endl;
                    break;
                case 'n': // mínimo
                    cout << avl.minimo().getChave() << endl;
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