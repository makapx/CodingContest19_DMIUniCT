// Inserimento, cancellazione e peso di un nodo in un albero BST
// Il peso di un nodo è la somma di tutte le key dei nodi contenuti nel suo sottoalbero
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

        return pLastRoot;
    }

    //canc ricorsiva
    Node<T> * _canc(T value, Node<T> * pLastRoot){
        //il valore e la key corrispondono
        if(pLastRoot->getKey() == value){
            //prendo il minimo dei maggioranti
            if(pLastRoot->getLeft() && pLastRoot->getRight()){
                Node<T> * pTemp = pLastRoot->getRight();
                while(pTemp->getLeft())
                    pTemp = pTemp->getLeft();
                
                //sostituisco la key
                pLastRoot->setKey(pTemp->getKey());
                //riscrivo il braccio destro per eliminare la copia
                pLastRoot->setRight(_canc(pTemp->getKey(),pLastRoot->getRight()));

                return pLastRoot;
            }

            if(pLastRoot->getRight()==NULL)
                pLastRoot = pLastRoot->getLeft();
            else 
                pLastRoot = pLastRoot->getRight();

            return pLastRoot;
        }

        if(value > pLastRoot->getKey())
            pLastRoot->setRight(_canc(value,pLastRoot->getRight()));
        else
            pLastRoot->setLeft(_canc(value, pLastRoot->getLeft()));

        return pLastRoot;
    }

    //search ricorsiva
    Node<T> * _search(T value, Node<T> * pLastRoot){
        if(pLastRoot->getKey() == value)
            return pLastRoot;
        
        if(value > pLastRoot->getKey())
            return _search(value, pLastRoot->getRight());
        else
            return _search(value, pLastRoot->getLeft());
        
        return pLastRoot;
    }

    //metodo ricorsivo per il calcolo del peso, implementato in modo simile ad
    //una visita inorder
    void _getWeight(Node<T> * pLastRoot, T &tWeight){

        if(pLastRoot == NULL)
            return;
        
        _getWeight(pLastRoot->getLeft(),tWeight);
        tWeight += pLastRoot->getKey();
        _getWeight(pLastRoot->getRight(),tWeight);
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

    //metodo innescante search
    Node<T> * search(T value){
        return _search(value,pRoot);
    }

    //metodo innescante per il calcolo del peso
    T getWeight(Node<T> * pNode){
        T tWeight = 0;
        _getWeight(pNode, tWeight);
        return tWeight;
    }
};

template <typename T>
void parsing(ifstream &inFile, ofstream &outFile){

    BST<T> *pBST = new BST<T>();

    int iN;         //numero operazioni
    char cOpType;   //tipo operazione
    char cIgnore;   //buffer per ignorare i caratteri
    T tmpValue;

    inFile >> iN;

    for(int i=0;i<iN;i++){

        inFile >> cOpType;

        inFile >> cIgnore;
        inFile >> cIgnore;
        inFile >> cIgnore;

        switch(cOpType){
            case 'i':
            inFile >> tmpValue;
            pBST->insert(tmpValue);
            break;

            case 'c':
            inFile >> cIgnore;
            inFile >> tmpValue;
            pBST->canc(tmpValue);
            break;
        }
    }

    inFile >> tmpValue;
    outFile<<pBST->getWeight(pBST->search(tmpValue))<<endl;
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
