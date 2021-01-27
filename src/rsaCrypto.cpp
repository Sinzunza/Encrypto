#include "../header/rsaCrypto.h"
#include "../header/mathFncts.h"
#include <cmath>
#include <fstream>
#include <sstream>

#include <iostream>
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

void rsaCrypto::encrypt(){
    ifstream decryptedFileIn("decrypted.txt");
    string fileString;
    string message;

    while(getline(decryptedFileIn,fileString)){
        message += fileString;
    }
    decryptedFileIn.close();

    vector <unsigned long long int> encryptedMessage;
    unsigned long long int currentNum;
    for(unsigned long long int i = 0; i < message.size(); i++){
        currentNum = message.at(i);
        currentNum = mathFncts().modBigNumber(currentNum, E, N);
        encryptedMessage.push_back(currentNum);
    }
    //output encrypted message to file
    ofstream encryptedFileOut("encrypted.txt");
    for (unsigned long long int i = 0; i < encryptedMessage.size(); i++){
        encryptedFileOut << encryptedMessage.at(i) << " ";
    }
    encryptedFileOut.close();
}

unsigned long long int rsaCrypto::dBreaker(unsigned long long int eKey, unsigned long long int NKey){
    for(unsigned long long int i = 2; i < NKey; i++){
        if(eKey*i % phiN == 1){
            return i;
        }
    }
}

void rsaCrypto::decrypt(){
    unsigned long long int D = dBreaker(E,N);
    ifstream encryptedFileIn("encrypted.txt");
    stringstream virtualStream;
    string fileString;
    unsigned long long int currentNum;
    char currentChar;
    string decryptedMessage;

    while(getline(encryptedFileIn,fileString)){
        virtualStream << fileString;
        while (virtualStream >> currentNum){
            currentNum = mathFncts().modBigNumber(currentNum, D, N);
            currentChar = currentNum;
            decryptedMessage.push_back(currentChar);
        }
        virtualStream.clear();
    }
    encryptedFileIn.close();
    //output decrypted message to file
    ofstream decryptedFileOut("decrypted.txt");
    decryptedFileOut << decryptedMessage;
    decryptedFileOut.close();
}
