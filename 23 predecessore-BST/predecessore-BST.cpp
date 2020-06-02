// Inserimento, cancellazione e predecessore in un albero BST
// Il predecessore di un nodo è quel nodo la cui key è immediatamente più piccola
// (o in alcuni casi uguali)

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
        pKey = new T(value);
        pLeft = pRight = NULL;
        this->pParent = pParent;    //il parent del nodo è settato nel momento della creazione
    }

    //metodi getter e setter

    void setKey(T value){       //utilizzato nella cancellazione
        *pKey = value;
    }

    void setLeft(Node<T> * pNode){
        pLeft = pNode;
    }

    void setRight(Node<T> * pNode){
        pRight = pNode;
    }

    void setParent(Node<T> * pNode){    //utilizzato nella cancellazione
        pParent = pNode;
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

    Node<T> * getParent(){
        return pParent;
    }
};

template <typename T>
class BST{
    private:
    Node<T> * pRoot;

    //insert ricorsivo
    Node<T> * _insert(T value, Node<T> * pLastRoot, Node<T> * pLastParent){
        //caso base
        if(pLastRoot == NULL){
            pLastRoot = new Node<T>(value,pLastParent);
            return pLastRoot;
        }

        //si passa la root corrente come last parent del figlio sinistro e destro
        if(value > pLastRoot->getKey())
            pLastRoot->setRight(_insert(value, pLastRoot->getRight(),pLastRoot));
        else
            pLastRoot->setLeft(_insert(value, pLastRoot->getLeft(),pLastRoot));

        return pLastRoot; //evita warning
    }

    //canc ricorsiva
    Node<T> * _canc(T value, Node<T> * pLastRoot){

        //caso 1: la key del nodo e il valore corrispondo
        if(pLastRoot->getKey() == value){
            
            //caso 1.1: il nodo ha entrambi i figli
            if(pLastRoot->getLeft() && pLastRoot->getRight()){
                //si prende il minimo dei maggioranti
                Node<T> * pTemp = pLastRoot->getRight();
                while(pTemp->getLeft())
                    pTemp = pTemp->getLeft();
                
                //si sostituisce a pLastRoot la key del minimo dei maggioranti
                pLastRoot->setKey(pTemp->getKey());

                //si riscrive il braccio destro per eliminare la copia del minimo
                // dei maggioranti
                pLastRoot->setRight(_canc(pTemp->getKey(),pLastRoot->getRight()));
            }
            //caso 1.2: il nodo non ha il figlio destro
            else if(pLastRoot->getRight() == NULL){
                    if(pLastRoot->getLeft())
                        pLastRoot->getLeft()->setParent(pLastRoot->getParent());

                pLastRoot = pLastRoot->getLeft();
            }
            //caso 1.3: il nodo non ha il figlio sinistro
            else{
                if(pLastRoot->getRight())
                    pLastRoot->getRight()->setParent(pLastRoot->getParent());

                pLastRoot = pLastRoot->getRight();
            }

            //NB: visto che i figli hanno come parent il nodo che si sta eliminando
            //bisogna spostare il parent al parent del nodo che sta per essere eliminato
            //cioè al "nonno"

            return pLastRoot;
        }

        //caso 2: il valore è maggiore della key nodo
            if(value > pLastRoot->getKey())
                pLastRoot->setRight(_canc(value, pLastRoot->getRight()));

        //caso 3: il valore è minore della key del nodo
            else
                pLastRoot->setLeft(_canc(value, pLastRoot->getLeft()));

        return pLastRoot; //evita warning
    }

    //search ricorsiva
    Node<T> * _search(T value, Node<T> * pLastRoot){

        //caso base
        if(pLastRoot->getKey() == value)
            return pLastRoot;
        
        if(value > pLastRoot->getKey())
            return _search(value, pLastRoot->getRight());
        else
            return _search(value, pLastRoot->getLeft());

        return pLastRoot; //evita warning
    }

    Node<T> * _getPrev(Node<T> * pLastRoot){

        Node<T> * pTemp = NULL;
        
        //se ha il figlio sinistro si prende il massimo dei minoranti
        if(pLastRoot->getLeft()){
            pTemp = pLastRoot->getLeft();
            while(pTemp->getRight())
                pTemp = pTemp->getRight();
        }
        //altrimenti si risale il parent fino a trovare quello con la key più piccola
        else{
            pTemp = pLastRoot->getParent();
            while(pTemp && pLastRoot->getKey() < pTemp->getKey())
                pTemp = pTemp->getParent();
        }
        return pTemp;
    }

    public:
    BST(){
        pRoot = NULL;
    }

    //metodo innescante dell'insert
    void insert(T value){
        pRoot = _insert(value, pRoot, NULL); //alla prima chiamata il parent è NULL
    }

    //metodo innescante della canc
    void canc(T value){
        pRoot = _canc(value, pRoot);
    }

    //metodo innescante della search
    Node<T> * search(T value){
        return _search(value, pRoot);
    }

    Node<T> * getPrev(Node<T> * pNode){
        return _getPrev(pNode);
    }
};

template <typename T>
void parsing(ifstream &inFile, ofstream &outFile){

    BST<T> * pBST = new BST<T>();

    int iN;         //numero di operazioni inserimento/cancellazione
    int iPrev;      //numero di nodi di cui stampare il predecessore
    char cOpType;   //tipo di operazione ins/canc
    char cIgnore;   //buffer per ignorare i caratteri
    T tmpValue;

    inFile >> iN;
    inFile >> iPrev;

    for(int i=0; i<iN;i++){
        inFile >> cOpType;

        inFile >> cIgnore;      //bisogna sempre ignorare 3 caratteri
        inFile >> cIgnore;
        inFile >> cIgnore;

        switch(cOpType){
            case 'i':   //inserimento
            inFile >> tmpValue;
            pBST->insert(tmpValue);
            break;

            case 'c':   //cancellazione
            inFile >> cIgnore;  //bisogna ignorare un altro carattere
            inFile >> tmpValue;
            pBST->canc(tmpValue);
            break;
        }
    }

    for(int i=0; i<iPrev;i++){
        inFile >> tmpValue;
        
        Node<T> * pTemp = pBST->getPrev(pBST->search(tmpValue));
        if(pTemp == NULL)
            outFile << "-1 ";   //stampa -1 se non c'è predecessore
        else
            outFile << pTemp->getKey() << " ";
    }

    outFile << endl;
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