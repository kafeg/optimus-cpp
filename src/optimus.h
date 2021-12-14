#ifndef OPTIMUSNATIVE_H
#define OPTIMUSNATIVE_H
#include <string>
#include "millerrabin.h"

#define MR_ITER 20

class Optimus {

public:
    Optimus() = delete;
    // load all values
    Optimus(uint64 prime, uint64 random, uint64 modInverse);

    // calculate 'modInverse'
    Optimus(uint64 prime, uint64 random);

    uint64 encode(uint64 value);
    uint64 decode(uint64 value);

    bool isValid() { return m_valid; }
    std::string lastError() { return m_lastError; }
    uint64 prime() { return m_prime; }
    uint64 modInverse() { return m_modInverse; }
    uint64 random() { return m_random; }

private:
    bool checkInput(uint64 prime, uint64 random, uint64 modInverse = 0);
    uint64 calcModInverse(uint64 prime);

private:
    uint64 m_prime;
    uint64 m_modInverse;
    uint64 m_random;
    bool m_valid;
    std::string m_lastError;
};



#endif // OPTIMUSNATIVE_H
