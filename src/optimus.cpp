#include "optimus.h"
#include <limits.h>
#include <cmath>

Optimus::Optimus(uint64 prime, uint64 random, uint64 modInverse)
    : m_valid(false)
{
    checkInput(prime, random, modInverse);
}

Optimus::Optimus(uint64 prime, uint64 random)
{
    checkInput(prime, random);
}

uint64 Optimus::encode(uint64 value)
{
    return ((value * m_prime) & INT_MAX) ^ m_random;
}

uint64 Optimus::decode(uint64 value)
{
    return ((value ^ m_random) * m_modInverse) & INT_MAX;
}

bool Optimus::checkInput(uint64 prime, uint64 random, uint64 modInverse)
{
    if (!MillerRabin::probablyPrime(prime, MR_ITER))
    {
        double accuracy = 1.0 - 1.0/std::pow(double(4), double(MR_ITER));
        m_lastError = std::to_string(prime) + " is not prime. Accuracy: " + std::to_string(accuracy);
        return false;
    }

    if (prime > INT_MAX) {
        m_lastError = "prime exceeds max int64";
        return false;
    }

    if (prime < 1) {
        m_lastError = "prime exceeds min: 1";
        return false;
    }

    m_prime = prime;
    m_modInverse = modInverse > 0 ? modInverse : calcModInverse(prime);
    m_random = random;
    m_valid = m_modInverse > 0;
    return true;
}

uint64 Optimus::calcModInverse(uint64 prime)
{
    uint64 max = uint64(INT_MAX)+uint64(1);
    for (uint64 x = 1; x < max; x++)
        if (((prime % max) * (x % max)) % max == 1)
            return x;

    return 0;
}
