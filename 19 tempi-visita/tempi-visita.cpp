// Implementazione di un grafo attraverso matrice di adiacenza
// L'esercizio chiede di stampare per ogni nodo i tempi della visita DFS
#include <iostream>
#include <fstream>
using namespace std;

template <typename T>
class Graph{
    private:
    T * pNodes;         //array nodi
    bool ** adjMatrix;  //matrice di adiacenza
    int iCurrent;       //indice nodo corrente
    int iN;             //numero nodi
    bool * isVisited;   //array visite
    int * pBegin;       //array tempi di inizio visita
    int * pEnd;         //array tempi di fine visita
    int iVisit;         //contatore tempo di visita

    void _DFS(int index){
        
        isVisited[index] = true;    //il nodo viene visitato

        pBegin[index] = iVisit;     //registra il suo inizio visita
        iVisit++;                   //incrementa il tempo

        for(int i=0;i<iN;i++)
            if(adjMatrix[index][i] == true && !isVisited[i])
                _DFS(i);

        pEnd[index] = iVisit;       //registra il tempo di fine visita
        iVisit++;                   //incrementa il tempo
    }

    public:
    Graph(int iN){
        pNodes = new T[iN]();

        adjMatrix = new bool * [iN]();
        for(int i=0;i<iN;i++)
            adjMatrix[i] = new bool[iN]();

        iCurrent = 0;
        isVisited = new bool[iN]();
        this->iN = iN;

        pBegin = new int[iN]();
        pEnd = new int [iN]();
        iVisit = 0;
    }

    void insertNode(T value){
        pNodes[iCurrent] = value;
        iCurrent++;

        if(iCurrent == iN)
            selectionSort();
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
            if(!isVisited[i])
                _DFS(i);
    }

    void print(ofstream &outFile){
        for(int i=0;i<iN;i++){
            outFile<<"("<<pNodes[i]<<" "<<pBegin[i]<<" "<<pEnd[i]<<") ";
        }
        outFile<<endl;
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
};

template <typename T>
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
        //inFile >> cIgnore; solo input d'esempio
        inFile >> tmp2;
        inFile >> cIgnore;

        pGraph->insertEdge(tmp,tmp2);
    }

    pGraph->DFS();
    pGraph->print(outFile);
}

int main(){
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    int iNodes, iEdges;
    string strType;

    while(inFile >> iNodes){
        inFile >> iEdges;
        inFile >> strType;

        switch(strType[0]){
            case 'i':
            parsing<int>(iNodes,iEdges,inFile,outFile);
            break;

            case 'd':
            parsing<double>(iNodes,iEdges,inFile,outFile);
            break;

            case 'c':
            parsing<char>(iNodes,iEdges,inFile,outFile);
            break;
        }
    }

}