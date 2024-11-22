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
        // Reset manipulators
        std::cout << std::dec << std::setfill(' ') << std::fixed << std::setprecision(2);

        std::cout << std::left << std::setw(15) << "Accesses:" << std::right << accesses << "\n";
        std::cout << std::left << std::setw(15) << "Hits:" << std::right << hits << "\n";
        std::cout << std::left << std::setw(15) << "Misses:" << std::right << misses << "\n";
        std::cout << std::left << std::setw(15) << "Writebacks:" << std::right << writebacks << "\n";
        std::cout << std::left << std::setw(15) << "Miss Perc:" << std::right
                  << (accesses ? (100.0 * misses / accesses) : 0.0) << "\n";
        std::cout << std::left << std::setw(15) << "Writeback Perc:" << std::right
                  << (accesses ? (100.0 * writebacks / accesses) : 0.0) << "\n";
    }
};

#endif // PERFORMANCE_COUNTER_H
