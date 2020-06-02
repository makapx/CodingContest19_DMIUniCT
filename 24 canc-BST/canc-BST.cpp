// Inserimento, cancellazione e visite in un albero BST
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

template<typename T>
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
            pLastRoot->setLeft(_insert(value,pLastRoot->getLeft()));

        return pLastRoot; //evita warning
    }

    // canc ricorsiva
    Node<T> * _canc(T value, Node<T> * pLastRoot){
        
        //caso 1, il valore e la key del nodo corrispondono
        if(value == pLastRoot->getKey()){

            //caso 1.1., il nodo ha entrambi i figli, si prende il minimo dei maggioranti
            if(pLastRoot->getLeft() && pLastRoot->getRight()){
                Node<T> * pTemp = pLastRoot->getRight();
                while(pTemp->getLeft())
                    pTemp = pTemp->getLeft();
                
                //pLastRoot ha la key del minimo dei maggioranti
                pLastRoot->setKey(pTemp->getKey());

                //si riscrive il braccio destro per eliminare il minimo dei maggioranti
                pLastRoot->setRight(_canc(pTemp->getKey(),pLastRoot->getRight()));
            }
            else if(pLastRoot->getRight() == NULL)  // caso 1.2, non ha figlio destro
                    pLastRoot = pLastRoot->getLeft();
                
            else    //caso 1.3, non ha figlio sinistro o non li ha entrambi
                pLastRoot = pLastRoot->getRight();
            return pLastRoot;
        }

        //caso 2, ricerca del valore da cancellare nel sottoalbero di destra
        if(value > pLastRoot->getKey())
            pLastRoot->setRight(_canc(value,pLastRoot->getRight()));
        //caso 3, ricerca del valore da cancellare nel sottoalbero di sinistra
        else
            pLastRoot->setLeft(_canc(value,pLastRoot->getLeft()));

        return pLastRoot; //evita warning
    }
    
    //metodi ricorsivi delle visite
    void _preorder(Node<T> * pLastRoot, ofstream &outFile){
        //caso base
        if(pLastRoot == NULL)
            return;
        
        outFile << pLastRoot->getKey() << " ";
        _preorder(pLastRoot->getLeft(),outFile);
        _preorder(pLastRoot->getRight(),outFile);
    }

    void _inorder(Node<T> * pLastRoot, ofstream &outFile){
        //caso base
        if(pLastRoot == NULL)
            return;
        
        _inorder(pLastRoot->getLeft(),outFile);
        outFile << pLastRoot->getKey() << " ";
        _inorder(pLastRoot->getRight(),outFile);
    }
    
    void _postorder(Node<T> * pLastRoot, ofstream &outFile){
        //caso base
        if(pLastRoot == NULL)
            return;
        
        _postorder(pLastRoot->getLeft(),outFile);
        _postorder(pLastRoot->getRight(),outFile);
        outFile << pLastRoot->getKey() <<  " ";
    }

    public:
    BST(){
        pRoot = NULL;
    }

    //metodo innescante insert
    void insert(T value){
        pRoot = _insert(value,pRoot);
    }

    //metodo innescante della canc
    void canc(T value){
        pRoot = _canc(value, pRoot);
    }

    //metodi innescanti per le visite preorder, inorder e postorder
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

    int iN;             //numero operazioni
    string strVisit;    //tipo di visita

    char cOpType;       //inserimento/cancellazione
    char cIgnore;       //buffer per ignorare gli altri caratteri

    T tmp;

    inFile >> iN;
    inFile >> strVisit;

    for(int i=0;i<iN; i++){
        inFile >> cOpType;

        inFile >> cIgnore;      //sia per l'ins che per la canc vanno ignorati
        inFile >> cIgnore;      //sicuramente 3 caratteri (un altro solo per la canc)
        inFile >> cIgnore;

        switch(cOpType){
            case 'i':   //inserimento
            inFile >> tmp;
            pBST->insert(tmp);
            break;

            case 'c': //cancellazione
            inFile >> cIgnore;
            inFile >> tmp;
            pBST->canc(tmp);
            break;
        }
    }

    switch (strVisit[1]) //check sul secondo carattere visto che il primo è uguale in pre e post
    {
        case 'r':   //pReorder
        pBST->preorder(outFile);
        break;

        case 'n':    //iNorder
        pBST->inorder(outFile);
        break;

        case 'o':    //pOstorder
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

            case 'd':
            parsing<double>(inFile,outFile);
            break;

            case 'c':
            parsing<char>(inFile,outFile);
            break;

            case 'b':
            parsing<bool>(inFile,outFile);
            break;
        }
    }
}