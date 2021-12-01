#ifndef RSACRYPTO_H
#define RSACRYPTO_H

#include <iostream>
#include "primes.h"

class rsaCrypto {
    
    public:
        rsaCrypto();
        void setN(unsigned long long int N);
        void setE(unsigned long long int E);
        bool isValidN(unsigned long long int number);
        bool isValidE(unsigned long long int number);
        void encrypt(string fileIn);
        void decrypt(string fileOut);

    protected:

    private:
        unsigned long long int dBreaker(unsigned long long int eKey, unsigned long long int NKey);
        primes primeObj;
        unsigned long long int N;
        unsigned long long int E;
        unsigned long long int phiN;
};

#endif // RSACRYPTO_H
