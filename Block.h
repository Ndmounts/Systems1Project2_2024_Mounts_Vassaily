#ifndef BLOCK_H
#define BLOCK_H

#include <chrono>

class Block {
    private:
        int blockSize;                  // Size of the block in bytes
        unsigned char* data;            // Array to hold block data
        unsigned long tag;              // Tag for the block (part of the address)
        bool valid;                     // Flag to indicate if the block contains valid data
        bool dirty;                     // Flag to indicate if the block has been modified
        long timestamp;                 // Timestamp for LRU tracking
        unsigned char* mainMemory;      // Pointer to main memory

        // Private helper to update timestamp
        void updateTimestamp();

    public:
        // Constructor
        Block(int blockSize, unsigned char* mainMemory);

        // Destructor
        ~Block();

        // Methods to read and write data within the block
        unsigned char read(int blockOffset);              // Read a byte at the given block offset
        void write(int blockOffset, unsigned char value); // Write a byte at the given block offset

        // Methods to load and save data to/from main memory
        void loadFromMemory(unsigned long address, unsigned long tag);  // Load data from memory
        void saveToMemory(unsigned long address);                       // Save data back to memory

        // Getters and setters
        unsigned long getTag() const { return tag; }
        bool isValid() const { return valid; }
        bool isDirty() const { return dirty; }
        void setTag(unsigned long newTag) { tag = newTag; valid = true; dirty = false; }
        void markDirty() { dirty = true; }
        long getTimestamp() const { return timestamp; }
};

#endif // BLOCK_H