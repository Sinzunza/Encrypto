#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <cmath>

using namespace std;

vector <unsigned long long int> primeNumbers = {2};
unsigned long long int N;
unsigned long long int phiN;
unsigned long long int E;
unsigned long long int D;

//creates list of prime numbers all the way up to numberBound
void increasePrimeNumbers(unsigned long long int numberBound){
    bool isCurrentNumberPrime = true;
    for(unsigned long long int currentNumber = primeNumbers.back() + 1; currentNumber <= numberBound; currentNumber++){
        for(unsigned long long int j = 0; j < primeNumbers.size(); j++){
            if(currentNumber % primeNumbers.at(j) == 0){
                isCurrentNumberPrime = false;
                break;
            }
        }
        if(isCurrentNumberPrime){
            primeNumbers.push_back(currentNumber);
        }
        isCurrentNumberPrime = true;
    }
}

bool isPrime(unsigned long long int number){
    if(number > primeNumbers.back()){
        increasePrimeNumbers(number);
        if(number == primeNumbers.back()){
            return true;
        }
        else {
            return false;
        }
    }
    else {
        for(unsigned long long int i = 0; i < primeNumbers.size(); i++){
            if(number == primeNumbers.at(i)){
                return true;
            }
        }
        return false;
    }
}

unsigned long long int gcd (unsigned long long int a, unsigned long long int b){
    if(a == b){
        return a;
    }
    if(a < b){
        swap(a,b);
    }
    return gcd(a-b,b);
}

//simplifies modding numbers to the power of several dozen digits if needed
int modBigNumber(unsigned long long int number, unsigned long long int power, unsigned long long int modder){
    vector<unsigned long long int> leftOvers;
    while(power > 1){
        if(power % 2 == 1){
            leftOvers.push_back(number);
        }
        number *= number;
        number %= modder;
        power /= 2;
    }
    if(leftOvers.size() > 0){
        for(unsigned long long int i = 0; i < leftOvers.size(); i++){
            number *= leftOvers.at(i);
            number %= modder;
        }
    }
    return number;
}

bool isValidN(unsigned long long int number){
    unsigned long long int p;
    unsigned long long int q;
    unsigned long long int limit = sqrt(number);
    for(p = 2; p <= limit; p++){
        if(isPrime(p)){
            if(number % p == 0){
                q = number / p;
                if(p!= q && isPrime(q)){
                    N = number;
                    phiN = (p-1)*(q-1);
                    return true;
                }
            }
        }
    }
    return false;
}

bool isValidE(unsigned long long int number){
    if(number > 1 && number < phiN && gcd(number, phiN) == 1 && gcd(number, N) == 1){
        E = number;
        return true;
    }
    else {
        return false;
    }
}

void encrypt(string message){
    vector <unsigned long long int> encryptedMessage;
    unsigned long long int currentNum;
    for(unsigned long long int i = 0; i < message.size(); i++){
        currentNum = message.at(i);
        currentNum = modBigNumber(currentNum, E, N);
        encryptedMessage.push_back(currentNum);
    }
    //output encrypted message to file
    ofstream encryptedFileOut("encrypted.txt");
    for (unsigned long long int i = 0; i < encryptedMessage.size(); i++){
        encryptedFileOut << encryptedMessage.at(i) << " ";
    }
    encryptedFileOut.close();
}

unsigned long long int dBreaker(unsigned long long int eKey, unsigned long long int NKey){
    for(unsigned long long int i = 2; i < NKey; i++){
        if(eKey*i % phiN == 1){
            return i;
        }
    }
}

void decrypt(){
    D = dBreaker(E,N);
    ifstream encryptedFileIn("encrypted.txt");
    stringstream virtualStream;
    string fileString;
    unsigned long long int currentNum;
    char currentChar;
    string decryptedMessage;

    while(getline(encryptedFileIn,fileString)){
        virtualStream << fileString;
        while (virtualStream >> currentNum){
            currentNum = modBigNumber(currentNum, D, N);
            currentChar = currentNum;
            decryptedMessage.push_back(currentChar);
        }
        virtualStream.clear();
    }
    encryptedFileIn.close();
    //output decrypted messafe to file
    ofstream decryptedFileOut("decrypted.txt");
    decryptedFileOut << decryptedMessage;
    decryptedFileOut.close();
}

int main(){

    char choice;
    bool isValidChoice = false;
    unsigned long long int tempN = 1;
    unsigned long long int tempE = 1;
    string tempMessage;

    while(!isValidN(tempN)){
        cout << "Enter a number for n greater than 127: ";
        cin >> tempN;
        if (!isValidN(tempN)){
            cout << "Invalid n!" << endl;
        }
    }

    while(!isValidE(tempE)){
        cout << "Enter a number for e: ";
        cin >> tempE;
        if (!isValidE(tempE)){
            cout << "Invalid e!" << endl;
        }
    }

    while(!isValidChoice) {
        cout << "Enter 'e' for encryption or 'd' for decryption: ";
        cin >> choice;
        if(choice == 'e' || choice == 'd'){
            isValidChoice = true;
        }
        else {
            cout << "Invalid choice!" << endl;
        }

    }

    if(choice == 'e'){
        cout << "Type message to encrypt: ";
        fflush(stdin);
        getline(cin, tempMessage);
        encrypt(tempMessage);
        cout << "Message encrypted." << endl;
    }
    else if (choice == 'd'){
        decrypt();
        cout << "Message decrypted." << endl;
    }

    return 0;

}
