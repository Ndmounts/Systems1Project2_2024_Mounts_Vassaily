#ifndef SET_H
#define SET_H

#include "Block.h"            // Assuming Block class is defined elsewhere
#include "AddressDecoder.h"    // Assuming AddressDecoder class is defined in this file

class Set {
    private:
        int numBlocks;                // Number of blocks in the set
        int blockSize;                // Size of each block in bytes
        Block** blocks;               // Array of pointers to Blocks
        AddressDecoder* decoder;      // Pointer to AddressDecoder instance
        unsigned char* mainMemory;    // Pointer to main memory

        // Private helper methods
        int findBlock(unsigned long address);   // Helper to find a block containing the address
        int findLRUBlock();                     // Helper to find the least recently used block
        void loadBlock(int blockIndex, unsigned long address);  // Load a block from memory

    public:
        // Constructor
        Set(int numBlocks, int blockSize, unsigned char* mainMemory, AddressDecoder* decoder);

        // Destructor
        ~Set();

        // Read, write, and display methods
        unsigned char read(unsigned long address);            // Read from the set
        void write(unsigned long address, unsigned char value); // Write to the set
        void display() const;                                  // Display contents for debugging
};

#endif // SET_H