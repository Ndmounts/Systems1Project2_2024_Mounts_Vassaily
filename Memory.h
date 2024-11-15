#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>

class Memory {
private:
    unsigned long memorySize;      // Changed from int to unsigned long
    unsigned char* bytes;
public:
    Memory(unsigned long size);    // Changed constructor parameter type
    ~Memory();

    unsigned char getByte(unsigned long address) const;
    void setByte(unsigned long address, unsigned char value);

    unsigned long getMemorySize() const; // Changed return type

    void display() const;
};

#endif // MEMORY_H
