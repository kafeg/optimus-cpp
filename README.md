# optimus-cpp
ID hashing and Obfuscation using Knuth's Algorithm for C++

You could use it if you need your ids to consist of only numbers. It's based on Knuth's integer hash method and produces obfuscated integer ids.

This realization doesn't work with big-integers, max id should be <= `INT_MAX` or `2147483647`.

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
    uint64 prime = 1580030173;
    uint64 modInverse = 59260789; // or once and slow: `uint64 modInverse = Optimus::calcModInverse(prime);`
    uint64 random = 1163945558;   // or `uint64 random = std::rand();`

    Optimus optimus(prime, modInverse, random);

    if (!optimus.isValid()) {
        std::cout << optimus.errorString() << std::endl;
        return 1;
    }

    uint64 myId = std::rand();
    uint64 encoded = optimus.encode(myId);
    uint64 decoded = optimus.decode(encoded);
    
    std::cout << optimus.prime() << " " << optimus.modInverse() << " " << optimus.random() << std::endl;
    std::cout << myId << " " << encoded << " " << decoded << std::endl;
    
    return 0;
}
```

### Alternatives

There are also PHP (+big numbers based on `GMP`) (https://github.com/jenssegers/optimus) and Go (also `INT_MAX`) (https://github.com/pjebs/optimus-go) implementations.

Mainly `optimus-cpp` lib is just a simple port of Go realization.

Another popular solution is http://hashids.org/, but it provides string ids like [A-Za-z0-9].
