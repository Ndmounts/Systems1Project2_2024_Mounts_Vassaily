#ifndef SET_H
#define SET_H

#include "Block.h"
#include "AddressDecoder.h"
#include "Memory.h"
#include "PerformanceCounter.h"

class Set {
private:
    int numBlocks;
    int blockSize;
    Block** blocks;
    Memory* memory;
    AddressDecoder* decoder;

public:
    Set(int numBlocks, int blockSize, Memory* memory, AddressDecoder* decoder);
    ~Set();

    unsigned char read(unsigned long address, PerformanceCounter& performanceCounter);
    void write(unsigned long address, unsigned char value, PerformanceCounter& performanceCounter);

    void display(int setIndex) const; // Added setIndex parameter
};

#endif // SET_H
