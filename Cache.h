// Cache.h
#ifndef CACHE_H
#define CACHE_H

#include "Set.h"
#include "AddressDecoder.h"

class Cache {
public:
    // Constructor
    Cache(unsigned char* mainMemory, int cacheSizeBytes, int blockSizeBytes, int associativity);

    // Destructor
    ~Cache();

    // Simulate a read operation
    unsigned char read(unsigned long address);

    // Simulate a write operation
    void write(unsigned long address, unsigned char value);

    // Display cache contents for debugging
    void display();

private:
    // Pointer to the main memory
    unsigned char* mainMemory;

    // Cache configuration parameters
    int cacheSizeBytes;
    int blockSizeBytes;
    int associativity;
    int numSets;
    int numBlocks;

    // Array of pointers to Sets
    Set** sets;

    // AddressDecoder instance
    AddressDecoder* addressDecoder;
};

#endif // CACHE_H
