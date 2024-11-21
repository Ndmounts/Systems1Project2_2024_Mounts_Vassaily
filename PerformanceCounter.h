#ifndef PERFORMANCE_COUNTER_H
#define PERFORMANCE_COUNTER_H

#include <iostream>
#include <iomanip>

class PerformanceCounter {
private:
    int accesses;
    int hits;
    int misses;
    int writebacks;

public:
    PerformanceCounter() : accesses(0), hits(0), misses(0), writebacks(0) {}

    void incrementAccess() { ++accesses; }
    void incrementHit() { ++hits; }
    void incrementMiss() { ++misses; }
    void incrementWriteback() { ++writebacks; }

    void displayStatistics() const {
        std::cout << "Accesses:     " << accesses << "\n";
        std::cout << "Hits:         " << hits << "\n";
        std::cout << "Misses:       " << misses << "\n";
        std::cout << "Writebacks:   " << writebacks << "\n";
        std::cout << "Miss Perc:    " << (accesses ? (100.0 * misses / accesses) : 0.0) << "\n";
        std::cout << "Writeback Perc: " << (accesses ? (100.0 * writebacks / accesses) : 0.0) << "\n";
    }
};


#endif // PERFORMANCE_COUNTER_H
