#ifndef PRIMES_H
#define PRIMES_H

#include <vector>

using namespace std;

class primes {
    
    public:
        primes();
        vector <unsigned long long int> getPrimeNumbers();
        bool isPrime(unsigned long long int number, primes primesObj);


    protected:

    private:
        //creates list of prime numbers all the way up to numberBound
        void increasePrimeNumbers(unsigned long long int numberBound);
        vector <unsigned long long int> primeNumbers;
};

#endif // PRIMES_H
