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
    performanceCounter.incrementAccess();
    unsigned long setIndex = decoder->getSetIndex(address);
    unsigned char value = sets[setIndex]->read(address, performanceCounter);
    return value;
}

void Cache::write(unsigned long address, unsigned char value) {
    performanceCounter.incrementAccess();
    unsigned long setIndex = decoder->getSetIndex(address);
    sets[setIndex]->write(address, value, performanceCounter);
}

void Cache::display() const {
    std::cout << "CACHE:\n";
    for (int i = 0; i < numSets; ++i) {
        sets[i]->display(i);
    }
}


const PerformanceCounter& Cache::getPerformanceCounter() const {
    return performanceCounter;
}
