#include <stdio.h>
#include "AddressDecoder.h"
#include <iostream>


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


int main() {
    // Initialize the AddressDecoder with specific bit sizes for tag, set index, and block offset
    int tagBits = 10;
    int setIndexBits = 5;
    int blockOffsetBits = 3;

    AddressDecoder decoder(tagBits, setIndexBits, blockOffsetBits);

    // Sample address to test the decoder functions
    unsigned long address = 0b11010110010111101001;  // Example binary address (21 bits)
    
    // Testing getTag, getSetIndex, and getBlockOffset methods
    unsigned long tag = decoder.getTag(address);
    unsigned long setIndex = decoder.getSetIndex(address);
    unsigned long blockOffset = decoder.getBlockOffset(address);

    // Display the results of decoding
    std::cout << "Address: " << std::hex << address << std::dec << std::endl;
    std::cout << "Tag: " << tag << std::endl;
    std::cout << "Set Index: " << setIndex << std::endl;
    std::cout << "Block Offset: " << blockOffset << std::endl;

    // Testing getBlockBaseAddress method
    unsigned long baseAddress = decoder.getBlockBaseAddress(address);
    std::cout << "Block Base Address: " << std::hex << baseAddress << std::dec << std::endl;

    // Testing constructAddress method with retrieved values
    unsigned long constructedAddress = decoder.constructAddress(tag, setIndex, blockOffset);
    std::cout << "Constructed Address: " << std::hex << constructedAddress << std::dec << std::endl;

    // Verifying if constructed address matches the original address
    if (constructedAddress == address) {
        std::cout << "Success: Constructed address matches the original address." << std::endl;
    } else {
        std::cout << "Error: Constructed address does not match the original address." << std::endl;
    }

    return 0;
}
