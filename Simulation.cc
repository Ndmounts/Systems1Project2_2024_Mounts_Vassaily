#include <stdio.h>
#include "Memory.h"
#include "Cache.h"

void testNwayDetail() {
    // This is a test that exercises an N-way associative cache
    printf("-------------------------------------------------------------------\n");
    printf("-------------------------------------------------------------------\n");
    printf("-------------------------------------------------------------------\n");
    printf("Cache Simulator Nway Detailed Test\n");
    
    // Initialize main memory with 32 bytes
    Memory* m = new Memory(32);
    // Initialize cache: 16 bytes cache size, 4 bytes per block, 2-way associative
    Cache* c = new Cache(m, 16, 4, 2);
    m->display();
    c->display();

    // Test sequence begins
    // -------------------------------------------------------------
    // 1. Read address 0 (Miss - Load into cache)
    printf("-------------------------------------------------------------------\n");
    printf("READ 0\n");
    printf("%d\n", c->read(0));
    m->display();
    c->display();
    c->getPerformanceCounter().displayStatistics();

    // 2. Read address 2 (Hit - Should be in cache)
    printf("-------------------------------------------------------------------\n");
    printf("READ 2\n");
    printf("%d\n", c->read(2));
    m->display();
    c->display();
    c->getPerformanceCounter().displayStatistics();

    // 3. Read address 4 (Miss - Different block, load into cache)
    printf("-------------------------------------------------------------------\n");
    printf("READ 4\n");
    printf("%d\n", c->read(4));
    m->display();
    c->display();
    c->getPerformanceCounter().displayStatistics();

    // 4. Read address 10 (Miss - Causes eviction if set is full)
    printf("-------------------------------------------------------------------\n");
    printf("READ 10\n");
    printf("%d\n", c->read(10));
    m->display();
    c->display();
    c->getPerformanceCounter().displayStatistics();

    // 5. Read address 12 (Miss - Will test LRU policy)
    printf("-------------------------------------------------------------------\n");
    printf("READ 12\n");
    printf("%d\n", c->read(12));
    m->display();
    c->display();
    c->getPerformanceCounter().displayStatistics();

    // 6. Read address 1 (Hit/Miss - Depending on LRU, test timestamp updates)
    printf("-------------------------------------------------------------------\n");
    printf("READ 1\n");
    printf("%d\n", c->read(1));
    m->display();
    c->display();
    c->getPerformanceCounter().displayStatistics();

    // 7. Read address 16 (Miss - Should cause eviction with LRU)
    printf("-------------------------------------------------------------------\n");
    printf("READ 16\n");
    printf("%d\n", c->read(16));
    m->display();
    c->display();
    c->getPerformanceCounter().displayStatistics();

    // 8. Write to address 6 (Hit - Modify existing cache block, mark dirty)
    printf("-------------------------------------------------------------------\n");
    printf("WRITE 6 with value 0x66\n");
    c->write(6, 0x66);
    m->display();
    c->display();
    c->getPerformanceCounter().displayStatistics();

    // 9. Write to address 21 (Miss - Load into cache, possibly evict dirty block)
    printf("-------------------------------------------------------------------\n");
    printf("WRITE 21 with value 0x55\n");
    c->write(21, 0x55);
    m->display();
    c->display();
    c->getPerformanceCounter().displayStatistics();

    // 10. Read address 12 (Miss - Should cause writeback if evicted block is dirty)
    printf("-------------------------------------------------------------------\n");
    printf("READ 12\n");
    printf("%d\n", c->read(12));
    m->display();
    c->display();
    c->getPerformanceCounter().displayStatistics();

    // 11. Write to address 30 (Miss - Causes writeback of dirty block)
    printf("-------------------------------------------------------------------\n");
    printf("WRITE 30 with value 0xEE\n");
    c->write(30, 0xEE);
    m->display();
    c->display();
    c->getPerformanceCounter().displayStatistics();

    // 12. Read address 6 (Hit - Verify that data was correctly written and cached)
    printf("-------------------------------------------------------------------\n");
    printf("READ 6\n");
    printf("%d\n", c->read(6));
    m->display();
    c->display();
    c->getPerformanceCounter().displayStatistics();

    // 13. Read address 21 (Hit - Verify that data was correctly written and cached)
    printf("-------------------------------------------------------------------\n");
    printf("READ 21\n");
    printf("%d\n", c->read(21));
    m->display();
    c->display();
    c->getPerformanceCounter().displayStatistics();

    // 14. Read address 4 (Miss - Test if it was evicted earlier)
    printf("-------------------------------------------------------------------\n");
    printf("READ 4\n");
    printf("%d\n", c->read(4));
    m->display();
    c->display();
    c->getPerformanceCounter().displayStatistics();

    // 15. Write to address 0 (Hit/Miss - Depending on cache state)
    printf("-------------------------------------------------------------------\n");
    printf("WRITE 0 with value 0xAA\n");
    c->write(0, 0xAA);
    m->display();
    c->display();
    c->getPerformanceCounter().displayStatistics();

    // 16. Read address 0 (Hit - Verify written data)
    printf("-------------------------------------------------------------------\n");
    printf("READ 0\n");
    printf("%d\n", c->read(0));
    m->display();
    c->display();
    c->getPerformanceCounter().displayStatistics();

    // Cleanup
    delete c;
    delete m;
}

int main() {
    // Correctness test
    testNwayDetail();
    // Performance tests can be added here...
    return 0;
}
