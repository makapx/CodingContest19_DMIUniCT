// Inserimento, cancellazione e profondità di un nodo in un albero BST
// La profondità di un nodo è il numero di archi che lo distanzia dalla root.
// Corrisponde al livello del nodo.

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
        return *pKey;
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

    //canc ricorsivo
    Node<T> * _canc(T value, Node<T> * pLastRoot){
        if(pLastRoot->getKey() == value){
            if(pLastRoot->getLeft() && pLastRoot->getRight()){
                Node<T> * pTemp = pLastRoot->getRight();
                while(pTemp->getLeft())
                    pTemp = pTemp->getLeft();

                pLastRoot->setKey(pTemp->getKey());
                pLastRoot->setRight(_canc(pTemp->getKey(),pLastRoot->getRight()));
            }
            else if(pLastRoot->getRight() == NULL)
                pLastRoot = pLastRoot->getLeft();
            else
                pLastRoot = pLastRoot->getRight();

            return pLastRoot;
        }

        if(value > pLastRoot->getKey())
            pLastRoot->setRight(_canc(value,pLastRoot->getRight()));
        else 
            pLastRoot->setLeft(_canc(value, pLastRoot->getLeft()));
        
        return pLastRoot; //evita warning
    }

    void _depth(T value, Node<T> * pLastRoot, int &iDepth){

        if(pLastRoot == NULL)
            return;
        
        iDepth++;

        if(value == pLastRoot->getKey())
        return;

        if(value < pLastRoot->getKey())
            _depth(value, pLastRoot->getLeft(), iDepth);
        else
            _depth(value, pLastRoot->getRight(), iDepth);
    }

    public:
    BST(){
        pRoot = NULL;
    }

    //metodo innescante inserimento
    void insert(T value){
        pRoot = _insert(value, pRoot);
    }

    //metodo innescante cancellazione
    void canc(T value){
        pRoot = _canc(value, pRoot);
    }

    //metodo innescante profondità
    int depth(T value){
        int iDepth = 0;
        _depth(value, pRoot,iDepth);
        return iDepth;
    }
};

template <typename T>
void parsing(ifstream &inFile, ofstream &outFile){
    
    BST<T> *pBST = new BST<T>();

    int iN;
    char cOpType;
    char cIgnore;
    T tmp;

    inFile >> iN;

    for(int i=0; i<iN;i++){
        inFile >> cOpType;

        inFile >> cIgnore;
        inFile >> cIgnore;
        inFile >> cIgnore;

        switch(cOpType){
            case 'i':
            inFile >> tmp;
            pBST->insert(tmp);
            break;

            case 'c':
            inFile >> cIgnore;
            inFile >> tmp;
            pBST->canc(tmp);
            break;
        }
    }

    inFile >> tmp;
    outFile << pBST->depth(tmp)-1<< endl; //stampa depth -1 
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