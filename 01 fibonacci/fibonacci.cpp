//  Ritorna il Fibonacci di un numero
//  Soluzione iterativa

#include <iostream>
#include <fstream>

using namespace std;

unsigned long long int fibonacci(int iN){

    if(iN == 1)  return 1;

    unsigned long long int a = 0, b = 1, c;

    for(int i=2;i<=iN;i++){
        c = a+b;
        a = b;
        b = c;
    }
    return c;
}

int main(){
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    int iN;
    while(inFile >> iN)
        outFile << fibonacci(iN)<<endl;
}