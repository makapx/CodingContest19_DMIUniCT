//  Implementazioni di push, pop e print in uno stack
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
class Stack{
    private:
    Node<T> * pTop;

    public:
    Stack(){
        pTop = NULL;
    }

    void push(T value){
        Node<T> * pTemp = new Node<T>(value);

        if(pTop == NULL)
            pTop = pTemp;   //primo inserimento
        else{
            pTemp->setNext(pTop);   //il nuovo nodo punta a quello che precedentemente stava in cima
            pTop = pTemp;           //il nodo viene inserito in cima allo stack
        }
    }

    void pop(){
        pTop = pTop->getNext();
    }

    void print(ofstream &outFile){
        Node<T> *pTemp = pTop;
        while(pTemp){
            outFile << pTemp ->getKey()<< " ";
            pTemp = pTemp->getNext();
        }
        outFile << endl;
    }
};

template <typename T>
void parsing(ifstream &inFile, ofstream &outFile){

    Stack<T> * pStack = new Stack<T>();

    T tmp;
    int iN;
    char cOpType;
    string strIgnore;

    inFile >> iN;
    for(int i=0;i<iN;i++){
        inFile >> cOpType;
        switch(cOpType){
            case 'i':
            inFile >> tmp;
            pStack->push(tmp);
            break;

            case 'p':
            inFile >> strIgnore;
            pStack->pop();
            break;
        }
    }

    pStack->print(outFile); 
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

            case 'b':
            parsing<bool>(inFile,outFile);
            break;

            case 'c':
            parsing<char>(inFile,outFile);
            break;
        }
    }
}