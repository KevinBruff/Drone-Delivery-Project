// Fleet.h
// ESE 224 Fall 2026 Midterm Project (starter code)
// Team members: TODO

#ifndef FLEET_H
#define FLEET_H

#include "Drone.h"
#include <string>
#include <vector>
using namespace std;

class Fleet {
private:
    vector<Drone> drones;

    // Provided random number generator (Section 4.5)
    unsigned long long nextRandom(unsigned long long& state) const;

    // Suggested helpers (you may add more private helpers)
    void swapDrones(int i, int j);
    bool validIndex(int index) const;
	int findIndexByID(int id) const;

public:
    // Accessors and mutators
    bool addDrone(const Drone& d);
    Drone getDrone(int index) const;
    int getSize() const;

    // Sorting
    void selectionSortByID();
    void insertionSortByBattery();
    void sortByName();
    bool isSortedByID() const;

    // Searching
    int linearSearchByName(const string& name) const;
    int binarySearchByID(int id);

    // Dispatching
    int findNearestAvailable(int x, int y, double weight) const;
    bool dispatchDrone(int index, int x, int y, double weight);
    bool rechargeDrone(int id);
    void countByStatus() const;
    void processOrders(const string& orderFile, const string& logFile);

    // Other
    void shuffleFleet(unsigned long long seed);
    void displayAll() const;
    void displayDrone(int index) const;
    void writeFleetToFile(const string& filename) const;
};

#endif
