// Inserimento, cancellazione e conto delle foglie in un albero BST
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class Node{
    private:
    T * pKey;
    Node<T> * pLeft;
    Node<T> * pRight;

    public:
    Node(T value){
        pKey = new T(value);
        pLeft = pRight = NULL;
    }

    //metodi getter e setter
    void setKey(T value){
        *pKey = value;
    }
    
    void setLeft(Node<T> * pNode){
        pLeft = pNode;
    }

    void setRight(Node<T> * pNode){
        pRight = pNode;
    }

    T getKey(){
        return * pKey;
    }

    Node<T> * getLeft(){
        return pLeft;
    }

    Node<T> * getRight(){
        return pRight;
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

        if(value > pLastRoot->getKey())
            pLastRoot->setRight(_insert(value, pLastRoot->getRight()));
        else 
            pLastRoot->setLeft(_insert(value, pLastRoot->getLeft()));
        
        return pLastRoot; //evita warning
    }

    //canc ricorsiva
    Node<T> * _canc(T value, Node<T> * pLastRoot){
        //caso 1: il valore e la key corrispondono
        if(pLastRoot->getKey() == value){
            //caso 1.1: il nodo ha entrambi i figli
            if(pLastRoot->getLeft() && pLastRoot->getRight()){
                //si prende il minimo dei maggioranti
                Node<T> * pTemp = pLastRoot->getRight();
                while(pTemp->getLeft())
                    pTemp = pTemp->getLeft();

                //sostituisco la key
                pLastRoot->setKey(pTemp->getKey());
                //riscrivo il braccio destro per eliminare la copia
                pLastRoot->setRight(_canc(pTemp->getKey(),pLastRoot->getRight()));
            }
            //caso 1.2: il nodo non ha il figlio destro
            else if(pLastRoot->getRight() == NULL)
                pLastRoot = pLastRoot->getLeft();
            else 
            //caso 1.3: non ha il figlio sinistro o non li ha entrambi
                pLastRoot = pLastRoot->getRight();

            return pLastRoot;
        }

        if(value > pLastRoot->getKey())
            pLastRoot->setRight(_canc(value, pLastRoot->getRight()));
        else 
            pLastRoot->setLeft(_canc(value, pLastRoot->getLeft()));
        
        return pLastRoot; //evita warning
    }

    //metodo ricorsivo per il conto delle foglie
    void _leafCount(Node<T> * pLastRoot, int &iCount){

        if(pLastRoot == NULL)
            return;
        
        //un nodo per essere una foglia non deve avere ne il figlio destro ne quello sinistro
        if(pLastRoot->getLeft() == NULL && pLastRoot->getRight() == NULL)
            iCount++;

        _leafCount(pLastRoot->getLeft(),iCount);
        _leafCount(pLastRoot->getRight(), iCount);

    }
    public:
    BST(){
        pRoot = NULL;
    }

    //metodo innescante dell'insert
    void insert(T value){
        pRoot = _insert(value, pRoot);
    }

    //metodo innescante canc
    void canc(T value){
        pRoot = _canc(value,pRoot);
    }

    //metodo innescante contatore foglie
    int leafCount(){
        int iCount = 0;
        _leafCount(pRoot, iCount);
        return iCount;
    }
};

template <typename T>
void parsing(ifstream &inFile, ofstream &outFile){
    
    BST<T> * pBST = new BST<T>();

    int iN;         //numero operazioni
    char cOpType;   //tipo operazione
    char cIgnore;   //buffer per ignorare i caratteri
    T tmp;

    inFile >> iN;

    for(int i=0;i<iN;i++){
        inFile >> cOpType;

        inFile >> cIgnore;  //bisogna ignorare sempre almeno 3 caratteri
        inFile >> cIgnore;
        inFile >> cIgnore;

        switch(cOpType){
            case 'i':   //insert
            inFile >> tmp;
            pBST->insert(tmp);
            break;

            case 'c':   //canc
            inFile >> cIgnore;  //si ignora un altro carattere
            inFile >> tmp;
            pBST->canc(tmp);
            break;
        }
    }

    outFile << pBST->leafCount()<<endl;
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
        }

    }
}