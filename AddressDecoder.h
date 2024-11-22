#ifndef ADDRESSDECODER_H
#define ADDRESSDECODER_H

#include <cstdint>

class AddressDecoder {
private:
    int cacheSize;
    int blockSize;
    int associativity;
    int numBlocks;
    int numSets;
    int tagBits;
    int setIndexBits;
    int blockOffsetBits;

public:
    AddressDecoder(int cacheSize, int blockSize, int associativity);

    unsigned long getTag(unsigned long address) const;
    unsigned long getSetIndex(unsigned long address) const;
    unsigned long getBlockOffset(unsigned long address) const;

    unsigned long reconstructAddress(unsigned long tag, unsigned long setIndex) const;

    int getBlockOffsetBits() const { return blockOffsetBits; }
    int getSetIndexBits() const { return setIndexBits; }
};

#endif // ADDRESSDECODER_H
