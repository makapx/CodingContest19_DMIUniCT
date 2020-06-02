//Implementazione di un grafo attraverso liste di adiacenza
#include <iostream>
#include <fstream>
using namespace std;

template <typename T>
class Node{
    private:
    T * pKey;
    Node<T> * pNext;

    public:
    Node(T value){
        pKey = new T(value);
        pNext = NULL;
    }

    //metodi getter e setter
    void setNext(Node<T> * pNext){
        this->pNext = pNext;
    }

    T getKey(){
        return *pKey;
    }

    Node<T> * getNext(){
        return pNext;
    }
};

template <typename T>
class List{
    private:
    Node<T> * pHead;

    public:
    List(){
        pHead = NULL;   
    }

    void insert(T value){
        if(pHead == NULL)
            pHead = new Node<T>(value);
        else{
            Node<T> * pTemp = pHead;
            //fix perchè le key devono essere ordinate
            while(pTemp->getNext() && pTemp->getNext()->getKey() < value)
                pTemp = pTemp->getNext();

            Node<T> * pNode = new Node<T>(value);
            pNode->setNext(pTemp->getNext());
            pTemp->setNext(pNode);
        }
    }

    void print(ofstream &outFile){
        Node<T> * pTemp = pHead;

        outFile<<pTemp->getKey();
        pTemp = pTemp->getNext();

        while(pTemp){
            outFile<<" "<<pTemp->getKey();
            pTemp = pTemp->getNext();
        }
    }
};

template <typename T>
class Graph{
    private:
    T * pNodes;         //array di nodi
    List<T> * pList;    //array di liste
    int iCurrent;       //indice nodo corrente
    int iN;             //numero nodi

    public:
    Graph(int iN){
        this->iN = iN;
        iCurrent = 0;
        pNodes = new T[iN]();
        pList = new List<T>[iN]();
    }

    void insertNode(T value){
        pNodes[iCurrent] = value;
        iCurrent++;
    }

    //inizializza le liste di adiacenza con i valori di pnodes
    void initList(){
        for(int i=0;i<iN;i++)
            pList[i].insert(pNodes[i]); 
    }

    void selectionSort(){
        for(int i=0;i<iN-1;i++){
            int min = i;
            for(int j=i+1;j<iN;j++)
                if(pNodes[j] < pNodes[min])
                    min = j;
            if(min != i){
                T tmp = pNodes[i];
                pNodes[i] = pNodes[min];
                pNodes[min] = tmp;
            }
        }
    }

    int search(T value){
        for(int i=0;i<iN;i++)
            if(pNodes[i] == value)
                return i;
    }

    void insertEdge(T begin, T end){
        pList[search(begin)].insert(end);
    }

    void print(ofstream &outFile){
        for(int i=0;i<iN;i++){
            outFile << "(";
            pList[i].print(outFile);
            outFile << ") ";
        }
        outFile << endl;
    }
};

template <typename T>
void parsing(int iNodes, int iEdges, ifstream &inFile, ofstream &outFile){
    Graph<T> * pGraph = new Graph<T>(iNodes);

    T tmp,tmp2;
    char cIgnore;

    for(int i=0;i<iNodes;i++){
        inFile >> tmp;
        pGraph->insertNode(tmp);
    }

    pGraph->selectionSort();
    pGraph->initList();

    for(int i=0;i<iEdges;i++){
        inFile >> cIgnore;
        inFile >> tmp;
        //inFile >> cIgnore;
        inFile >> tmp2;
        inFile >> cIgnore;

        pGraph->insertEdge(tmp,tmp2);
    }

    pGraph->print(outFile);
}

int main(){
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    int iNodes;
    int iEdges;
    string strType;

    while(inFile >> iNodes){
        inFile >> iEdges;
        inFile >> strType;

        switch(strType[0]){
            case 'i':
            parsing<int>(iNodes,iEdges,inFile,outFile);
            break;

            case 'c':
            parsing<char>(iNodes,iEdges,inFile,outFile);
            break;

            case 'd':
            parsing<double>(iNodes,iEdges,inFile,outFile);
            break;
        }
    }

}