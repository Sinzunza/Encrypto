#include <iostream>
#include <stdio.h>
#include <limits>

#include "../header/rsaCrypto.h"
#include "../header/primes.h"
#include "../header/mathFncts.h"

using namespace std;

void setRSAKeys(rsaCrypto &encrypto);

int main(){

    while (true){

        string buffer;
        char choice;
        while(true) {
            cout << "Enter 'e' for encryption, 'd' for decryption, or 'x' to exit: ";
            getline(cin, buffer);
            choice = buffer[0];
            if(buffer.length() == 1 && (choice == 'e' || choice == 'd' || choice == 'x')){
                break;
            }
            else {
                cout << "Invalid input: Choose between given choices." << endl;
            }
        }

        switch (choice){
            case 'e': {
                rsaCrypto encrypto;
                setRSAKeys(encrypto);
                encrypto.encrypt();
                cout << "Message encrypted.\n" << endl;
                break;
                }
            case 'd': {
                rsaCrypto encrypto;
                setRSAKeys(encrypto);
                encrypto.decrypt();
                cout << "Message decrypted.\n" << endl;
                break;
                }
            case 'x':
                return 0;
            default:
                cout << "Error Occurred!" << endl;
        }

    }

    return 0;

}

void setRSAKeys(rsaCrypto &encrypto){
    unsigned long long int N = 1;
    unsigned long long int E = 1;

    while(true){
        cout << "Enter a valid n greater than 127: ";
        cin >> N;
        if (N <= 127) {
            cout << "Invalid input: N has to be greater than 127." << endl;
        }
        else if (!encrypto.isValidN(N)){
            cout << "Invalid input: Unacceptable N value, refer to RSA Cryptosystem for acceptable values." << endl;
        }
        else {
            encrypto.setN(N);
            break;
        }
    }

    while(true){
        cout << "Enter a valid e: ";
        cin >> E;
        if (!encrypto.isValidE(E)){
            cout << "Invalid input: Unacceptable E value, refer to RSA Cryptosystem for acceptable values." << endl;
        }
        else {
            encrypto.setE(E);
            break;
        }
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
