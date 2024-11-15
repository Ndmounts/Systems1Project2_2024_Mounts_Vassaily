#include "Cache.h"
#include <iostream>

Cache::Cache(Memory* memory, int cacheSize, int blockSize, int associativity)
    : memory(memory), cacheSize(cacheSize), blockSize(blockSize), associativity(associativity) {
    int numBlocks = cacheSize / blockSize;
    numSets = numBlocks / associativity;
    decoder = new AddressDecoder(cacheSize, blockSize, associativity);

    sets = new Set*[numSets];
    for (int i = 0; i < numSets; ++i) {
        sets[i] = new Set(associativity, blockSize, memory, decoder);
    }
}

Cache::~Cache() {
    for (int i = 0; i < numSets; ++i) {
        delete sets[i];
    }
    delete[] sets;
    delete decoder;
}

unsigned char Cache::read(unsigned long address) {
    unsigned long setIndex = decoder->getSetIndex(address);
    return sets[setIndex]->read(address);
}

void Cache::write(unsigned long address, unsigned char value) {
    unsigned long setIndex = decoder->getSetIndex(address);
    sets[setIndex]->write(address, value);
}

void Cache::display() const {
    for (int i = 0; i < numSets; ++i) {
        std::cout << "Set " << i << ":\n";
        sets[i]->display();
    }
}
