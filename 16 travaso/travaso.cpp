// Implementazione di una coda e di uno stack con i relativi metodi enqueue/push e dequeue/pop
// L'operazione di travaso consiste nell'estrarre i valori dallo stack e metterli nella coda

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

    Node<T> * getNext(){
        return pNext;
    }

    T getKey(){
        return *pKey;
    }
};

template<typename T>
class Stack{
    private:
    Node<T> * pTop;

    public:
    Stack(){
        pTop == NULL;
    }

    void push(T value){

        Node<T> * pTemp = new Node<T>(value);

        if(pTop == NULL)
            pTop = pTemp;

        else{
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
    Node<T> * pHead;
    Node<T> * pTail;

    public:
    Queue(){
        pHead = pTail = NULL;
    }

    void enqueue(T value){

        Node<T> * pTemp = new Node<T>(value);
        if(pHead == NULL)
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
    }

    void travasa(Stack<T> *pStack){
        while(!pStack->isEmpty()){
            T tmp = pStack->pop();
            enqueue(tmp);
        }   
    }
};

template <typename T>
void parsing(ifstream &inFile, ofstream &outFile){

    Queue<T> * pQueue = new Queue<T>();
    Stack<T> * pStack = new Stack<T>();

    int iN;         //numero operazioni
    inFile >> iN;

    T tmp;
    char cOpType;
    char cAux;
    string strIgnore;

    for(int i=0;i<iN;i++){
        inFile >> cOpType;
        inFile >> cAux;

        switch (cOpType)
        {
            case 'e':   //enqueue
            inFile >> tmp;
            pQueue->enqueue(tmp);
            break;

            case 'd':   //dequeue
            inFile >> strIgnore;
            pQueue->dequeue();
            break;

            case 'p': //push e pop
                if(cAux == 'o'){
                    inFile >> strIgnore;
                    pStack->pop();
                }

                else{
                    inFile >> tmp;
                    pStack->push(tmp);
                }
            break;

            case 't':   //travaso
            inFile >> strIgnore;
            pQueue->travasa(pStack);
            break;
        }
    }

    pQueue->print(outFile);
    pStack->print(outFile);
    outFile << endl;
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