#ifndef MILLERRABIN_H
#define MILLERRABIN_H

typedef unsigned long long uint64;

class MillerRabin
{
public:
    MillerRabin() = delete;
    MillerRabin(MillerRabin &other) = delete;

    static bool probablyPrime(uint64 val, int iterations);

private:
    static uint64 mulmod(uint64 a, uint64 b, uint64 mod);
    static uint64 modulo(uint64 base, uint64 exp, uint64 mod);
};

#endif // MILLERRABIN_H
