//  Insertion sort è un algoritmo di ordinamento in place, stabile, con complessità
//  O(n^2) nel caso medio e peggiore, O(n) in quello ottimo.
//  Questo esercizio stampa il numero di spostamenti effettuati dall'algoritmo nel corrispondente task

#include <iostream>
#include <fstream>
using namespace std;

int main(){

    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    int iN;
    while(inFile >> iN){
        int array[iN];
        for(int i=0;i<iN;i++)
            inFile >> array[i];
        
        //insertion sort
        int iKey, j, iCounter = 0;

        for(int i=0;i<iN;i++){
            iKey = array[i];
            j=i-1;
            while(j>=0 && array[j]>iKey){
                array[j+1] = array[j];
                j--;

                iCounter++;
            }
            array[j+1] = iKey;  
        }

        outFile << iCounter << endl;
    }
}