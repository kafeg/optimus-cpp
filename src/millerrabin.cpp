#include "millerrabin.h"
#include <cstdlib>

bool MillerRabin::probablyPrime(uint64 val, int iterations) {
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

uint64 MillerRabin::mulmod(uint64 a, uint64 b, uint64 mod)
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

uint64 MillerRabin::modulo(uint64 base, uint64 exp, uint64 mod)
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
