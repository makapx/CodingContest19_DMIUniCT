//Inserimento, cancellazione e common ancestor
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
    
    //metodi di servizio
    Node<T> * _insert(T value, Node<T> * pLastRoot){
        if(pLastRoot == NULL){
            pLastRoot = new Node<T>(value);
            return pLastRoot;
        }

        if(value > pLastRoot->getKey())
            pLastRoot->setRight(_insert(value,pLastRoot->getRight()));
        else 
            pLastRoot->setLeft(_insert(value,pLastRoot->getLeft()));
    }

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
            pLastRoot->setLeft(_canc(value,pLastRoot->getLeft()));
    }

    T _commonAncestor(T fValue, T sValue, Node<T> * pLastRoot){
        
        if(pLastRoot == NULL)
            return NULL;

        if(pLastRoot->getKey() > fValue && pLastRoot->getKey() > sValue)
        return _commonAncestor(fValue,sValue,pLastRoot->getLeft());

        else if(pLastRoot->getKey() < fValue && pLastRoot->getKey() < sValue)
        return _commonAncestor(fValue,sValue,pLastRoot->getRight());

        else
            return pLastRoot->getKey();
        
    }
    public:
    BST(){
        pRoot = NULL;
    }

    //metodi innescanti
    void insert(T value){
        pRoot = _insert(value,pRoot);
    }

    void canc(T value){
        pRoot = _canc(value,pRoot);
    }

    T commonAncestor(T fValue, T sValue){
       return _commonAncestor(fValue,sValue,pRoot);
    }

};

template <typename T>
void parsing(ifstream &inFile, ofstream &outFile){

    BST<T> * pBST = new BST<T>();

    int iN;
    char cOpType;
    char cIgnore;
    T tmpValue;

    T tmpFirst;
    T tmpSecond;

    inFile >> iN;
    for(int i=0;i<iN;i++){
        inFile >> cOpType;

        inFile >> cIgnore;
        inFile >> cIgnore;
        inFile >> cIgnore;

        switch (cOpType)
        {
            case 'i':   //inserimento
            inFile >> tmpValue;
            pBST->insert(tmpValue);
            break;

            case 'c':   //cancellazione
            inFile >> cIgnore;
            inFile >> tmpValue;
            pBST->canc(tmpValue);
            break;
        }
    }

    inFile >> tmpFirst;
    inFile >> tmpSecond;

    outFile << pBST->commonAncestor(tmpFirst,tmpSecond) << endl;
    
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
