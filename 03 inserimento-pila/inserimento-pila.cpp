//  La pila/stack è una struttura dati lineare di tipo LIFO (Last in first out)
//  In questo esercizio sono implementate solo l'inserimento/push e la stampa
//  Lo stack è implementato attraverso una lista linkata

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

        Node<T> * pTemp = new Node<T>(value);

        if(pTop == NULL)
            pTop = pTemp;   //primo inserimento
        else{
            pTemp->setNext(pTop);       //il nodo che si sta per inserire punta al nodo precedentemente inserito
            pTop = pTemp;               //ora il nodo è inserito in testa 
        }
    }

    void print(ofstream &outFile){
        while(pTop){
            outFile << pTop->getKey()<<" ";
            pTop = pTop->getNext();
        }
        outFile << endl;
    }
};

template <typename T>
void parsing(ifstream &inFile, ofstream &outFile){
    int iN;
    inFile >> iN;

    Stack<T> * pStack = new Stack<T>();

    T tmp;
    for(int i=0;i<iN;i++){
        inFile >> tmp;
        pStack->push(tmp);
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

            case 'b':
            parsing<bool>(inFile,outFile);
            break;

            case 'd':
            parsing<double>(inFile,outFile);
            break;

            case 'c':
            parsing<char>(inFile,outFile);
            break;
        }
    }
}