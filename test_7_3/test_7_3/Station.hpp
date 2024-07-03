#pragma once
#ifndef STATION_H_
#define STATION_H_

#include <iostream>

#include "Passenger.hpp"
#include "Bus.hpp"

class Bus;

class Station {
public:
    static const int MAX_NUM_PASSENGERS = 1000;

    Station(int id);
    ~Station();

    Station(const Station&) = delete;
    Station& operator= (const Station&) = delete;

    bool add_passenger(Passenger* passenger);

    // �˿��ϳ�������ǰ��ĳ˿����ϳ�������ʵ���ϳ�����
    int get_on(Bus* bus);

private:
    int id;
    Passenger** passengers; // �򳵳˿��б�
    int num_passengers; // �򳵳˿�����

public:
    // getter
    int get_id() const {
        return id;
    }
    int get_num_passengers() const {
        return num_passengers;
    }

    void print() const {
        std::cout << "Station id: " << get_id();
        std::cout << ", num_passengers: " << get_num_passengers();
        std::cout << ", passengers: [";
        for (int i = 0; i < num_passengers; i++) {
            std::cout << passengers[i]->get_name();
            if (i != num_passengers - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]";
        std::cout << std::endl;
    }
};

#endif