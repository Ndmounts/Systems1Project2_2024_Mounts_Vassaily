#ifndef SET_H
#define SET_H

#include "Block.h"
#include "AddressDecoder.h"

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

    unsigned char read(unsigned long address);
    void write(unsigned long address, unsigned char value);

    void display() const;
};

#endif // SET_H
