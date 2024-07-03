#pragma once
#ifndef PASSENGER_H_
#define PASSENGER_H_

#include <iostream>
#include <string>

class Passenger
{
public:
    Passenger(int id, const std::string& name, int destination) 
        : id(id)
        , name(name)
        , destination(destination)
        , _aboard(false) 
    {}

    Passenger(const Passenger&) = delete;
    Passenger& operator= (const Passenger&) = delete;

    // 操作成功时返回true，失败时返回false
    bool get_on()
    {
        if (_aboard)
        {
            return false;
        }
        else
        {
            _aboard = true;
            return true;
        }
    }

    bool get_off()
    {
        if (!_aboard)
        {
            return false;
        }
        else
        {
            _aboard = false;
            return true;
        }
    }

    // getter
    bool aboard() const {
        return _aboard;
    }
    std::string get_name() const {
        return name;
    }
    int get_destination() const {
        return destination;
    }

    void print() const {
        std::cout << "Passenger name: " << get_name();
        std::cout << ", destination: " << get_destination();
        std::cout << ", aboard: " << std::boolalpha << aboard();
        std::cout << std::endl;
    }

private:
    int id;
    std::string name;
    int destination;
    bool _aboard;
};

#endif