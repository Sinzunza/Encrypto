#include "../header/mathFncts.h"
#include <vector>

using namespace std;

mathFncts::mathFncts()
{
    //ctor
}

unsigned long long int mathFncts::gcd (unsigned long long int a, unsigned long long int b){
    if(a == b){
        return a;
    }
    if(a < b){
        swap(a,b);
    }
    return gcd(a-b,b);
}

//simplifies modding numbers to the power of several dozen digits if needed
int mathFncts::modBigNumber(unsigned long long int number, unsigned long long int power, unsigned long long int modder){
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
