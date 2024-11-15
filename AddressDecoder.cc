#include "AddressDecoder.h"
#include <cmath>

AddressDecoder::AddressDecoder(int cacheSize, int blockSize, int associativity)
    : cacheSize(cacheSize), blockSize(blockSize), associativity(associativity) {
    numBlocks = cacheSize / blockSize;
    numSets = numBlocks / associativity;

    blockOffsetBits = (int)std::log2(blockSize);
    setIndexBits = (int)std::log2(numSets);
    tagBits = 32 - blockOffsetBits - setIndexBits;
}

unsigned long AddressDecoder::getTag(unsigned long address) const {
    return address >> (blockOffsetBits + setIndexBits);
}

unsigned long AddressDecoder::getSetIndex(unsigned long address) const {
    unsigned long temp = address >> blockOffsetBits;
    unsigned long mask = (1 << setIndexBits) - 1;
    return temp & mask;
}

unsigned long AddressDecoder::getBlockOffset(unsigned long address) const {
    unsigned long mask = (1 << blockOffsetBits) - 1;
    return address & mask;
}

unsigned long AddressDecoder::reconstructAddress(unsigned long tag, unsigned long setIndex) const {
    return (tag << (setIndexBits + blockOffsetBits)) | (setIndex << blockOffsetBits);
}
