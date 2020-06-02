/*  Inserimento, cancellazione e differenza di nodi in un albero BST.

    "Diciamo che un nodo x di un BST è bilanciato se il numero di nodi
    presenti nel suo sottoalbero sinistro è uguale al numero di nodi presenti
    nel suo sottoalbero destro".

    Questo programma stampa la differenza di nodi tra il sottoalbero sinistro
    e quello destro di un nodo.    
*/

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

    //metodi gettere e setter
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
    int iLeft;      //contatore nodi sottoalbero sinistro
    int iRight;     //contatore nodi sottoalbero destro
    int iSum;       //totale

    //metodi di servizio
    Node<T> * _insert(T value, Node<T> * pLastRoot){
        //caso base
        if(pLastRoot == NULL){
            pLastRoot = new Node<T>(value);
            return pLastRoot;
        }

        if(value > pLastRoot->getKey())
            pLastRoot->setRight(_insert(value, pLastRoot->getRight()));
        else 
            pLastRoot->setLeft(_insert(value, pLastRoot->getLeft()));
    }

    Node<T> * _canc(T value, Node<T> *pLastRoot){
        
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
            pLastRoot->setRight(_canc(value, pLastRoot->getRight()));
        else 
            pLastRoot->setLeft(_canc(value, pLastRoot->getLeft()));

    }

    Node<T> *_search(T value, Node<T> * pLastRoot){
        
        if(value == pLastRoot->getKey())
            return pLastRoot;
        if(value > pLastRoot->getKey())
            return _search(value, pLastRoot->getRight());
        else 
            return _search(value, pLastRoot->getLeft());
    }

    void _getSum(Node<T> * pLastRoot, int &iSum){

        if(pLastRoot == NULL)
            return;
        
        iSum++;
        _getSum(pLastRoot->getLeft(),iSum);
        _getSum(pLastRoot->getRight(),iSum);
    }

    public:
    BST(){
        pRoot = NULL;
        iLeft = iRight = iSum = 0;
    }

    //metodi innescanti
    void insert(T value){
        pRoot = _insert(value,pRoot);
    }

    void canc(T value){
        pRoot = _canc(value,pRoot);
    }

    Node<T> * search(T value){
        return _search(value,pRoot);
    }
    int getDifference(Node<T> * pNode){
        _getSum(pNode->getLeft(),iLeft);
        _getSum(pNode->getRight(),iRight);
        iSum = iLeft - iRight;
        if(iSum < 0) iSum *= -1;    //valore assoluto

        return iSum;
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
    outFile << pBST->getDifference(pBST->search(tmp)) << endl;
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