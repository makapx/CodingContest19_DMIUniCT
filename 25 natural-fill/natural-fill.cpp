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

    Node<T> * getLeft(){
        return pLeft;
    }
    
    Node<T> * getRight(){
        return pRight;
    }

    T getKey(){
        return * pKey;
    }
};

template<typename T>
class BST{
    private:
    Node<T> * pRoot;
    int index;

    Node<T> * _insert(T value, Node<T> * pLastRoot){

        if(pLastRoot == NULL){
            pLastRoot = new Node<T>(value);
            return pLastRoot;
        }

        if(value > pLastRoot->getKey())
            pLastRoot->setRight(_insert(value, pLastRoot->getRight()));
        else 
            pLastRoot->setLeft(_insert(value,pLastRoot->getLeft()));
    }

    void _naturalFill(T * pNatural, Node<T> * pLastRoot){

        if(pLastRoot == NULL)
            return;
        
        _naturalFill(pNatural,pLastRoot->getLeft());
        pLastRoot->setKey(pNatural[index]);
        index++;
        _naturalFill(pNatural,pLastRoot->getRight());
    }

    void _postorder(Node<T> * pLastRoot, ofstream &outFile){
        if(pLastRoot == NULL)
            return;
        
        _postorder(pLastRoot->getLeft(),outFile);
        _postorder(pLastRoot->getRight(),outFile);
        outFile << pLastRoot->getKey()<<" ";
    }

    public:
    BST(){
        pRoot = NULL;
        index = 0;
    }

    void insert(T value){
        pRoot = _insert(value, pRoot);
    }

    void naturalFill(T * pNatural){
        _naturalFill(pNatural, pRoot);
    }

    void postorder(ofstream &outFile){
        _postorder(pRoot,outFile);
        outFile << endl;
    }
};

template <typename T>
void parsing(ifstream &inFile, ofstream &outFile){

    BST<T> *pBST = new BST<T>();
    int iN;
    T tmp;
    inFile >> iN;
    T * pNatural = new T[iN]();

    for(int i=0;i<iN;i++){
        inFile >> tmp;
        pBST->insert(tmp);
    }

    for(int i=0;i<iN;i++)
        inFile >> pNatural[i];
    
    pBST->naturalFill(pNatural);
    pBST->postorder(outFile);
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