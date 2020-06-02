//  Implementazione di enqueue, dequeue e print
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

        if(pHead == NULL)   //primo inserimento
            pHead = pTail = pTemp;
        else{
            pTail->setNext(pTemp);
            pTail = pTemp;
        }
    }

    void dequeue(){
        pHead = pHead->getNext();
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
    Queue<T> * pQueue = new Queue<T>();

    int iN;
    inFile >> iN;
    T tmp;
    string strIgnore;
    char cOpType;

    for(int i=0;i<iN;i++){
        inFile >> cOpType;
        switch (cOpType)
        {
            case 'i':
            inFile >> tmp;
            pQueue->enqueue(tmp);
            break;

            case 'd':
            inFile >> strIgnore;
            pQueue->dequeue();
            break;
        }
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