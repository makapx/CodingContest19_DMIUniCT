#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class Graph{
    private:
    T * pNodes;
    bool ** adjMatrix;
    int iCurrent;
    int iCurrentTopol;
    T * pTopol;
    bool * isVisited;
    int iN;

    void _DFS(int index){

        isVisited[index] = true;

        for(int i=0;i<iN;i++)
            if(adjMatrix[index][i] && !isVisited[i])
                _DFS(i);
        
        pTopol[iCurrentTopol] = pNodes[index];
        iCurrentTopol++;
    }

    public:
    Graph(int iN){
        this->iN = iN;
        pNodes = new T[iN]();
        adjMatrix = new bool *[iN]();
        for(int i=0;i<iN;i++)
            adjMatrix[i] = new bool[iN]();
        iCurrent = 0;
        iCurrentTopol = 0;

        isVisited = new bool[iN]();
        pTopol = new T[iN]();
    }

    void insertNode(T value){
        pNodes[iCurrent] = value;
        iCurrent++;

        if(iCurrent == iN)
            insertionSort();
    }

    void insertionSort(){
        int j;
        T key;
        for(int i=0;i<iN;i++){
            key = pNodes[i];
            j = i-1;

            while(j>= 0 && pNodes[j]>key){
                pNodes[j+1] = pNodes[j];
                j--;  
            }
            pNodes[j+1] = key;
        }
    }

    int search(T value){
        for(int i=0;i<iN;i++)
            if(pNodes[i] == value)
                return i;
    }

    void insertEdge(T begin, T end){
        adjMatrix[search(begin)][search(end)] = true;
    }

    void DFS(){
        for(int i=0;i<iN;i++)
            if(!isVisited[i])
                _DFS(i);
    }

    void printTopo(ofstream &outFile){
        for(int i=iN-1;i>=0;i--)
            outFile<<pTopol[i]<<" ";
        outFile << endl;
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
        inFile >> cIgnore;
        inFile >> tmp2;
        inFile >> cIgnore;

        pGraph->insertEdge(tmp,tmp2);
    }

    pGraph->DFS();
    pGraph->printTopo(outFile);

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