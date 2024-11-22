#include "PerformanceCounter.h"

PerformanceCounter::PerformanceCounter() : accesses(0), hits(0), misses(0) {}

void PerformanceCounter::incrementAccess() {
    accesses++;
}

void PerformanceCounter::incrementHit() {
    hits++;
}

void PerformanceCounter::incrementMiss() {
    misses++;
}


void PerformanceCounter::displayStatistics() const {
    std::cout << "Accesses: " << accesses << "\n";
    std::cout << "Hits: " << hits << "\n";
    std::cout << "Misses: " << misses << "\n";
    std::cout << "Miss Perc: " << (accesses ? (100.0 * misses / accesses) : 0.0) << "\n";
}
