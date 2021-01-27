#include "../header/primes.h"

primes::primes()
{
    primeNumbers = {2};
}

vector <unsigned long long int> primes::getPrimeNumbers(){
    return primeNumbers;
}

void primes::increasePrimeNumbers(unsigned long long int numberBound){
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

bool primes::isPrime(unsigned long long int number, primes primeObj){
    if(number > primeObj.getPrimeNumbers().back()){
        primeObj.increasePrimeNumbers(number);
        if(number == primeObj.getPrimeNumbers().back()){
            return true;
        }
        else {
            return false;
        }
    }
    else {
        for(unsigned long long int i = 0; i < primeObj.getPrimeNumbers().size(); i++){
            if(number == primeObj.getPrimeNumbers().at(i)){
                return true;
            }
        }
        return false;
    }
}
