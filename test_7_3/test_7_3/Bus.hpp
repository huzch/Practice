#pragma once
#ifndef BUS_H_
#define BUS_H_

#include <algorithm>

#include "Passenger.hpp"
#include "Station.hpp"

class Station;

class Bus {
public:
    static const int MAX_NUM_PASSENGERS = 1000;

    Bus(int id, int capacity, Station* station);
    ~Bus();

    Bus(const Bus&) = delete;
    Bus& operator= (const Bus&) = delete;

    // 操作成功时返回true，失败时返回false
    // 发车，下一站是next
    bool depart(Station* next);
    // 到站
    bool arrive();

    // 乘客上车
    bool get_on(Passenger* passenger);

private:
    int id;
    int capacity;
    Passenger** passengers;
    int num_passengers;
    Station* station; // 当前到站
    bool stop;

public:
    // getter
    int get_id() const {
        return id;
    }
    int get_num_passengers() const {
        return num_passengers;
    }
    int get_capacity() const {
        return capacity;
    }
    Station* get_station() const {
        return station;
    }

    void print() const {
        std::string names[MAX_NUM_PASSENGERS];
        if (num_passengers > 0) {
            for (int i = 0; i < num_passengers; i++) {
                names[i] = passengers[i]->get_name();
            }
            std::sort(names, names + num_passengers);
        }

        std::cout << "Bus id: " << get_id();
        std::cout << ", num_passengers: " << get_num_passengers();
        std::cout << ", passengers: [";
        for (int i = 0; i < num_passengers; i++) {
            // std::cout << passengers[i]->get_name();
            std::cout << names[i];
            if (i != num_passengers - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]";
        std::cout << std::endl;
    }
};

#endif