#ifndef CACHE_H
#define CACHE_H

#include "Set.h"
#include "AddressDecoder.h"
#include "PerformanceCounter.h"

class Cache {
private:
    Memory* memory;
    int cacheSize;
    int blockSize;
    int associativity;
    int numSets;
    Set** sets;
    AddressDecoder* decoder;

    PerformanceCounter performanceCounter;

public:
    Cache(Memory* memory, int cacheSize, int blockSize, int associativity);
    ~Cache();

    unsigned char read(unsigned long address);
    void write(unsigned long address, unsigned char value);

    void display() const;

    const PerformanceCounter& getPerformanceCounter() const; // Added getter
};

#endif // CACHE_H
