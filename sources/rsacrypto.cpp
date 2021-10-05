#include "..\headers\rsaCrypto.h"
#include "..\headers\mathFncts.h"
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

rsaCrypto::rsaCrypto()
{
    N = 0;
    E = 0;
    phiN = 0;
}

void rsaCrypto::setN(unsigned long long int N){
    this->N = N;
}

void rsaCrypto::setE(unsigned long long int E){
    this->E = E;
}

bool rsaCrypto::isValidN(unsigned long long int number){
    unsigned long long int p;
    unsigned long long int q;
    unsigned long long int limit = sqrt(number);
    for(p = 2; p <= limit; p++){
        if(primeObj.isPrime(p, primeObj)){
            if(number % p == 0){
                q = number / p;
                if(p!= q && primeObj.isPrime(q, primeObj)){
                    phiN = (p-1)*(q-1);
                    return true;
                }
            }
        }
    }
    return false;
}

bool rsaCrypto::isValidE(unsigned long long int number){
    if(number > 1 && number < phiN && mathFncts().gcd(number, phiN) == 1 && mathFncts().gcd(number, N) == 1){
        return true;
    }
    else {
        return false;
    }
}

void rsaCrypto::encrypt(string fileIn){
    // set input and output files
    ifstream fileInStream(fileIn);
    ofstream fileOutStream("encrypted.txt");
    unsigned long long int currentNum;
    string fileString;
    
    // extract from input file, one line at a time and then a char at a time, and encrypt each character
    while(getline(fileInStream,fileString)){
        fileString += "\n";
        for(unsigned long long int i = 0; i < fileString.size(); i++){
        currentNum = mathFncts().modBigNumber(fileString.at(i), E, N);
        fileOutStream << currentNum << " ";
        }
    }
    fileInStream.close();
    fileOutStream.close();
}

unsigned long long int rsaCrypto::dBreaker(unsigned long long int eKey, unsigned long long int NKey){
    for(unsigned long long int i = 2; i < NKey; i++){
        if(eKey*i % phiN == 1){
            return i;
        }
    }
    return 0;
}

void rsaCrypto::decrypt(string fileIn){
    unsigned long long int D = dBreaker(E,N);
    // set input and output files
    ifstream fileInStream(fileIn);
    ofstream fileOutStream("decrypted.txt");
    unsigned long long int currentNum;
    stringstream virtualStream;
    string fileString;
    char currentChar;
    
    // extract from input file, one line at a time and then an encrytped value at a time, and decrypt each value
    while(getline(fileInStream,fileString)){
        virtualStream << fileString;
        while (virtualStream >> currentNum){
            currentChar = mathFncts().modBigNumber(currentNum, D, N);
            fileOutStream << currentChar;
        }
        virtualStream.clear();
    }
    fileInStream.close();
    fileOutStream.close();
}
