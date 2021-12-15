# optimus-cpp
ID hashing and Obfuscation using Knuth's Algorithm for C++

You could use it if you need your ids to consist of only numbers. It's based on Knuth's integer hash method and produces obfuscated integer ids.

This realization doesn't work with big-integers, max id should be <= `INT_MAX` or `2147483647`.

CI and Platforms: https://github.com/microsoft/vcpkg/pull/22025

### Build and install

Please just use vcpkg to build this library:
```bash
# Windows
git clone https://github.com/microsoft/vcpkg
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg.exe install optimus-cpp

# Unix
git clone https://github.com/microsoft/vcpkg
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg install optimus-cpp
```

### Usage

- Calculate `Prime`, `ModInverse` and `Random`. All values should be <= INT_MAX.
- `Prime` should be (2147483647). You could take Prime there: http://primes.utm.edu/lists/small/millions/
- Calculate `ModInverse` for your prime using `Optimus::calcModInverse(2147483647)` - this is slow operation so do it once and then save value.
- Generate any `Random` you want
- Store those 3 values and then load and use them for create instance of Optimus
- Use generated numbers in the code like this:

```cpp
#include <iostream>
#include "src/optimus.h"

int main(int argc, char *argv[])
{
    std::srand(std::time(nullptr));

    // all values <= INT_MAX
    uint64 prime = 	334214467;
    uint64 modInverse = 734363499; // or slow: `uint64 modInverse = Optimus::calcModInverse(prime);`
    uint64 random = 763294573;   // or `uint64 random = std::rand();`

    Optimus optimus(prime, modInverse, random);

    if (!optimus.isValid()) {
        std::cout << optimus.errorString() << std::endl;
        return 1;
    }

    std::cout << optimus.prime() << " "
              << optimus.modInverse() << " "
              << optimus.random() << std::endl;

    for (int i = 1; i < 50; ++i) {
        uint64 myId = std::rand();
        uint64 encoded = optimus.encode(myId);
        uint64 decoded = optimus.decode(encoded);
        std::cout.width(7);
        std::cout << myId;
        std::cout.width(7);
        std::cout << decoded;
        std::cout.width(12);
        std::cout << encoded;
        std::cout.width(2);
        std::cout << (myId == decoded) << std::endl;
    }

    return 0;
}
```

Sample output:
```
334214467 734363499 763294573
   1490   1490  1553599643 1
  15533  15533   431735082 1
  32387  32387   430589988 1
  12346  12346   404574787 1
  30236  30236  2116699705 1
   4436   4436   488513425 1
  16199  16199   713306616 1
   9225   9225  1975007286 1
   8612   8612   136524417 1
  32287  32287  1103044208 1
   7676   7676  1660024729 1
  16109  16109   711195242 1
  14641  14641  1711763390 1
  22285  22285   820972042 1
  11185  11185  1880385342 1
  26247  26247  1190902584 1
    369    369   465483518 1
  11617  11617  1448248846 1
  22197  22197  1777686834 1
  10690  10690  1977214123 1
     52     52   647897841 1
   6145   6145    26676782 1
   8545   8545  1137943054 1
  27736  27736  1677746277 1
   2520   2520   893303013 1
  23324  23324  1514690361 1
  15161  15161  1866416006 1
  27545  27545  1104979302 1
  17156  17156   761376097 1
  13071  13071   848626816 1
  12340  12340   279155441 1
    104    104   985616469 1
  27290  27290   967195427 1
  18058  18058   501152627 1
   8791   8791  1045662888 1
  17030  17030   526570623 1
  32742  32742  2043667551 1
   1006   1006  1698479655 1
  16776  16776  1128316405 1
  28947  28947   687863188 1
   6428   6428   520465721 1
  28154  28154  2099411203 1
  30114  30114  2021564427 1
  17489  17489  1153750366 1
  32257  32257   979131438 1
   7079   7079  2006957272 1
  28357  28357   825996770 1
   3244   3244  1134698089 1
  23272  23272  1177231829 1
```

### Alternatives

There are also PHP (+big numbers based on `GMP`) (https://github.com/jenssegers/optimus) and Go (also `INT_MAX`) (https://github.com/pjebs/optimus-go) implementations.

Mainly `optimus-cpp` lib is just a simple port of Go realization.

Another popular solution is http://hashids.org/, but it provides string ids like [A-Za-z0-9].
