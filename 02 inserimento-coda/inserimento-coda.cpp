//  Una coda/queue è una struttura dati lineare di tipo FIFO (First In First Out)
//  In questo esercizio sono implementate solo l'operazione di inserimento/enqueue
//  e la stampa.
//  La coda è implementata attraverso una lista linkata

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
class Queue{
    private:
    Node<T> * pHead;
    Node<T> * pTail;

    public:
    Queue(){
        pHead = pTail = NULL;
    }

    void enqueue(T value){
        
        Node<T> * pTemp = new Node<T>(value);
        if(pHead == NULL)  //primo inserimento/coda vuota
            pHead = pTail = pTemp;

        else{
            pTail->setNext(pTemp);      //l'elemento viene inserito alla fine, dopo l'ultimo
            pTail = pTail->getNext();   //l'elemento inserito ora è la nuova coda       
        }
    }

    void print(ofstream &outFile){
        Node<T> * pTemp = pHead;
        while(pTemp){
            outFile << pTemp->getKey()<<" ";
            pTemp = pTemp->getNext();
        }
        outFile << endl;
    }
};

template <typename T>
void parsing(ifstream &inFile, ofstream &outFile){

    int iN;
    T tmp;

    Queue<T> * pQueue = new Queue<T>();

    inFile >> iN;

    for(int i=0;i<iN;i++){
        inFile >> tmp;
        pQueue->enqueue(tmp);
    }

    pQueue->print(outFile);
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