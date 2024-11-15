#include "Memory.h"
#include <stdexcept>
#include <cstdio>

Memory::Memory(int size) : mem_size(size) {
    mem_bytes = new unsigned char[mem_size];
    for (int i = 0; i < mem_size; ++i) {
        mem_bytes[i] = i % 255;
    }
}

Memory::~Memory() {
    delete[] mem_bytes;
}

unsigned char Memory::getByte(unsigned long address) const {
    if (address >= static_cast<unsigned long>(mem_size)) {
        throw std::out_of_range("Address out of range in getByte");
    }
    return mem_bytes[address];
}

void Memory::setByte(unsigned long address, unsigned char value) {
    if (address >= static_cast<unsigned long>(mem_size)) {
        throw std::out_of_range("Address out of range in setByte");
    }
    mem_bytes[address] = value;
}

int Memory::getMemSize() const {
    return mem_size;
}

void Memory::display() const {
    printf("Main memory:\n");
    for (int i = 0; i < mem_size; ++i) {
        if (i % 16 == 0) {
            printf("%04x: ", i);
        }
        printf("%02x ", mem_bytes[i]);
        if ((i + 1) % 16 == 0 || i == mem_size - 1) {
            printf("\n");
        }
    }
}
