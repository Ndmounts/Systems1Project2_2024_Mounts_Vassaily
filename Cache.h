#ifndef CACHE_H
#define CACHE_H

#include "Set.h"
#include "AddressDecoder.h"

class Cache {
private:
    Memory* memory;
    int cacheSize;
    int blockSize;
    int associativity;
    int numSets;
    Set** sets;
    AddressDecoder* decoder;

public:
    Cache(Memory* memory, int cacheSize, int blockSize, int associativity);
    ~Cache();

    unsigned char read(unsigned long address);
    void write(unsigned long address, unsigned char value);

    void display() const;
};

#endif // CACHE_H
