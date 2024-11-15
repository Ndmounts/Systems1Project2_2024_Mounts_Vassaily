#ifndef MEMORY_H
#define MEMORY_H

class Memory {
private:
    int mem_size;
    unsigned char* mem_bytes;

public:
    // Constructor
    Memory(int size);

    // Destructor
    ~Memory();

    // Accessors
    unsigned char getByte(unsigned long address) const;
    void setByte(unsigned long address, unsigned char value);

    // Getter for memory size
    int getMemSize() const;

    // Display method
    void display() const;
};

#endif // MEMORY_H
