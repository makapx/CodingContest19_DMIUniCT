#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class Node{
    private:
    T * pKey;
    Node<T> * pLeft;
    Node<T> * pRight;
    Node<T> * pParent;

    public:
    Node(T value, Node<T> * pParent){
        this->pParent = pParent;
        pKey = new T(value);
        pLeft = pRight = NULL;
    }

    //metodi getter e setter
    void setKey(T value){
        *pKey = value;
    }

    void setParent(Node<T> * pParent){
        this->pParent = pParent;
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

    Node<T> * getParent(){
        return pParent;
    }

    Node<T> * getLeft(){
        return pLeft;
    }

    Node<T> * getRight(){
        return pRight;
    }
};

template<typename T>
class BST{
    private:
    Node<T> * pRoot;

    Node<T> * _insert(T value, Node<T> * pLastRoot, Node<T> * pLastParent){
        if(pLastRoot == NULL){  //caso base
            pLastRoot = new Node<T>(value, pLastParent);
            return pLastRoot;
        }

        if(value > pLastRoot->getKey())
            pLastRoot->setRight(_insert(value,pLastRoot->getRight(),pLastRoot));
        else 
            pLastRoot->setLeft(_insert(value,pLastRoot->getLeft(),pLastRoot));
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
            else if(pLastRoot->getRight() == NULL){
                if(pLastRoot->getLeft())
                   pLastRoot->getLeft()->setParent(pLastRoot->getParent());

                pLastRoot = pLastRoot->getLeft();
            }
            else {
                if(pLastRoot->getRight())
                    pLastRoot->getRight()->setParent(pLastRoot->getParent());
                
                pLastRoot = pLastRoot->getRight();
            }

            return pLastRoot;
        }

        if(value > pLastRoot->getKey())
            pLastRoot->setRight(_canc(value,pLastRoot->getRight()));
        else 
            pLastRoot->setLeft(_canc(value,pLastRoot->getLeft()));
    }

    void _inorder(Node<T> * pLastRoot){

        if(pLastRoot == NULL){
            return;
        }

        _inorder(pLastRoot->getLeft());
        cout << pLastRoot->getKey()<<" ";
        _inorder(pLastRoot->getRight());
    }

    Node<T> * _search(T value, Node<T> * pLastRoot){
        if(pLastRoot->getKey() == value)
            return pLastRoot;
        
        if(value > pLastRoot->getKey())
            return _search(value, pLastRoot->getRight());
        else
            return _search(value, pLastRoot->getLeft());
    }

    Node<T> * _getNext(Node<T> * pLastRoot){

        Node<T> * pTemp = NULL;
        if(pLastRoot->getRight()){
            pTemp = pLastRoot->getRight();
            while(pTemp->getLeft())
                pTemp = pTemp->getLeft();
        
            return pTemp;
        }
        else{
            pTemp = pLastRoot->getParent();
            while(pTemp && pTemp->getKey() < pLastRoot->getKey())
                pTemp = pTemp->getParent();

            return pTemp;
        }
    }
    public:
    BST(){
        pRoot = NULL;
    }

    //metodi innescanti
    void insert(T value){
        pRoot = _insert(value,pRoot, NULL);
    }

    void canc(T value){
        pRoot = _canc(value, pRoot);
    }

    void inorder(){
        _inorder(pRoot);
    }

    Node<T> * search(T value){
        return _search(value, pRoot);
    }

    Node<T> * getNext(Node<T> * pNode){
        return _getNext(pNode);
    }
};


template<typename T>
void parsing(ifstream &inFile, ofstream &outFile){

    BST<T> * pBST = new BST<T>();

    int iN;
    T tmp;
    char cOpType;
    char cIgnore;
    int iSucc;

    inFile >> iN;
    inFile >> iSucc;

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

    
    for(int i=0;i<iSucc;i++){
        inFile >> tmp;

        Node<T> * pTemp = pBST->getNext(pBST->search(tmp));

        if(pTemp)
            outFile << pTemp->getKey()<<" ";
        else
            outFile << "-1 ";
    }
    outFile<<endl;
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

           case 'c':
           parsing<char>(inFile,outFile);
           break;

           case 'd':
           parsing<double>(inFile,outFile);
           break;

           case 'b':
           parsing<bool>(inFile,outFile);
           break;
       }
   }
}