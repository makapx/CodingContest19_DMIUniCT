// L'altezza di un nodo è il numero di archi del percorso da esso alla foglia che si
// trova più in profondità. L'altezza dell'albero corrisponde all'altezza della root.
// Questo esercizio chiede di calcolare l'altezza dell'albero.
// Sono implementati sia l'inserimento che la cancellazione

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
            pLastRoot->setRight(_insert(value,pLastRoot->getRight()));
        else
            pLastRoot->setLeft(_insert(value, pLastRoot->getLeft()));

        return pLastRoot; //evita warning
    }

    //canc ricorsiva
    Node<T> * _canc(T value, Node<T> * pLastRoot){
        //caso 1, il valore è uguale alla key
        if(pLastRoot->getKey() == value){
            //caso 1.1: la root ha entrambi i figli
            if(pLastRoot->getLeft() && pLastRoot->getRight()){
                //prendo il minimo dei maggioranti
                Node<T> * pTemp = pLastRoot->getRight();
                while(pTemp->getLeft())
                    pTemp = pTemp->getLeft();

                //sostituisco la key 
                pLastRoot->setKey(pTemp->getKey());
                //riscrivo il braccio destro per eliminare l'altra copia
                pLastRoot->setRight(_canc(pTemp->getKey(),pLastRoot->getRight()));
            }
            //caso 1.2: non ha il figlio destro
            else if(pLastRoot->getRight() == NULL)
                pLastRoot = pLastRoot->getLeft();
            else
            //caso 1.3: non ha il figlio sinistro o non li ha entrambi
                pLastRoot = pLastRoot->getRight();

            return pLastRoot;
        }

         if(value > pLastRoot->getKey())
            pLastRoot->setRight(_canc(value,pLastRoot->getRight()));
        else
            pLastRoot->setLeft(_canc(value, pLastRoot->getLeft()));

        return pLastRoot; //evita warning
    }
    
    // getHeight ricorsivo
    void _getHeight(Node<T> * pLastRoot, int &iCurrentHeight, int &iMaxHeight){

        //caso base
        if(pLastRoot == NULL)
            return;
        
        iCurrentHeight++;
        if(iCurrentHeight > iMaxHeight)
            iMaxHeight = iCurrentHeight;

        _getHeight(pLastRoot->getLeft(), iCurrentHeight,iMaxHeight);
        _getHeight(pLastRoot->getRight(),iCurrentHeight, iMaxHeight);

        //si decrementa l'altezza corrente perchè si risale
        iCurrentHeight--;
    }

    public:
    BST(){
        pRoot = NULL;
    }

    //metodo innescante dell'insert
    void insert(T value){
        pRoot = _insert(value, pRoot);
    }

    //metodo innescante della canc
    void canc(T value){
        pRoot = _canc(value, pRoot);
    }

    //metodo innescante getHeight
    int getHeight(){
        int iCurrentHeight = 0;
        int iMaxHeight = 0;
        _getHeight(pRoot, iCurrentHeight, iMaxHeight);
        return iMaxHeight;
    }
};

template <typename T>
void parsing(ifstream &inFile, ofstream &outFile){

    int iN; //numero operazioni inserimento/cancellazione

    BST<T> * pBST = new BST<T>();

    inFile >> iN;

    char cOpType;       //tipo operazione
    char cIgnore;       //buffer per ignorare i caratteri
    T tmp;

    for(int i=0; i<iN; i++){
        inFile >> cOpType;

        inFile >> cIgnore;
        inFile >> cIgnore;
        inFile >> cIgnore;

        switch(cOpType){
            case 'i':       //insert
            inFile >> tmp;
            pBST->insert(tmp);
            break;

            case 'c':       //canc
            inFile >> cIgnore;
            inFile >> tmp;
            pBST->canc(tmp);
            break;
        }
    }

    outFile << pBST->getHeight() << endl;
}

int main(){
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    string strType;

    while(inFile >> strType){
        switch (strType[0])
        {
            case 'i':
            parsing<int>(inFile,outFile);
            break;

            case 'd':
            parsing<double>(inFile,outFile);
            break;
        }
    }
}