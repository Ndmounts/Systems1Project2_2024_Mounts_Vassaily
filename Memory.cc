#include "Memory.h"
#include <iostream>
#include <iomanip>

Memory::Memory(unsigned long size) : memorySize(size) { // Updated constructor
    bytes = new unsigned char[memorySize];
    for (unsigned long i = 0; i < memorySize; ++i) { // Changed loop variable to unsigned long
        bytes[i] = i % 255;
    }
}

Memory::~Memory() {
    delete[] bytes;
}

unsigned char Memory::getByte(unsigned long address) const {
    if (address < memorySize) {
        return bytes[address];
    } else {
        std::cerr << "Memory::getByte: Invalid address " << address << std::endl;
        return 0;
    }
}

void Memory::setByte(unsigned long address, unsigned char value) {
    if (address < memorySize) {
        bytes[address] = value;
    } else {
        std::cerr << "Memory::setByte: Invalid address " << address << std::endl;
    }
}

unsigned long Memory::getMemorySize() const {
    return memorySize;
}

void Memory::display() const {
    for (unsigned long i = 0; i < memorySize; ++i) { // Changed loop variable to unsigned long
        std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)bytes[i] << " ";
        if ((i + 1) % 16 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::dec << std::endl;
}
