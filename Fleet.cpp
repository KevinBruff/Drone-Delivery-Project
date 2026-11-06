// Fleet.cpp
// ESE 224 Fall 2026 Midterm Project (starter code)
// Team members: TODO
//
// Every function below compiles but does nothing useful yet.
// Replace each TODO with your implementation (see Section 4 of the handout).
// Remember: no <algorithm>, no std::sort, std::swap, std::find, or std::shuffle.

#include "Fleet.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// ---------- Private helpers ----------

// Provided random number generator. Copy exactly; do not change.
unsigned long long Fleet::nextRandom(unsigned long long& state) const
{
    state = (state * 1103515245ULL + 12345ULL) % 2147483648ULL;
    return state;
}

void Fleet::swapDrones(int i, int j)
{
    // TODO: exchange drones[i] and drones[j] using a temporary Drone **DONE**
    if (validIndex(i) && validIndex(j)) {
        Drone temp;
        temp = drones[i];
        drones[i] = drones[j];
        drones[j] = temp;
    }
    else {
        cout << "Invalid Indices" << endl;
    }
}

bool Fleet::validIndex(int index) const
{
    // TODO: true if 0 <= index < number of drones **DONE**
    if (index >= 0 && index < (int)drones.size())
    {
        return true;
    }
    return false;
}

// ---------- Accessors and mutators ----------

bool Fleet::addDrone(const Drone& d)
{
    // TODO: reject a duplicate ID (use operator==), otherwise add to the end       **DONE**
    for (int i = 0; i < (int)drones.size(); i++) {
        if (d == drones[i]) {
            cout << "Duplicate ID" << endl;
            return false;
        }
    }
    drones.push_back(d);
    return true;
}

Drone Fleet::getDrone(int index) const
{
    // TODO: check the range; print an error and return Drone() if invalid  **DONE**
    if (index >= 0 && index < drones.size()) {
        return drones[index];
    }
    cout << "Drone not found";
    return Drone();
}

int Fleet::getSize() const
{
    return (int)drones.size();
}

// ---------- Sorting ----------
// Follow the counting rules in Section 4.2 exactly; your counts are checked.

void Fleet::selectionSortByID()
{
    // TODO: ascending by ID. Print: Selection sort by ID: C comparisons, S swaps. **DONE**
    int C(0), S(0);
    for (int i = 0; i < (int)drones.size() - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < (int)drones.size(); j++) {
            C++;
            if (drones[j].getID() < drones[minIndex].getID()) {
                minIndex = j;
            }
        }
        if (i != minIndex) {
            S++;
            swapDrones(i, minIndex);
        }
    }
    cout << "Selection Sort by ID successful" << endl;
    displayAll();
    cout << "Comparisons: " << C << " | Swaps: " << S << endl;
}

void Fleet::insertionSortByBattery()
{
    // TODO: descending by battery. Print: Insertion sort by battery: C comparisons, H shifts.
    int C(0), H(0);
    for (int i = 1; i < (int)drones.size(); i++) {
        Drone key = drones[i];
        int j = i - 1;

        while (j >= 0) {
            C++;
            if (drones[j].getBattery() < key.getBattery()) {
                drones[j + 1] = drones[j];
                j--;
                H++;
            }
            else {
                break;
            }
        }
        drones[j + 1] = key;
    }

    cout << "Insertion Sort by battery successful" << endl;
    displayAll();
    cout << "Comparisons: " << C << ", Shifts: " << H << endl;

}

void Fleet::sortByName()
{
    // TODO: insertion sort, alphabetical. Print: Insertion sort by name: C comparisons, H shifts.
    int C(0), H(0);
    for (int i = 1; i < (int)drones.size(); i++) {
        Drone key = drones[i];
        int j = i - 1;

        while (j >= 0) {
            C++;
            if (drones[j].getName() > key.getName()) {
                drones[j + 1] = drones[j];
                j--;
                H++;
            }
            else {
                break;
            }

        }
        drones[j + 1] = key;

    }
    cout << "Insertion Sort by name successful" << endl;
    displayAll();
    cout << "Comparisons: " << C << ", Shifts: " << H << endl;

}

