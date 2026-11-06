// main.cpp
// ESE 224 Fall 2026 Midterm Project (starter code)
// Team members: TODO
//
// This skeleton compiles and shows the menu. Fill in each TODO (see Section 5 of the handout).

#include "Drone.h"
#include "Fleet.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

void login()
{
    ifstream fin("users.txt");
    if (!fin) {
        cout << "Could not open users.txt" << endl;
        return;
    }
    int flag = 0;
    string username, password;
    string inpUser, inpPass;
    cout << "Input Username: ";
    cin >> inpUser;
    cout << "Input Password: ";
    cin >> inpPass;
    while (fin >> username >> password) {
        if (inpUser == username && inpPass == password) {
            cout << "Welcome, " << username << "!" << endl;
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        cout << "Invalid Username/Password" << endl;
        return login();
    }

}

// TODO: read every drone from the file until the end of the file,
//       add each one to the fleet, and print how many were loaded.
void loadFleet(Fleet& fleet, const string& filename)
{
    ifstream fin(filename);
    if (!fin) {
        cout << "Unable to open file" << endl;
        return;
    }
    string name;
    int ID;
    string model;
    double battery;
    double maxPayload;
    int x;
    int y;
    string status;
    int deliveriesCompleted;
    while (fin >> name >> ID >> model >> battery >> maxPayload >> x >> y >> status) {
        Drone drone(name, ID, model, battery, maxPayload, x, y, status);
        fleet.addDrone(drone);
    }
    cout << "Loaded " << fleet.getSize() << " drones." << endl;
}

void showMenu()
{
    cout << endl
        << "===== SkyDrop Menu =====" << endl
        << " 1. Display all drones" << endl
        << " 2. Sort by ID" << endl
        << " 3. Sort by battery" << endl
        << " 4. Sort by name" << endl
        << " 5. Shuffle fleet" << endl
        << " 6. Search by name" << endl
        << " 7. Search by ID" << endl
        << " 8. Find nearest available drone" << endl
        << " 9. Dispatch a delivery" << endl
        << "10. Recharge a drone" << endl
        << "11. Fleet status summary" << endl
        << "12. Process orders file" << endl
        << "13. Write fleet to file" << endl
        << "14. Add a new drone" << endl
        << " 0. Quit" << endl;
}

int main()
{
    string name;
    int ID;
    string model;
    double battery;
    double maxPayload;
    int x;
    int y;
    string status;
    int deliveriesCompleted;

    login();

    Fleet fleet;
    loadFleet(fleet, "drones.txt");

    int choice = -1;
    int index, seed;
    double weight;
    string fout, fin;
    string inpName;
    int inpID;
    while (choice != 0)
    {
        showMenu();
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            fleet.displayAll();
            break;
        case 2:
            fleet.selectionSortByID();
            break;
        case 3:
            fleet.insertionSortByBattery();
            break;
        case 4:
            fleet.sortByName();
            break;
        case 5:
            cout << "Input seed: ";
            cin >> seed;
            fleet.shuffleFleet(seed);
            break;
        case 6:
            // TODO: Implement search by name
            cout << "Input name: ";
            cin >> name;
            fleet.linearSearchByName(name);
            break;
        case 7:
            // TODO: Implement search by ID
            cout << "Input ID: ";
            cin >> ID;
            fleet.binarySearchByID(ID);
            break;
        case 8: {
            cout << "Input position and weight (x y weight): ";
            cin >> x >> y >> weight;
            int found = fleet.findNearestAvailable(x, y, weight);
            if (found == -1) {
                cout << "No available drone." << endl;
            }
            else {
                cout << "Nearest drone at index " << found << ":" << endl;
                fleet.displayDrone(found);
            }
            break;
        }
        case 9:
            cout << "Input index, position and weight (index x y weight): ";
            cin >> index >> x >> y >> weight;
            if (fleet.dispatchDrone(index, x, y, weight)) {
                cout << "Drone dispatched. Deliveries completed: "
                    << fleet.getDrone(index).getDeliveriesCompleted() << endl;
            }
            else {
                cout << "Dispatch failed." << endl;
            }
            break;
        case 10:
            cout << "Input drone ID you want to charge: ";
            cin >> ID;
            fleet.rechargeDrone(ID);
            break;
        case 11:
            fleet.countByStatus();
            break;
        case 12:
            fin = "orders.txt";
            fout = "delivery_log.txt";
            fleet.processOrders(fin, fout);
            break;
        case 13:
            fin = "fleet_output.txt";
            fleet.writeFleetToFile(fin);
            break;
        case 14: {
            cout << "Enter name: ";
            cin >> name;
            cout << endl;
            while (1) {
                cout << "Enter ID: ";
                cin >> ID;
                if (ID > -1 && ID < 1000) {
                    break;
                }
                cout << "Invalid ID" << endl;
            }
            cout << endl;
            cout << endl;
            while (1) {
                cout << "Enter model: ";
                cin >> model;
                if (model == "Condor" || model == "Kestrel" || model == "Falcon") {
                    break;
                }
                cout << "Invalid model name" << endl;
            }
            cout << endl;
            
            while (1) {
                cout << "Enter battery: ";
                cin >> battery;
                if (battery >= 0 && battery <= 100) {
                    break;
                }
                cout << "Invalid battery" << endl;
            }

            cout << endl;

            while (1) {
                cout << "Enter max payload: ";
                cin >> maxPayload;
                if (maxPayload >= 0) {
                    break;
                }
                cout << "Invalid payload" << endl;
            }

            cout << endl;
            cout << "Enter position (x y): ";
            cin >> x >> y;
            cout << endl;
            
            while (1) {
                cout << "Enter status: ";
                cin >> status;
                if (status == "IDLE" || status == "MAINTENANCE" || status == "CHARGING") {
                    break;
                }
                cout << "Invalid status" << endl;
            }
            cout << endl;

            Drone newDrone(name, ID, model, battery, maxPayload, x, y, status);
            fleet.addDrone(newDrone);
            break;
        }
        case 0:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid option." << endl;
        }
    }
    return 0;
}