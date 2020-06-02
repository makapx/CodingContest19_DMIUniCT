//Esercizio sulle Torri di Hanoi.
//L'esercizio deve stampare il palo da cui il disco proviene e quello dove viene posto
//nella mossa indicata in input.
//Il primo valore in input è il numero dei dischi, il secondo la mossa di cui si
//vogliono conoscere i dettagli

#include <iostream>
#include <fstream>

using namespace std;

void hanoi(int iN, int from, int to, int aux, int iMove, int &iCount,ofstream &outFile){

    //primo check: il contatore delle mosse è maggiore o uguale della mossa da conoscere
    if(iCount >= iMove){
        //il check da fare ha sempre la stessa struttura
        if(iCount==iMove){
            iCount++;
            outFile << from << " "<<to<<endl;
            return;
        }
        return;
    }

    if(iN == 1){    //caso base di hanoi, un solo disco da muovere
        iCount++;

            if(iCount==iMove){
            iCount++;
            outFile << from << " "<<to<<endl;
            return;
            }

        return;
    }

    //FROM, AUX, TO
    hanoi(iN-1,from,aux,to,iMove,iCount,outFile);
        iCount++;   //incremento contatore fuori dal check
        if(iCount==iMove){
            iCount++;
            outFile << from << " "<<to<<endl;
            return;
        }
    //AUX, TO, FROM
    hanoi(iN-1,aux,to,from,iMove,iCount,outFile);

}

int main(){

    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    int iCount;     //contatore mosse
    int iN;             //numero dischi
    int iMove;          //numero mossa di cui si vogliono conoscere i dettagli

    while(inFile >> iN){
        iCount = 0;
        inFile >> iMove;

        hanoi(iN,1,3,2,iMove,iCount,outFile);
    }

}