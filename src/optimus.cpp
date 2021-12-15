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
    if (!probablyPrime(prime, MR_ITER))
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
    uint64 max = uint64(INT_MAX) + uint64(1);
    for (uint64 x = 1; x < max; x++)
        if (((prime % max) * (x % max)) % max == 1)
            return x;

    return 0;
}

uint64 Optimus::mulmod(uint64 a, uint64 b, uint64 mod)
{
    uint64  x = 0,y = a % mod;
    while (b > 0) {
        if (b % 2 == 1) {
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b/= 2;
    }
    return x % mod;
}

uint64 Optimus::modulo(uint64 base, uint64 exp, uint64 mod)
{
    uint64 x = 1;
    uint64 y = base;
    while (exp > 0) {
        if (exp % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exp = exp/2;
    }
    return x % mod;
}

bool Optimus::probablyPrime(uint64 val, int iterations)
{
    if (val < 2) {
        return false;
    }
    if (val != 2 && val % 2==0) {
        return false;
    }
    uint64 s = val - 1;
    while (s % 2 == 0) {
        s/= 2;
    }
    for (int i = 0; i < iterations; i++) {
        uint64 a = std::rand() % (val - 1) + 1, temp = s;
        uint64 mod = modulo(a, temp, val);
        while (temp != val - 1 && mod != 1 && mod != val - 1) {
            mod = mulmod(mod, mod, val);
            temp *= 2;
        }
        if (mod != val - 1 && temp % 2 == 0) {
            return false;
        }
    }
    return true;
}
