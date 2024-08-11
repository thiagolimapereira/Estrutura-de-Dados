/*Uma loja de ferramentas decidiu mudar sua estratégia de vendas e, sempre que um cliente pergunta por uma ferramenta, o vendedor oferece a de maior potência que tiver na loja. As ferramentas estão cadastradas com uma chave, o nome da ferramenta, a marca e a potência. Utilizando o código fornecido, implemente um árvore AVL com as funções de inserir e remover elementos. A ideia principal do problema é que implementação da remoção seja utilizando recursão, não sendo necessário o uso da função transplanta. A estratégia de remoção de elementos que não estejam em nós folhas é a substituição pelo elemento posterior (sucessor).

O código fornecido já tem o menu de entrada e o método de impressão. Não altere essas funções. O caminho mais fácil para a solução do exercício é não alterar a assinaturas das funções, dessa forma, não resultará em conflito com o código fornecido. O dado a ser armazenado na árvore é composto por uma chave do tipo inteiro, o nome da ferramenta do tipo string, a marca do tipo string e a potência do tipo inteiro. Não existem ferramentas diferentes com a mesma chave.

Entradas:

i - para inserir elemento : deve ler chave [inteiro] , nome da ferramenta [string], marca [string] e a potência [inteiro]
r - para remover elemento : deve ler chave [inteiro]
b - para buscar elemento : deve ler chave [inteiro]
l - para fazer o levantamento da marca com maior potência de uma dada ferramenta : deve ler nome da ferramenta [string]
e - para imprimir árvore
f - finalizar
Saídas:

i - inserir elemento : A operação de inserção não produz saída
r - remover elemento : A operação de remoção não produz saída
b - buscar elemento : A operação de busca escreve a frase: "Informações sobre a ferramenta: ([chave],[nome],[marca],[potencia])", em que [chave], [nome], [marca] e [potencia] devem ser substituídos pela respectiva chave, nome da ferramenta, marca da ferramenta e potência da ferramenta
l - levantamento de ferramenta: Imprime: "Levantamento do ferramenta [ferramenta]: [marca]", em que [ferramenta] é dada como entrada para o levantamento e [marca] deve ser substituída pela marca da ferramenta mais potente -- no caso de haver mais de uma marca com a mesma potência, o resultado deverá mostrar a marca da ferramenta de menor chave
e - imprimir árvore : imprime a árvore seguindo o padrão de formatação tree
f - finalizar : finaliza o programa
Exemplo de Entrada:

i 5 tupia Makita 650
i 7 serra_circular DeWalt 200
i 9 lixadeira Vonder 275
i 6 tupia Fort 1200
i 11 lixadeira Skill 250
i 42 serra_sabre Makita 850
i 43 serra_circular Bosch 200
i 44 furadeira Fort 650
i 45 esmerilhadeira Black&Decker 650
i 46 furadeira  Schulz 500
i 101 martelete DeWalt 500
i 103 serra_circular Fort 200
e
b 45
l lixadeira
l serra_circular
f
Exemplo de Saída:

(43,serra_circular)
 ├e─(7,serra_circular)
 │   ├e─(5,tupia)
 │   │   └d─(6,tupia)
 │   └d─(11,lixadeira)
 │       ├e─(9,lixadeira)
 │       └d─(42,serra_sabre)
 └d─(45,esmerilhadeira)
     ├e─(44,furadeira)
     └d─(101,martelete)
         ├e─(46,furadeira)
         └d─(103,serra_circular)
Elemento buscado: (45,esmerilhadeira,Black&Decker,650)
Levantamento do ferramenta lixadeira: Vonder
Levantamento do ferramenta serra_circular: DeWalt*/

#include <iostream>
#include <queue>
#include <stdexcept>
using namespace std;

class objeto {
    private:
    unsigned chave;
    string ferramenta;
    string marca;
    short potencia;

    public:
    objeto() {
        chave = 0;
        ferramenta = "";
        marca = "";
        potencia = 0;
    }
    objeto(unsigned c, string f, string m, short p) {
        chave = c;
        ferramenta = f;
        marca = m;
        potencia = p;
    }
    unsigned getChave() const {
        return chave;
    }
    string getFerramenta() const {
        return ferramenta;
    }
    string getMarca() const {
        return marca;
    }
    short getPotencia() const {
        return potencia;
    }
    void setChave(unsigned c) {
        chave = c;
    }
    void setFerramenta(string f) {
        ferramenta = f;
    }
    void setMarca(string m) {
        marca = m;
    }
    void setPotencia(short p) {
        potencia = p;
    }
};

ostream& operator<<(ostream& saida, const objeto& e) {
    saida << "(" << e.getChave() << "," << e.getFerramenta() << "," << e.getMarca() << "," << e.getPotencia() << ")";
    return saida;
}

