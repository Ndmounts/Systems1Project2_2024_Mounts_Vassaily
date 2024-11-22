#ifndef BLOCK_H
#define BLOCK_H

#include "Memory.h"
#include <chrono>

class Block {
private:
    unsigned char* data;
    int blockSize;
    unsigned long tag;
    bool valid;
    bool dirty;
    Memory* memory;
    std::chrono::high_resolution_clock m_clock;
    long timestamp;

public:
    Block(int blockSize, Memory* memory);
    ~Block();

    unsigned char read(int blockOffset);
    void write(int blockOffset, unsigned char value);

    void loadFromMemory(unsigned long address);
    void saveToMemory(unsigned long address);

    unsigned long getTag() const { return tag; }
    void setTag(unsigned long tag) { this->tag = tag; }

    bool isValid() const { return valid; }
    void setValid(bool valid) { this->valid = valid; }

    bool isDirty() const { return dirty; }
    void setDirty(bool dirty) { this->dirty = dirty; }

    long getTimestamp() const { return timestamp; }
    void updateTimestamp();

    void display() const;
};

#endif // BLOCK_H
