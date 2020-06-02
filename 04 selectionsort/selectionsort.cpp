// Il selection sort è un algoritmo di ordinamento in place con complessità n^2
// Questo esercizio stampa la somma delle differenze degli gli indici, accumulata
// ogni qual volta si fa lo swap.

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

        int iCount = 0;
        //selection sort
        for(int i=0;i<iN-1;i++){
            int min = i;
            for(int j=i+1;j<iN;j++)
                if(array[j] < array[min])
                    min = j;
                    
            if(min != i){
                int tmp = array[i];
                array[i] = array[min];
                array[min] = tmp;

                //iCount += min-i;
            }
        }
        outFile << iCount<<endl;
    }
}