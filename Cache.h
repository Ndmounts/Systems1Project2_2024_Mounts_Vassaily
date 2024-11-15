#ifndef CACHE_H 
#define CACHE_H

#include "Set.h"            // Assuming Set and AddressDecoder classes are defined elsewhere
#include "AddressDecoder.h" // Ensure this file defines the AddressDecoder class

class Cache {
    private:
        int cacheSize;
        int blockSize;
        int setAssociativity;
        int numSets;                // Number of sets in the cache
        Set** sets;                 // Array of pointers to Sets
        AddressDecoder* decoder;    // Pointer to AddressDecoder instance
        unsigned char* mainMemory;  // Pointer to the main memory

    public:
        // Constructor
        Cache(unsigned char* mainMemory, int cacheSize, int blockSize, int setAssociativity);

        // Destructor to clean up allocated memory
        ~Cache();

        // Methods for read, write, and display
        unsigned char read(unsigned long address);  // Simulate a read from cache
        void write(unsigned long address, unsigned char value); // Simulate a write to cache
        void display() const;                       // Display contents of the cache for debugging
};

#endif // CACHE_H
