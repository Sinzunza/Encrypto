#ifndef MATHFNCTS_H
#define MATHFNCTS_H


class mathFncts {
    
    public:
        mathFncts();
        static unsigned long long int gcd (unsigned long long int a, unsigned long long int b);
        //simplifies modding numbers to the power of several dozen digits if needed
        static int modBigNumber(unsigned long long int number, unsigned long long int power, unsigned long long int modder);


    protected:

    private:

};

#endif // MATHFNCTS_H
