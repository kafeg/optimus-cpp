#include "src/optimus.h"
#include <iostream>

#define RANGE(a, b) uint64 a=1; a<b; a++

int main(int argc, char *argv[])
{
    std::srand(std::time(nullptr));

    // https://primes.utm.edu/lists/small/millions/

    // simple create with wrong prime and modinverse
    Optimus optimus(961748942, 2, std::rand());
    std::cout << optimus.isValid() << " " << optimus.lastError() << std::endl;

    // create with correct prime and mod inverse
    optimus = Optimus(1580030173, 59260789, std::rand());
    std::cout << optimus.isValid() << " " << optimus.lastError() << std::endl;

    // calculate mod inverse (slow)
    optimus = Optimus(1580030173, std::rand());
    std::cout << optimus.isValid() << " " << optimus.lastError() << " " << optimus.prime() << " " << optimus.modInverse() << " " << optimus.random() << std::endl;

    // test all possible values
    for(RANGE(i, INT_MAX)) {
        uint64 encoded = optimus.encode(i);
        uint64 decoded = optimus.decode(encoded);
        if (!i == decoded)
            std::cout << i << " " << decoded << " " << (i == decoded) << " " << encoded << std::endl;
    }
}
