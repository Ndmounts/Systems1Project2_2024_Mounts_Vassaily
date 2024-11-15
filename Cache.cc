// Cache.cc
#include "Cache.h"
#include <iostream>
#include <cmath>

Cache::Cache(unsigned char* mainMemory, int cacheSizeBytes, int blockSizeBytes, int associativity)
    : mainMemory(mainMemory),
      cacheSizeBytes(cacheSizeBytes),
      blockSizeBytes(blockSizeBytes),
      associativity(associativity)
{
    // Calculate the number of blocks and sets
    numBlocks = cacheSizeBytes / blockSizeBytes;
    numSets = numBlocks / associativity;

    // Create the AddressDecoder instance
    addressDecoder = new AddressDecoder(blockSizeBytes, numSets);

    // Initialize the array of Sets
    sets = new Set*[numSets];
    for (int i = 0; i < numSets; ++i) {
        sets[i] = new Set(associativity, blockSizeBytes);
    }
}

Cache::~Cache()
{
    // Delete each Set
    for (int i = 0; i < numSets; ++i) {
        delete sets[i];
    }
    delete[] sets;

    // Delete the AddressDecoder instance
    delete addressDecoder;
}

unsigned char Cache::read(unsigned long address)
{
    // Decode the address into tag, set index, and block offset
    unsigned long tag;
    int setIndex;
    int blockOffset;
    addressDecoder->decode(address, tag, setIndex, blockOffset);

    // Access the appropriate Set
    Set* set = sets[setIndex];
    unsigned char data = set->read(tag, blockOffset, mainMemory, address);

    return data;
}

void Cache::write(unsigned long address, unsigned char value)
{
    // Decode the address into tag, set index, and block offset
    unsigned long tag;
    int setIndex;
    int blockOffset;
    addressDecoder->decode(address, tag, setIndex, blockOffset);

    // Access the appropriate Set
    Set* set = sets[setIndex];
    set->write(tag, blockOffset, value, mainMemory, address);
}

void Cache::display()
{
    // Display the contents of the cache
    std::cout << "Cache Contents:" << std::endl;
    for (int i = 0; i < numSets; ++i) {
        std::cout << "Set " << i << ":" << std::endl;
        sets[i]->display();
    }
}
