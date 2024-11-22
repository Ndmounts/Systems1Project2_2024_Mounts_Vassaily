#include "Block.h"
#include <iostream>
#include <iomanip>

Block::Block(int blockSize, Memory* memory) : blockSize(blockSize), memory(memory) {
    data = new unsigned char[blockSize];
    valid = false;
    dirty = false;
    timestamp = 0;
    tag = 0;
}

Block::~Block() {
    delete[] data;
}

unsigned char Block::read(int blockOffset) {
    if (blockOffset >= 0 && blockOffset < blockSize) {
        updateTimestamp();
        return data[blockOffset];
    } else {
        std::cerr << "Block::read: Invalid blockOffset " << blockOffset << std::endl;
        return 0;
    }
}

void Block::write(int blockOffset, unsigned char value) {
    if (blockOffset >= 0 && blockOffset < blockSize) {
        data[blockOffset] = value;
        dirty = true;
        updateTimestamp();
    } else {
        std::cerr << "Block::write: Invalid blockOffset " << blockOffset << std::endl;
    }
}

void Block::loadFromMemory(unsigned long address) {
    for (int i = 0; i < blockSize; ++i) {
        data[i] = memory->getByte(address + i);
    }
    valid = true;
    dirty = false;
    updateTimestamp();
}

void Block::saveToMemory(unsigned long address) {
    for (int i = 0; i < blockSize; ++i) {
        memory->setByte(address + i, data[i]);
    }
    dirty = false;
}

void Block::updateTimestamp() {
    timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(
        m_clock.now().time_since_epoch()).count();
}

void Block::display() const {
    std::cout << "      valid: " << valid
              << "    tag: " << std::hex << tag
              << std::dec  // Reset to decimal
              << "    dirty: " << dirty
              << "    timestamp: " << timestamp << "\n";
    std::cout << "      ";
    for (int i = 0; i < blockSize; ++i) {
        std::cout << std::setw(2) << std::setfill('0') << std::hex
                  << std::nouppercase << (int)data[i] << "  ";
    }
    // Reset manipulators
    std::cout << std::dec << std::setfill(' ') << std::endl;
}
