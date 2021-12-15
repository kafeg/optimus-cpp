#ifndef OPTIMUSNATIVE_H
#define OPTIMUSNATIVE_H
#include <string>

#define MR_ITER 20

typedef unsigned long long uint64;

class Optimus {

public:
    Optimus() = delete;
    Optimus(uint64 prime, uint64 modInverse, uint64 random);

    uint64 encode(uint64 value);
    uint64 decode(uint64 value);
    static uint64 calcModInverse(uint64 prime);

    bool isValid() { return m_valid; }
    std::string errorString() { return m_lastError; }
    uint64 prime() { return m_prime; }
    uint64 modInverse() { return m_modInverse; }
    uint64 random() { return m_random; }

private:
    bool checkInput(uint64 prime, uint64 random, uint64 modInverse = 0);

    //check for prime
    uint64 mulmod(uint64 a, uint64 b, uint64 mod);
    uint64 modulo(uint64 base, uint64 exp, uint64 mod);
    bool probablyPrime(uint64 val, int iterations);

private:
    uint64 m_prime;
    uint64 m_modInverse;
    uint64 m_random;
    bool m_valid;
    std::string m_lastError;
};



#endif // OPTIMUSNATIVE_H
