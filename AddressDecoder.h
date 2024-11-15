#ifndef ADDRESS_DECODER_H
#define ADDRESS_DECODER_H

class AddressDecoder {
    private:
        int tagBits;           // Number of bits for the tag
        int setIndexBits;      // Number of bits for the set index
        int blockOffsetBits;   // Number of bits for the block offset

    public:
        // Constructor: Takes in bit counts for tag, set index, and block offset
        AddressDecoder(int tagBits, int setIndexBits, int blockOffsetBits);

        // Methods to decode components of an address
        unsigned long getTag(unsigned long address) const;
        unsigned long getSetIndex(unsigned long address) const;
        unsigned long getBlockOffset(unsigned long address) const;

        // Method to get the base address of a block in memory using tag and set index
        unsigned long getBlockBaseAddress(unsigned long address) const;

        // Method to construct the full address from tag, set index, and block offset
        unsigned long constructAddress(unsigned long tag, unsigned long setIndex, unsigned long blockOffset) const;
};

#endif // ADDRESS_DECODER_H
