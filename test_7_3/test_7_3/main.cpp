#include <iostream>

#include "Passenger.hpp"
#include "Station.hpp"
#include "Bus.hpp"

using namespace std;

const int MAX = 1000;

int main()
{
    int num_passengers, num_stations, num_buses;
    cin >> num_passengers >> num_stations >> num_buses;
    Passenger* passengers[MAX];
    Station* stations[MAX];
    Bus* buses[MAX];
    for (int i = 0; i < num_passengers; i++)
    {
        string name;
        int destination;
        cin >> name >> destination;
        passengers[i] = new Passenger(i, name, destination);
        passengers[i]->print();
    }
    for (int i = 0; i < num_stations; i++)
    {
        stations[i] = new Station(i);
        if (i == num_stations - 1)
        {
            break;
        }
        int x = 0;
        while (cin >> x) {
            if (x == -1) {
                break;
            }
            stations[i]->add_passenger(passengers[x]);
        }
        stations[i]->print();
    }
    for (int i = 0; i < num_buses; i++) {
        int capacity;
        cin >> capacity;
        buses[i] = new Bus(i, capacity, stations[0]);
        buses[i]->print();
    }

    int op, id, next;
    bool ret;
    Station* station;
    while (cin >> op) {
        if (!cin || op == -1) {
            break;
        }
        cin >> id;
        switch (op) {
        case 0:
            next = buses[id]->get_station()->get_id() + 1;
            station = nullptr;
            if (next < num_stations) {
                station = stations[next];
            }
            ret = buses[id]->depart(station);
            cout << "depart " << id << ": " << boolalpha << ret << endl;
            break;
        case 1:
            ret = buses[id]->arrive();
            cout << "arrive " << id << ": " << boolalpha << ret << endl;
            break;
        case 2:
            passengers[id]->print();
            break;
        case 3:
            stations[id]->print();
            break;
        case 4:
            buses[id]->print();
            break;
        }
    }

    for (int i = 0; i < num_buses; i++) {
        delete buses[i];
    }
    for (int i = 0; i < num_stations; i++) {
        delete stations[i];
    }
    for (int i = 0; i < num_passengers; i++) {
        delete passengers[i];
    }
    return 0;
}