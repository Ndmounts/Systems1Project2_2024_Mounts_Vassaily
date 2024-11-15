#include <stdio.h>
#include "AddressDecoder.h"

// Constructor: Takes in bit counts for tag, set index, and block offset
AddressDecoder::AddressDecoder(int tagBits, int setIndexBits, int blockOffsetBits) {
    this->tagBits = tagBits;
    this->setIndexBits = setIndexBits;
    this->blockOffsetBits = blockOffsetBits;
}

// Getter methods defined outside the constructor

unsigned long AddressDecoder::getTag(unsigned long address) const {
    unsigned long tagMask = (1UL << tagBits) - 1;
    return (address >> (setIndexBits + blockOffsetBits)) & tagMask;
}

unsigned long AddressDecoder::getSetIndex(unsigned long address) const {
    unsigned long setIndexMask = (1UL << setIndexBits) - 1;
    return (address >> blockOffsetBits) & setIndexMask;
}

unsigned long AddressDecoder::getBlockOffset(unsigned long address) const {
    unsigned long blockOffsetMask = (1UL << blockOffsetBits) - 1;
    return address & blockOffsetMask;
}


// Calculate the base address of a block in memory using the tag and set index
unsigned long AddressDecoder::getBlockBaseAddress(unsigned long address) const {
    unsigned long tag = getTag(address);
    unsigned long setIndex = getSetIndex(address);

    return (tag << (setIndexBits + blockOffsetBits)) | (setIndex << blockOffsetBits);
}

// Construct the full address from tag, set index, and block offset
unsigned long AddressDecoder::constructAddress(unsigned long tag, unsigned long setIndex, unsigned long blockOffset) const {
    return (tag << (setIndexBits + blockOffsetBits)) | (setIndex << blockOffsetBits) | blockOffset;
}