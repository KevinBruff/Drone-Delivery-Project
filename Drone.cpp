// Drone.cpp
// ESE 224 Fall 2026 Midterm Project (starter code)
// Team members: TODO
//
// Every function below compiles but does nothing useful yet.
// Replace each TODO with your implementation (see Section 3 of the handout).

#include "Drone.h"
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// ---------- Constructors ----------

Drone::Drone()
{
    ID = -1;
    battery = 100.0;
    maxPayload = 0.0;
    position[0] = 0;
    position[1] = 0;
    status = "IDLE";
    deliveriesCompleted = 0;
}

Drone::Drone(const string& n, int id, const string& m, double b, double p,
    int x, int y, const string& s) : Drone()
{
    setName(n), setID(id), setModel(m), setBattery(b), setMaxPayload(p), setPosition(0, x), setPosition(1, y), setStatus(s);
}

// ---------- Accessors ----------

string Drone::getName() const { return name; }
int Drone::getID() const { return ID; }
string Drone::getModel() const { return model; }
double Drone::getBattery() const { return battery; }
double Drone::getMaxPayload() const { return maxPayload; }
string Drone::getStatus() const { return status; }
int Drone::getDeliveriesCompleted() const { return deliveriesCompleted; }

int Drone::getPosition(int index) const
{
    // TODO: index 0 is x, index 1 is y; any other index prints an error and returns -1
    if (index == 0 || index == 1) {
        return position[index];
    }
    cout << "Error: position index must be 0 or 1 (got " << index << ")." << endl;
    return -1;
}

// ---------- Mutators ----------

void Drone::setName(const string& n)
{
    name = n;
}

bool Drone::setID(int id)
{
    if (id > 0)
    {
        ID = id;
        return true;
    }
    return false;
}

bool Drone::setModel(const string& m)
{
    if (m == "Kestrel" || m == "Falcon" || m == "Condor")
    {
        model = m;
        return true;
    }
    return false;
}

bool Drone::setBattery(double b)
{
    if (b >= 0 && b <= 100)
    {
        battery = b;
        return true;
    }
    return false;
}

bool Drone::setMaxPayload(double p)
{
    if (p > 0)
    {
        maxPayload = p;
        return true;
    }
    return false;
}

bool Drone::setPosition(int index, int value)
{
	if (index != 0 && index != 1) {
		cout << "Error: position index must be 0 (x) or 1 (y) (got " << index << ")" << endl;
		return false;
	}
    if (value < 0) {
        cout << "Error: position value must be non-negative (got " << value << ")." << endl;
        return false;
    }
    position[index] = value;
    return true;
}

bool Drone::setStatus(const string& s)
{
    if (s == "IDLE" || s == "CHARGING" || s == "MAINTENANCE")
    {
        status = s;
        return true;
    }
    return false;
}

// ---------- Delivery methods ----------

double Drone::distanceTo(int x, int y) const
{
    return sqrt(pow(x - position[0], 2) + pow(y - position[1], 2));
}

double Drone::batteryNeeded(int x, int y, double weight) const
{
    return distanceTo(x, y) * BATTERY_PER_UNIT * (1 + PAYLOAD_FACTOR * weight);
}

bool Drone::canDeliver(int x, int y, double weight) const
{
    if (status == "IDLE" && weight <= maxPayload)
    {
        double needed = batteryNeeded(x, y, weight);
        if (battery - needed >= SAFETY_RESERVE)
        {
            return true;
        }
    }
    return false;
}

void Drone::completeDelivery(int x, int y, double weight)
{
    battery -= batteryNeeded(x, y, weight);
    setPosition(0, x);
    setPosition(1, y);
    deliveriesCompleted++;
    if (battery < LOW_BATTERY)
    {
        setStatus("CHARGING");
    }
}

// ---------- Display and comparison ----------

void Drone::displayDrone() const
{
    cout << "Name: " << name << ", "
    << "ID: " << ID << ", "
        << "Model: " << model << ", "
        << "Battery: " << battery << ", "
        << "Max Payload: " << maxPayload << ", "
        << "Position: (" << position[0] << ", " << position[1] << ")"
        << ", Status: " << status
        << ", Deliveries Completed: " << deliveriesCompleted << endl;
}

bool Drone::operator==(const Drone& other) const
{
    if (ID == other.ID)
    {
        return true;
    }
    return false;
}