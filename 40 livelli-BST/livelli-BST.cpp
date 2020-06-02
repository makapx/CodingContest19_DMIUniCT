//  LIVELLI BST
//  Come livello BST
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

    void setLeft(Node<T> * pNode){
        pLeft = pNode;
    }

    void setRight(Node<T> * pNode){
        pRight = pNode;
    }

    Node<T> * getLeft(){
        return pLeft;
    }

    Node<T> * getRight(){
        return pRight;
    }

    T getKey(){
        return *pKey;
    }

    void setKey(T value){
        *pKey = value;
    }
};

template<typename T>
class BST{
    private:
    Node<T> * pRoot;
    int iCurrentHeight;
    int iMaxHeight;

    T * pArray;

    Node<T> * _insert(T value, Node<T> * pLastRoot){

        if(pLastRoot == NULL){
            pLastRoot = new Node<T>(value);
            return pLastRoot;
        }

        if(value > pLastRoot->getKey())
            pLastRoot->setRight(_insert(value,pLastRoot->getRight()));
        
        else
            pLastRoot->setLeft(_insert(value,pLastRoot->getLeft()));
        
        return pLastRoot;
    }

    Node<T> * _canc(T value, Node<T> * pLastRoot){
        if(value == pLastRoot->getKey()){
            
            Node<T> * pTemp = pLastRoot;
            if(pLastRoot->getLeft() && pLastRoot->getRight()){
                pTemp = pLastRoot->getRight();

                while(pTemp->getLeft())
                    pTemp = pTemp->getLeft();

                pLastRoot->setKey(pTemp->getKey());
                pLastRoot->setRight(_canc(pTemp->getKey(),pLastRoot->getRight()));
            }

            else if(pLastRoot->getRight() == NULL)
                pLastRoot = pLastRoot->getLeft();

            else pLastRoot = pLastRoot->getRight();

            return pLastRoot;
        }

        if(value > pLastRoot->getKey())
            pLastRoot->setRight(_canc(value,pLastRoot->getRight()));
        
        else
            pLastRoot->setLeft(_canc(value,pLastRoot->getLeft()));
        
        return pLastRoot;
    }

    void _altezza(Node<T> *pLastRoot){

        if(pLastRoot == NULL)
            return;

        pArray[iCurrentHeight]++;
        iCurrentHeight++;
        if(iCurrentHeight > iMaxHeight)
            iMaxHeight = iCurrentHeight;

        _altezza(pLastRoot->getLeft());
        _altezza(pLastRoot->getRight());

        iCurrentHeight--;

    }

    public:
    BST(){
        pRoot = NULL;
        iCurrentHeight = 0;
        iMaxHeight = 0;
        pArray = new T [100]();

    }

    void insert(T value){
        pRoot = _insert(value, pRoot);
    }

    void canc(T value){
        pRoot = _canc(value, pRoot);
    }

    void altezza(ofstream &outFile){
        iCurrentHeight = 0;
        iMaxHeight = 0;

        _altezza(pRoot);
        //return iMaxHeight;

        outFile << iMaxHeight-1 << " ";

        for(int i=0;i<iMaxHeight;i++){
            outFile << pArray[i]<< " ";
        }
        outFile << endl;
    }
};

template<typename T>
void parsing(ifstream &inFile, ofstream &outFile, int iN){

    BST<T> * pBST = new BST<T>();

    char c_op;
    char c_ignore;
    T tmpValue;

    for(int i=0;i<iN;i++){
        inFile >> c_op;

        switch (c_op)
        {
        case 'i':
            for(int i=0;i<3;i++)
                inFile >> c_ignore;
            inFile >> tmpValue;
            pBST->insert(tmpValue);
        break;
        
        case 'c':
            for(int i=0;i<4;i++)
                inFile >> c_ignore;
            inFile >> tmpValue;
            pBST->canc(tmpValue);
        break;
        }
    }
    
    pBST->altezza(outFile);
}

int main(){

    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    string strType;
    int iN;

    while(inFile >> strType){
        inFile >> iN;

        switch (strType[0])
        {
            case 'i':
            parsing<int>(inFile,outFile,iN);
            break;

            case 'd':
            parsing<double>(inFile,outFile,iN);
            break;
        }
    }

}