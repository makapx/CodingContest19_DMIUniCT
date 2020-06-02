//Implementazione di una coda attraverso due stack

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
        return * pKey;
    }

    Node<T> * getNext(){
        return pNext;
    }
};

template <typename T>
class Stack{
    private:
    Node<T> * pTop;

    public:
    Stack(){
        pTop = NULL;
    }

    void push(T value){
        if(pTop == NULL)
            pTop = new Node<T>(value);

        else{
            Node<T> *pTemp = new Node<T>(value);
            pTemp->setNext(pTop);
            pTop = pTemp;
        }
    }

    T pop(){
        T tmp = pTop->getKey();
        pTop = pTop->getNext();
        return tmp;
    }

    bool isEmpty(){
        return pTop == NULL;
    }

    void print(ofstream &outFile){
        Node<T> * pTemp = pTop;
        while(pTemp){
            outFile << pTemp->getKey()<< " ";
            pTemp = pTemp->getNext();
        }
    }
};

template <typename T>
class Queue{
    private:
    Stack<T> *pStack1;
    Stack<T> *pStack2;

    public:
    Queue(){
        pStack1 = new Stack<T>();
        pStack2 = new Stack<T>();
    }

    void enqueue(T value){
        pStack1->push(value);   //i valori vengono inseriti nel primo stack
    }

    void dequeue(){
        while(!(pStack1->isEmpty())){       //sposta i valori dal primo al secondo stack
            T tmp = pStack1->pop();
            pStack2->push(tmp);
        }

        pStack2->pop();             //estrai il valore dal secondo stack

        while(!(pStack2->isEmpty())){   //rimetti a posto
            T tmp = pStack2->pop();
            pStack1->push(tmp);
        }
    }

    void print(ofstream &outFile){

        while(!(pStack1->isEmpty())){   //sposta i valori
            T tmp = pStack1->pop();
            pStack2->push(tmp);
        }

        pStack2->print(outFile);        //chiama la print sul secondo stack
        outFile<<endl;
    }
};

template <typename T>
void parsing(ifstream &inFile, ofstream &outFile){

    Queue<T> * pQueue = new Queue<T>();

    int iN;
    char cOpType;
    string strIgnore;
    T tmp;

    inFile >> iN;
    for(int i=0;i<iN;i++){
        inFile >> cOpType;

        switch(cOpType){
            case 'i':       //enqueue
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