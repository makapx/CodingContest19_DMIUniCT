//Il merge sort è un algoritmo di ordinamento di tipo divide et impera
//L'approccio divide et impera consiste nel dividere il problema (l'array da ordinare)
//in sottoproblemi via via più semplici (divisione in sottoarray fino ad avere singoli
//elementi che sono quindi già ordinati) per poi rifonderli
//La complessità temporale di merge sort è sempre O(n log n)

//L'esercizio chiede di stampare il numero di chiamate ricorsive sull'array
//eccezion fatta per gli array di dimensione 1, che sono già ordinati
//Si può quindi anche evitare di fare il merge e stampare solo il numero di chiamate ricosive

#include <iostream>
#include <fstream>

using namespace std;

//void merge(array,iLeft,iCenter,iRight){}

void mergesort(int * array, int iLeft, int iRight, int &iSum){

    if(iLeft < iRight){
        int iCenter = (iLeft+iRight)/2;
        mergesort(array,iLeft,iCenter,iSum);
        mergesort(array,iCenter+1,iRight,iSum);

        iSum += array[iLeft];
        //merge(array,iLeft,iCenter,iRight);
    }
}

int main(){
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    int iN;
    while(inFile >>iN){
        int * array = new int[iN];
        for(int i=0;i<iN;i++)
            inFile >> array[i];
        
        int iSum = 0; //numero chiamate ricorsive
        mergesort(array,0, iN-1,iSum);
        outFile << iSum << endl;  
    }
}