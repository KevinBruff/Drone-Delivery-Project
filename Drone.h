// Drone.h
// ESE 224 Fall 2026 Midterm Project (starter code)
// Team members: TODO

#ifndef DRONE_H
#define DRONE_H

#include <string>
using namespace std;

// Battery and delivery constants (Section 3.1)
const double BATTERY_PER_UNIT = 2.0;  // battery % per grid unit with no payload
const double PAYLOAD_FACTOR = 0.2;    // extra fraction of battery per kg
const double SAFETY_RESERVE = 20.0;   // minimum battery % left after a delivery
const double LOW_BATTERY = 30.0;      // below this after a delivery -> CHARGING

class Drone {
private:
    string name;
    int ID;
    string model;
    double battery;
    double maxPayload;
    int position[2];
    string status;
    int deliveriesCompleted;

public:
    // Constructors
    Drone();
    Drone(const string& n, int id, const string& m, double b, double p,
        int x, int y, const string& s);

    // Accessors
    string getName() const;
    int getID() const;
    string getModel() const;
    double getBattery() const;
    double getMaxPayload() const;
    int getPosition(int index) const;
    string getStatus() const;
    int getDeliveriesCompleted() const;

    // Mutators: print an error, leave the member unchanged, and return false if invalid
    void setName(const string& n);
    bool setID(int id);
    bool setModel(const string& m);
    bool setBattery(double b);
    bool setMaxPayload(double p);
    bool setPosition(int index, int value);
    bool setStatus(const string& s);

    // Delivery methods
    double distanceTo(int x, int y) const;
    double batteryNeeded(int x, int y, double weight) const;
    bool canDeliver(int x, int y, double weight) const;
    void completeDelivery(int x, int y, double weight);

    // Display and comparison
    void displayDrone() const;
    bool operator==(const Drone& other) const;
};

#endif
