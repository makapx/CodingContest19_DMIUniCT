// Implementazione di un grafo attraverso matrice di adiacenza

#include <iostream>
#include <fstream>
using namespace std;

template <typename T>
class Graph{
    private:
    T * pNodes;             //array di nodi
    bool ** adjMatrix;      //matrice di adiacenza
    int iCurrent;           //contatore nodo corrente
    int iN;                 //numero nodi

    public:
    Graph(int iN){
        this->iN = iN;
        pNodes = new T[iN]();
        adjMatrix = new bool * [iN]();
        for(int i=0;i<iN;i++)
            adjMatrix[i] = new bool[iN]();

        iCurrent = 0;
    }

    void insertNode(T value){
        pNodes[iCurrent] = value;
        iCurrent++;
    }

    void insertEdge(T begin, T end){
        adjMatrix[search(begin)][search(end)] = true;
    }

    int search(T value){
        for(int i=0;i<iN;i++)
            if(pNodes[i] == value)
                return i;
    }

    void print(ofstream &outFile){
        for(int i=0;i<iN;i++){
            outFile<<"(";
            outFile<<pNodes[i];

            for(int j=0;j<iN;j++)
                if(adjMatrix[i][j] == true)
                    outFile <<" "<<pNodes[j];
            
            outFile << ") ";
        }
        outFile << endl;
    }

    void sorting(){     //selection sort
        for(int i=0;i<iN-1;i++){
           int min = i;
           for(int j=i+1;j<iN;j++)
            if(pNodes[j]<pNodes[min])
                min = j;
            
            if(min !=i){
                T tmp = pNodes[i];
                pNodes[i] = pNodes[min];
                pNodes[min] = tmp;
            }

        }
    }
};

template<typename T>
void parsing(int iNodes,int iEdges,ifstream &inFile, ofstream &outFile){
    Graph<T> * pGraph = new Graph<T>(iNodes);
    T tmp;
    T tmp2;
    char cIgnore;

    for(int i=0;i<iNodes;i++){
        inFile >> tmp;
        pGraph->insertNode(tmp);
    }

    pGraph->sorting();

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