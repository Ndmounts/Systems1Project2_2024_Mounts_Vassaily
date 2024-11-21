#include "Set.h"
#include <iostream>
#include <climits>

Set::Set(int numBlocks, int blockSize, Memory* memory, AddressDecoder* decoder)
    : numBlocks(numBlocks), blockSize(blockSize), memory(memory), decoder(decoder) {
    blocks = new Block*[numBlocks];
    for (int i = 0; i < numBlocks; ++i) {
        blocks[i] = new Block(blockSize, memory);
    }
}

Set::~Set() {
    for (int i = 0; i < numBlocks; ++i) {
        delete blocks[i];
    }
    delete[] blocks;
}

unsigned char Set::read(unsigned long address, PerformanceCounter& performanceCounter) {
    unsigned long tag = decoder->getTag(address);
    unsigned long setIndex = decoder->getSetIndex(address);
    int blockOffset = decoder->getBlockOffset(address);

    // Search for block with matching tag
    Block* targetBlock = nullptr;
    for (int i = 0; i < numBlocks; ++i) {
        if (blocks[i]->isValid() && blocks[i]->getTag() == tag) {
            targetBlock = blocks[i];
            break;
        }
    }

    if (targetBlock) {
        // Cache hit
        performanceCounter.incrementHit();
        performanceCounter.incrementAccess();
        return targetBlock->read(blockOffset);
    } else {
        // Cache miss
        // Find a block to replace
        performanceCounter.incrementMiss();
        performanceCounter.incrementAccess();
        Block* blockToReplace = nullptr;
        // First look for an invalid block
        for (int i = 0; i < numBlocks; ++i) {
            if (!blocks[i]->isValid()) {
                blockToReplace = blocks[i];
                break;
            }
        }

        if (!blockToReplace) {
            // All blocks are valid, use LRU replacement
            long oldestTimestamp = LONG_MAX;
            for (int i = 0; i < numBlocks; ++i) {
                if (blocks[i]->getTimestamp() < oldestTimestamp) {
                    oldestTimestamp = blocks[i]->getTimestamp();
                    blockToReplace = blocks[i];
                }
            }
        }

        // If dirty, write back to Memory
        if (blockToReplace->isDirty()) {
            performanceCounter.incrementWriteback();
            unsigned long oldAddress = decoder->reconstructAddress(blockToReplace->getTag(), setIndex);
            blockToReplace->saveToMemory(oldAddress);
        }

        // Load the new block from Memory
        unsigned long blockStartAddress = address - decoder->getBlockOffset(address);
        blockToReplace->loadFromMemory(blockStartAddress);
        blockToReplace->setTag(tag);
        blockToReplace->setValid(true);

        // Read the data
        return blockToReplace->read(blockOffset);
    }
}

void Set::write(unsigned long address, unsigned char value, PerformanceCounter& performanceCounter) {
    unsigned long tag = decoder->getTag(address);
    unsigned long setIndex = decoder->getSetIndex(address);
    int blockOffset = decoder->getBlockOffset(address);

    // Search for block with matching tag
    Block* targetBlock = nullptr;
    for (int i = 0; i < numBlocks; ++i) {
        if (blocks[i]->isValid() && blocks[i]->getTag() == tag) {
            targetBlock = blocks[i];
            break;
        }
    }

    if (targetBlock) {
        performanceCounter.incrementHit();
        performanceCounter.incrementAccess();
        targetBlock->write(blockOffset, value);
        return;
    } else {
        // Cache miss
        performanceCounter.incrementMiss();
        performanceCounter.incrementAccess();
        // Find a block to replace
        Block* blockToReplace = nullptr;
        // First look for an invalid block
        for (int i = 0; i < numBlocks; ++i) {
            if (!blocks[i]->isValid()) {
                blockToReplace = blocks[i];
                break;
            }
        }

        if (!blockToReplace) {
            // All blocks are valid, use LRU replacement
            long oldestTimestamp = LONG_MAX;
            for (int i = 0; i < numBlocks; ++i) {
                if (blocks[i]->getTimestamp() < oldestTimestamp) {
                    oldestTimestamp = blocks[i]->getTimestamp();
                    blockToReplace = blocks[i];
                }
            }
        }

        // If dirty, write back to Memory
        if (blockToReplace->isDirty()) {
            performanceCounter.incrementWriteback();
            unsigned long oldAddress = decoder->reconstructAddress(blockToReplace->getTag(), setIndex);
            blockToReplace->saveToMemory(oldAddress);
        }

        // Load the new block from Memory
        unsigned long blockStartAddress = address - decoder->getBlockOffset(address);
        blockToReplace->loadFromMemory(blockStartAddress);
        blockToReplace->setTag(tag);
        blockToReplace->setValid(true);

        // Write the data
        blockToReplace->write(blockOffset, value);
    }
}

void Set::display() const {
    for (int i = 0; i < numBlocks; ++i) {
        blocks[i]->display();
    }
}