class noh {
    friend class AVL;
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
    void removerBusca(unsigned c, noh*& atual, bool& diminuiu);
    void deletarNoh(noh*& atual, bool& diminuiu);
    void obterSucessor(objeto& objSucessor, noh* aux);
    void rotacaodireita(noh*& tree);
    void rotacaoesquerda(noh*& tree);  
    void rotacaoesquerdadireita(noh*& tree);
    void rotacaodireitaesquerda(noh*& tree);
    void realizarotacao(noh*& tree);
    void insererecursivo(noh*& atual, objeto o, bool& cresceu);
    int getAltura(noh* atual);
    void atualizaAltura(noh* atual);
    void imprimirDir(const std::string& prefixo, const noh* meuNoh);
    void imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao);
    void levantamentoRecursivo(noh* atual, string nomeFerramenta, string& marca, short& maiorPotencia, unsigned& menorChave);

    public:
    AVL();
    ~AVL();
    void deletaTudo(noh* atual); 
    noh* getRaiz();
    bool vazia();
    void inserir(unsigned c, string f, string m, short p);
    void remover(unsigned c);
    bool buscar(unsigned c, objeto& objRetorno);
    void imprimePreOrdem(noh* atual, int nivel);
    void imprimeEmOrdem(noh* atual, int nivel);
    void imprimePosOrdem(noh* atual, int nivel);
    void escreverNivelANivel(ostream& saida);
    void imprimir();
    string levantamento(string nomeFerramenta);
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

void AVL::inserir(unsigned c, string f, string m, short p){
    objeto o(c, f, m, p);
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

void AVL::remover(unsigned c){
    bool diminuiu;
    removerBusca(c, raiz, diminuiu);
}

void AVL::removerBusca(unsigned c, noh*& atual, bool& diminuiu){
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

bool AVL::buscar(unsigned c, objeto& objRetorno){
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

ostream& operator<<(ostream& output, AVL& arvore) {
    // arvore.percorreEmOrdemAux(arvore.raiz,0);
    arvore.imprimir();
    return output;
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void AVL::imprimirDir(const std::string& prefixo, const noh* meuNoh)
{
    if( meuNoh != nullptr )
    {
        std::cout << prefixo
                  << "└d─"
                  << "(" << meuNoh->elemento.getChave() << "," << meuNoh->elemento.getFerramenta() << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "    " , meuNoh->filhoEsquerda , meuNoh->filhoDireita==nullptr );
        imprimirDir( prefixo + "    " , meuNoh->filhoDireita );
    }
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void AVL::imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao)
{
    if( meuNoh != nullptr )
    {
        std::cout << prefixo ;

        // A impressao da arvore esquerda depende da indicacao se existe o irmao a direita
        if (temIrmao)
            std::cout << "└e─" ;
        else
            std::cout << "├e─";

        std::cout << "(" << meuNoh->elemento.getChave() << "," << meuNoh->elemento.getFerramenta() << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "│   " , meuNoh->filhoEsquerda, meuNoh->filhoDireita==nullptr );
        imprimirDir( prefixo + "│   " , meuNoh->filhoDireita );
    }
}

// imprime formatado seguindo o padrao tree uma avl
void AVL::imprimir()
{
    if( this->raiz != nullptr )
    {
        std::cout << "(" << this->raiz->elemento.getChave() << "," << this->raiz->elemento.getFerramenta() << ")" << std::endl;
        // apos imprimir a raiz, chama os respectivos metodos de impressao nas subarvore esquerda e direita
        // a chamada para a impressao da subarvore esquerda depende da existencia da subarvore direita
        imprimirEsq( " " , this->raiz->filhoEsquerda, this->raiz->filhoDireita==nullptr );
        imprimirDir( " " , this->raiz->filhoDireita );
    } else
        std::cout << "*arvore vazia*" << std::endl;
}

string AVL::levantamento(string nomeFerramenta) {
    string marca = "Marca não encontrada";
    short maiorPotencia = 0;
    unsigned menorChave = 0;

    levantamentoRecursivo(raiz, nomeFerramenta, marca, maiorPotencia, menorChave);

    return marca;
}

void AVL::levantamentoRecursivo(noh* atual, string nomeFerramenta, string& marca, short& maiorPotencia, unsigned& menorChave) {
    if (atual == NULL) {
        return;
    }

    // Verifica se a ferramenta atual tem o nome procurado
    if (atual->elemento.getFerramenta() == nomeFerramenta) {
        // Se for a ferramenta com maior potência encontrada até agora ou se a potência for a mesma, mas a chave for menor
        if (atual->elemento.getPotencia() > maiorPotencia || (atual->elemento.getPotencia() == maiorPotencia && atual->elemento.getChave() < menorChave)) {
            marca = atual->elemento.getMarca();
            maiorPotencia = atual->elemento.getPotencia();
            menorChave = atual->elemento.getChave();
        }
    }
    // Chama recursivamente para os filhos esquerdo e direito
    levantamentoRecursivo(atual->filhoEsquerda, nomeFerramenta, marca, maiorPotencia, menorChave);
    levantamentoRecursivo(atual->filhoDireita, nomeFerramenta, marca, maiorPotencia, menorChave);
}
    
    

int main() {
    AVL avl;
    objeto objAux;
    unsigned chave;
    string ferramenta;
    string marca;
    short potencia;

    char comando;    
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> chave>> ferramenta >> marca >> potencia;
                    
                    avl.inserir(chave, ferramenta, marca, potencia);
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
                case 'l': // Levantamento por ferramenta
                    cin >> ferramenta; // ler os dados para levantamento
                    marca = avl.levantamento(ferramenta);
                    cout << "Levantamento do ferramenta " << ferramenta << ": " << marca << endl;
                    break;
                case 'e': // Escrever tudo (em ordem)
                    cout << avl;
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
                        cout << "Elemento buscado: " << objAux << endl;
                    }
                    else{
                        cout << "Objeto não encontrado!" << endl;
                    }
                    break; 
                case 'n': // escrever nível a nível
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