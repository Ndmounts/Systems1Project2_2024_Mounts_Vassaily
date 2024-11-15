# include "Block.h"
# include "AddressDecoder.h"

#include <iostream>
#include <stdlib.h>
#include <chrono>

AddressDecoder* decoder;  // Pointer to an AddressDecoder object


Block::Block(int blockSize, unsigned char* mainMemory) {
    this->blockSize = blockSize;
    this->mainMemory = mainMemory;
    data = new unsigned char[blockSize];
    valid = false;
    dirty = false;
    timestamp = 0;


}

// Memory methods

// Load from Memory

void Block::loadFromMemory(unsigned long address, unsigned long tag) {
    unsigned long baseAddress = decoder->getBlockBaseAddress(address);
    for (int i = 0; i < blockSize; i++) {
        data[i] = mainMemory[baseAddress + i];
    }
    setTag(tag);
}

// Save to Memory
void Block::saveToMemory(unsigned long address) {
    unsigned long baseAddress = decoder->getBlockBaseAddress(address);
    for (int i = 0; i < blockSize; i++) {
        mainMemory[baseAddress + i] = data[i];
    }
}




Block::~Block() {
    delete[] data;
}

// Getter Methods


// Get Tag
unsigned long Block::getTag() const {
    return tag;
}

// Is Valid
bool Block::isValid() const {
    return valid;
}

// Is Dirty
bool Block::isDirty() const {
    return dirty;
}

// Get Timestamp
long Block::getTimestamp() const {
    return timestamp;
}


// Setter Methods

// Set Tag
void Block::setTag(unsigned long newTag) {
    tag = newTag;
    valid = true;
    dirty = false;
    updateTimestamp();
}


// Read and Write Methods

// Read