bool Fleet::isSortedByID() const
{
    // TODO                                         **DONE**
    for (int i = 1; i < drones.size(); i++) {
        int j = i - 1;
        if (drones[i].getID() < drones[j].getID()) {
            return false;
        }
    }
    return true;
}

// ---------- Searching ----------

int Fleet::findIndexByID(int id) const
{
	for (int i = 0; i < drones.size(); i++) {
		if (drones[i].getID() == id) {
			return i;
		}
	}
	return -1;
}

int Fleet::linearSearchByName(const string& name) const
{
    // TODO: one comparison per drone checked; print the count; return index or -1          **DONE**
    int count(0);
    for (int i = 0; i < drones.size(); i++) {
        count++;
        if (drones[i].getName() == name) {
            int index = count - 1;
            cout << "Count: " << count << "| Index: " << index << endl;
            
            return i;
        }
    }
    int index = count - 1;
    cout << "Name not found." << endl;
    cout << "Comparisons: " << count << endl;
    return -1;
}

int Fleet::binarySearchByID(int id)
{
    // TODO: sort first if needed (print a message), then binary search.            **DONE**
    // One comparison per loop iteration. Print the count; return index or -1.
    if (!(isSortedByID())) {
        cout << "ID's not sorted, forcing selection sort by ID..." << endl;
        selectionSortByID();
        
    }
    int comparison(0);
    int left = 0;
    int mid;
    int right = (int)drones.size() - 1;
    while (left <= right) {
        comparison++;
        mid = left + (right - left) / 2;
        if (drones[mid].getID() == id) {
            cout << "Id no. " << id << " found: " << endl;
            displayDrone(mid);
            cout << endl;
            cout << "Index: " << mid << endl;
            cout << "Comparisons: " << comparison << endl;
            return mid;
        }
        else if (drones[mid].getID() < id) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    cout << "No ID found. " << endl;
    cout << "Comparisons:" << comparison << endl;
    return -1;
}

// ---------- Dispatching ----------

int Fleet::findNearestAvailable(int x, int y, double weight) const
{
    // TODO: closest drone that canDeliver; ties go to the smaller ID; -1 if none
    int bestIndex = -1;
    double bestDist = 0.0;

    for (int i = 0; i < (int)drones.size(); i++) {
        if (!drones[i].canDeliver(x, y, weight)) {
            continue; // checks for not IDLE, too heavey, or not enough battery
        }

        double d = drones[i].distanceTo(x, y);
        if (bestIndex == -1 || d < bestDist || (d == bestDist && drones[i].getID() < drones[bestIndex].getID())) {
            bestIndex = i;
            bestDist = d;
        }
    }
    return bestIndex;
}

bool Fleet::dispatchDrone(int index, int x, int y, double weight)
{
    if (!validIndex(index)) {
        cout << "Invalid index" << endl;
        return false;
    }
    if (!drones[index].canDeliver(x, y, weight)) {
        return false;
    }
    drones[index].completeDelivery(x, y, weight);
    return true;
}

bool Fleet::rechargeDrone(int id)
{
    // TODO: battery 100 and IDLE, unless MAINTENANCE; message if not found     
    int index = findIndexByID(id);
    if (index == -1) {
        cout << "Drone not found" << endl;
        return false;
    }

    if (drones[index].getStatus() == "MAINTENANCE"){
        cout << "Drone " << drones[index].getName() << " is in MAINTENANCE and cannot be recharged." << endl;
        return false;
    }
 
    drones[index].setBattery(100);
    drones[index].setStatus("IDLE");
    cout << "Drone " << drones[index].getName() << " recharged to 100% and set to IDLE." << endl;
    return true;
}

void Fleet::countByStatus() const
{
    // TODO: counts of IDLE, CHARGING, MAINTENANCE and the average battery  **DONE**
    int batteryTotal(0);
    int idle(0), charging(0), maintenance(0);
    for (int i = 0; i < drones.size(); i++) {
        batteryTotal += drones[i].getBattery();
        if (drones[i].getStatus() == "IDLE") {
            idle++;
        }
        else if (drones[i].getStatus() == "CHARGING") {
            charging++;
        }
        else if (drones[i].getStatus() == "MAINTENANCE") {
            maintenance++;
        }
    }
    cout << "Battery Total: " << batteryTotal << endl;
    cout << "Status Counts: Idle: " << idle << " | Charging: " << charging << " | Maintenance: " << maintenance << endl;
}

void Fleet::processOrders(const string& orderFile, const string& logFile)
{
    // TODO: for each order in file order, find the nearest available drone and dispatch it.
    // Write one line per order to the screen and the log, then the summary line.
    // Sum the exact distances; round only when printing.

    ifstream fin(orderFile);
    ofstream fout(logFile);
    if (!(fin) || !(fout)) {
        cout << "Error opening file" << endl;
        return;
    }
    double initBattery, finalBattery;
    int index = 0;
    int count = 0;
    int countDelivered = 0;
    double distance;
    double sum(0);
    string ID;
    int x, y;
    double weight;
    while (fin >> ID >> x >> y >> weight) {
        index = findNearestAvailable(x, y, weight);
        if (index != -1) {
            count++;
            countDelivered++;
            distance = drones[index].distanceTo(x, y);
            sum += drones[index].distanceTo(x, y);
            initBattery = drones[index].getBattery();
            dispatchDrone(index, x, y, weight);
            finalBattery = drones[index].getBattery();
            cout << "Order " << ID << ": Drone " << drones[index].getID() << "(" << drones[index].getName() << ") "
                << "distance " << distance << " " << initBattery << " -> " << finalBattery << endl;
            fout << "Order " << ID << ": Drone " << drones[index].getID() << "(" << drones[index].getName() << ") "
                << "distance " << distance << " " << initBattery << " -> " << finalBattery << endl;
        }
        else {
            count++;
            cout << "Order " << ID << ": " << "UNASSIGNED" << endl;
            fout << "Order " << ID << ": " << "UNASSIGNED" << endl;
        }

    }
    fout << "Assigned " << countDelivered << " of " << count << ". Total distance flown: " << sum << endl;
}

// ---------- Other ----------

void Fleet::shuffleFleet(unsigned long long seed)
{
    // TODO: Fisher-Yates. state = seed; for i from n-1 down to 1:
    //       j = nextRandom(state) % (i + 1), then swap drones i and j.

    unsigned long long state = seed;
    for (int i = drones.size() - 1; i > 0; i--) {
        int j = nextRandom(state) % (i + 1);
        swapDrones(i, j);
    }
    cout << "Fleet Shuffled." << endl;
}

void Fleet::displayAll() const
{
    // TODO: print every drone with its index
    for (int i = 0; i < drones.size(); i++) {
        cout << "Index " << i << ": ";
        drones[i].displayDrone();
    }
}

void Fleet::displayDrone(int index) const
{
    // TODO: check the range, then print one drone
    if (index >= 0 && drones.size()) {
        drones[index].displayDrone();
    }
    else {
        cout << "Invalid index" << endl;
    }
}

void Fleet::writeFleetToFile(const string& filename) const
{
    // TODO: same format as drones.txt plus deliveriesCompleted; one decimal for battery and payload
    ofstream fout(filename);
    if (!fout) {
        cout << "Error opening file" << endl;
        return;
    }
    for (int i = 0; i < drones.size(); i++) {
        fout << drones[i].getName() << " " << drones[i].getID() << " " << drones[i].getModel() << " " << drones[i].getBattery() << " "
            << drones[i].getMaxPayload() << " " << drones[i].getPosition(0) << " " << drones[i].getPosition(1) << " " << drones[i].getStatus() << endl;
        fout << "Deliveries Completed: " << drones[i].getDeliveriesCompleted() << endl;
    }
}
