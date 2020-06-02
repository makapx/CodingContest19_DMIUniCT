// Implementazione di un grafo attraverso matrice di adiacenza
// L'esercizio chiede di stampare il numero di cicli nel grafo

#include <iostream>
#include <fstream>

using namespace std;

template<typename T>
class Graph{
    private:
    T * pNodes;             //array di nodi
    bool ** adjMatrix;      //matrice di adiacenza
    int iCurrent;           //indice nodo corrente
    int iN;                 //numero nodi
    int * pColor;           //array colori visite, 0 = non visitato, 1 =visita iniziata, 2 = visita finita
    int iCycleCounter;      //contatore cicli

    void _DFS(int index){

        pColor[index] = 1;  //la visita è iniziata

        for(int i=0;i<iN;i++){
            if(adjMatrix[index][i] && pColor[i] == 1)
                iCycleCounter++;    //c'è un ciclo

            if(adjMatrix[index][i] && pColor[i] == 0)
                _DFS(i);           //chiama la dfs sul nodo non visitato
        }

        pColor[index] = 2; //la visita è finita

    }

    public:
    Graph(int iN){
        pNodes = new T[iN]();
        adjMatrix = new bool * [iN]();
        for(int i=0;i<iN;i++)
            adjMatrix[i] = new bool[iN]();
        this->iN = iN;
        iCycleCounter = 0;
        pColor = new int [iN]();
        iCurrent = 0;
    }

    void insertNode(T value){
        pNodes[iCurrent] = value;
        iCurrent++;

        if(iCurrent == iN)
            selectionSort();
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

    void insertEdge(T begin, T end){
        adjMatrix[search(begin)][search(end)] = true;
    }

    int search(T value){
        for(int i=0;i<iN;i++)
            if(pNodes[i] == value)
                return i;
    }

    void DFS(){
        for(int i=0;i<iN;i++)
            if(pColor[i]==0)  //se il nodo non è stato visitato chiama la dfs  
                _DFS(i);
    }

    int printCycle(){
        return iCycleCounter;
    }
};

template<typename T>
void parsing(int iNodes, int iEdges, ifstream &inFile, ofstream &outFile){

    Graph<T> * pGraph = new Graph<T>(iNodes);

    T tmp;
    T tmp2;
    char cIgnore;

    for(int i=0;i<iNodes;i++){
        inFile >> tmp;
        pGraph->insertNode(tmp);
    }

    for(int i=0;i<iEdges;i++){
        inFile >> cIgnore;
        inFile >> tmp;
        //inFile >> cIgnore; solo input esempio
        inFile >> tmp2;
        inFile >> cIgnore;
        
        pGraph->insertEdge(tmp,tmp2);
    }

    pGraph->DFS();
    outFile << pGraph->printCycle()<<endl;
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

        switch (strType[0])
        {
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