//Inserimento in un albero BST

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

    void _preorder(Node<T> *pLastRoot,ofstream &outFile){
        if(pLastRoot==NULL)
            return;
        
        outFile << pLastRoot->getKey() << " ";
        _preorder(pLastRoot->getLeft(),outFile);
        _preorder(pLastRoot->getRight(),outFile);
    }

    void _inorder(Node<T> *pLastRoot,ofstream &outFile){
        if(pLastRoot==NULL)
            return;
        
        _inorder(pLastRoot->getLeft(),outFile);
        outFile << pLastRoot->getKey() << " ";
        _inorder(pLastRoot->getRight(),outFile);
    }

    void _postorder(Node<T> *pLastRoot,ofstream &outFile){
        if(pLastRoot==NULL)
            return;
        
        _postorder(pLastRoot->getLeft(),outFile);
        _postorder(pLastRoot->getRight(),outFile);
        outFile << pLastRoot->getKey() << " ";
    }

    public:
    BST(){
        pRoot=NULL;
    }

    //metodo innescante insert
    void insert(T value){
        pRoot = _insert(value, pRoot);
    }

    //metodi innescanti visite
    void preorder(ofstream &outFile){
        _preorder(pRoot,outFile);
        outFile << endl;
    }

    void inorder(ofstream &outFile){
        _inorder(pRoot,outFile);
        outFile << endl;
    }

    void postorder(ofstream &outFile){
        _postorder(pRoot,outFile);
        outFile << endl;
    }
};

template <typename T>
void parsing(ifstream &inFile, ofstream &outFile){

    BST<T> * pBST = new BST<T>();
    string strVisit;
    int iN;
    T tmp;

    inFile >> iN;
    inFile >> strVisit;

    for(int i=0;i<iN;i++){
        inFile >> tmp;
        pBST->insert(tmp);
    }

    switch (strVisit[1])
    {
        case 'r': //pReorder
        pBST->preorder(outFile);
        break;
        
        case 'n':    //iNorder
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