#include "src/optimus.h"
#include <iostream>

#define RANGE(a, b) uint64 a=1; a<b; a++

int main(int argc, char *argv[])
{
    std::srand(std::time(nullptr));

    // https://primes.utm.edu/lists/small/millions/

    // simple create with wrong prime and modinverse
    Optimus optimus(961748942, 2, std::rand());
    std::cout << optimus.isValid() << " " << optimus.errorString() << std::endl;

    // create with correct prime and mod inverse
    optimus = Optimus(1580030173, 59260789, std::rand());
    std::cout << optimus.isValid() << " " << optimus.errorString() << std::endl;

    // calculate mod inverse (slow)
    optimus = Optimus(1580030173, Optimus::calcModInverse(1580030173), std::rand());
    std::cout << optimus.isValid() << " " << optimus.errorString() << " " << optimus.prime() << " " << optimus.modInverse() << " " << optimus.random() << std::endl;

    optimus = Optimus(2147483647, Optimus::calcModInverse(2147483647), std::rand());

    // test all possible values
    int logCounter = 0;
    for(RANGE(i, INT_MAX)) {
        logCounter++;
        uint64 encoded = optimus.encode(i);
        uint64 decoded = optimus.decode(encoded);
        if (i != decoded)
            std::cout << i << " " << decoded << " " << (i == decoded) << " " << encoded << std::endl;

        if (logCounter > 100000000) {
            std::cout << "Processed " << i << std::endl;
            logCounter = 0;
        }
    }
    std::cout << "Processed " << INT_MAX << std::endl;
}
