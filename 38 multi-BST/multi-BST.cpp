// Albero BST con molteplicità
// Se un valore viene inserito più volte consecutivamente
// anzichè inserire un nuovo nodo di volta in volta bisogna aumentare la molteplicità,
// analogamente nella cancellazione vengono diminuite le molteplicità del valore
// e il nodo viene cancellato solo quando rimane l'ultima occorrenza.
// I valori vengono poi stampati con visite preorder, inorder o postorder.

#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class Node{
    private:
    T * pKey;
    int iMul;               //contatore molteplicità
    Node<T> * pLeft;
    Node<T> * pRight;

    public:
    Node(T value){
        pKey = new T(value);
        pLeft = pRight = NULL;
        iMul = 1;   //alla creazione del nodo viene inizializzata la prima occorrenza
    }

    //metodi getter e setter
    void setKey(T value){
        *pKey = value;
    }

    void setLeft(Node<T> *pNode){
        pLeft = pNode;
    }

    void setRight(Node<T> *pNode){
        pRight = pNode;
    }

    T getKey(){
        return *pKey;
    }

    Node<T> * getLeft(){
        return pLeft;
    }

    Node<T> * getRight(){
        return pRight;
    }
    
    //metodi gestione molteplicità
    void incrMul(){
        iMul++;
    }

    void decrMul(){
        iMul--;
    }

    int getMul(){
        return iMul;
    }

};

template <typename T>
class BST{
    private:
    Node<T> * pRoot;

    //insert ricorsivo
    Node<T> * _insert(T value, Node<T> * pLastRoot){

        if(pLastRoot == NULL){
            pLastRoot = new Node<T>(value);
            return pLastRoot;
        }

        //se il valore inserito è uguale alla key della root incremententa la molteplicità
        if(pLastRoot->getKey() == value){
            pLastRoot->incrMul();
        }

        if (value > pLastRoot->getKey())
            pLastRoot->setRight(_insert(value,pLastRoot->getRight()));
        //NB: se prima l'insert sul braccio sinistro era gestito da un else
        //ora bisogna porre che sia strettamente minore altrimenti inserirebbe nuovi nodi
        //quando riscontra molteplicità
        if(value < pLastRoot->getKey())
            pLastRoot->setLeft(_insert(value, pLastRoot->getLeft()));
        
        return pLastRoot;   //evita warning
    }

    //canc ricorsiva
    Node<T> * _canc(T value, Node<T> * pLastRoot){
        //caso 1: la key e il valore sono uguali
        if(pLastRoot->getKey() == value){
            //se è rimasta l'ultima occorrenza del valore cancella il nodo che lo 
            //attraverso la classica procedura, altrimenti decrementa al molteplicità
            //(vedi else giù)
            if(pLastRoot->getMul() <= 1){
                //caso 1.1: se ha entrambi i figli prendi il minimo dei maggioranti
                if(pLastRoot->getLeft() && pLastRoot->getRight()){
                Node<T> * pTemp = pLastRoot->getRight();
                while(pTemp->getLeft())
                    pTemp = pTemp->getLeft();
                //sostituisci la key
                pLastRoot->setKey(pTemp->getKey());
                //riscrivi il braccio destro per togliere la copia del minimo dei maggioranti
                pLastRoot->setRight(_canc(pTemp->getKey(),pLastRoot->getRight()));
                }

                //caso 1.2: non ha il figlio destro
                else if(pLastRoot->getRight() == NULL)
                    pLastRoot = pLastRoot->getLeft();

                else
                //caso 1.3: non ha il figlio sinistro o non li ha entrambi
                    pLastRoot = pLastRoot->getRight();
            }

            //ci sono più occorrenze quindi decrementa il numero di molteplicità
            else{
            pLastRoot->decrMul();
            }

            return pLastRoot;
        }
        
        //caso 2: valore maggiore della key
        if(value > pLastRoot->getKey())
            pLastRoot->setRight(_canc(value,pLastRoot->getRight()));
        //caso 3: valore minore della key
        else 
            pLastRoot->setLeft(_canc(value, pLastRoot->getLeft()));
        
        return pLastRoot;   //evita warning
    }

    //metodi ricorsivi per le visite
    //viene utilizzato un ciclo for per stampare le molteplicità
    void _preorder(Node<T> * pLastRoot, ofstream &outFile){

        if(pLastRoot==NULL)
            return;
        
        for(int i=0;i<pLastRoot->getMul();i++)
            outFile << pLastRoot->getKey() << " ";
        _preorder(pLastRoot->getLeft(),outFile);
        _preorder(pLastRoot->getRight(),outFile);
    }

    void _inorder(Node<T> * pLastRoot, ofstream &outFile){

        if(pLastRoot==NULL)
            return;
        
        _inorder(pLastRoot->getLeft(),outFile);
        for(int i=0;i<pLastRoot->getMul();i++)
            outFile << pLastRoot->getKey() << " ";
        _inorder(pLastRoot->getRight(),outFile);
    }

    void _postorder(Node<T> * pLastRoot, ofstream &outFile){

        if(pLastRoot==NULL)
            return;
        
        _postorder(pLastRoot->getLeft(),outFile);
        _postorder(pLastRoot->getRight(),outFile);
        for(int i=0;i<pLastRoot->getMul();i++)
            outFile << pLastRoot->getKey() << " ";
    }


    public:
    BST(){
        pRoot = NULL;
    }

    //metodo innescante insert
    void insert(T value){
        pRoot = _insert(value, pRoot);
    }
    
    //metodo innescante canc
    void canc(T value){
        pRoot = _canc(value, pRoot);
    }

    //metodi innescanti per le visite
    void preorder(ofstream &outFile){
        _preorder(pRoot,outFile);
        outFile << endl;
    }

    void inorder(ofstream &outFile){
        _inorder(pRoot,outFile);
        outFile << endl;
    }

    void postorder(ofstream &outFile){
        _postorder(pRoot, outFile);
        outFile << endl;
    }
};

template <typename T>
void parsing(ifstream &inFile, ofstream &outFile){

    BST<T> * pBST = new BST<T>();

    int iN;             //numero operazioni
    char cOpType;       //tipo operazione inserimento/cancellazione 
    char cIgnore;       //buffer per ignorare i caratteri
    string strVisit;    //tipo di visita da applicare
    T tmpValue;

    inFile >> iN;
    inFile >> strVisit;

    for(int i=0;i<iN;i++){
        inFile >> cOpType;

        inFile >> cIgnore;      //vengono ignorati sicuramente 3 caratteri
        inFile >> cIgnore;
        inFile >> cIgnore;
        
        switch(cOpType){
            case 'i':
            inFile >> tmpValue;
            pBST->insert(tmpValue);
            break;

            case 'c':
            inFile >> cIgnore;      //si ignora un altro carattere per la canc
            inFile >> tmpValue;
            pBST->canc(tmpValue);
            break;
        }
    }

    switch(strVisit[1]){   //check sul secondo carattere visto che in pre e post il primo è uguale
        case 'r': //pReorder
        pBST->preorder(outFile);
        break;
        case 'n': //iNorder
        pBST->inorder(outFile);
        break;
        case 'o': //pOstorder
        pBST->postorder(outFile);
        break;
    }
}

int main(){

    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    string strType;

    while(inFile >> strType){
        switch(strType[0]){
            case 'i':
            parsing<int>(inFile,outFile);
            break;

            case 'd':
            parsing<double>(inFile,outFile);
            break;

            case 'b':
            parsing<bool>(inFile,outFile);
            break;

            case 'c':
            parsing<char>(inFile,outFile);
            break;

        }
    }
}