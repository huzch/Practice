#include "Bus.hpp"


Bus::Bus(int id, int capacity, Station* station)
    : id(id)
    , capacity(capacity)
    , passengers(new Passenger* [MAX_NUM_PASSENGERS])
    , num_passengers(0)
    , station(station)
    , stop(true)
{}

Bus::~Bus()
{
    delete[] passengers;
}

// 发车，下一站是next
bool Bus::depart(Station* next)
{
    if (!stop || next == nullptr) return false;

    station->get_on(this);
    station = next;
    stop = false;
    return true;
}

// 到站
bool Bus::arrive()
{
    if (stop) return false;

    stop = true;
    for (int i = 0; i < num_passengers; )
    {
        if (passengers[i]->get_destination() == station->get_id())
        {
            passengers[i]->get_off();
            for (int j = i; j < num_passengers - 1; ++j)
            {
                passengers[j] = passengers[j + 1];
            }
            --num_passengers;
        }
        else ++i;
    }
    return true;
}

// 乘客上车
bool Bus::get_on(Passenger* passenger)
{
    if (num_passengers < capacity && passenger->get_on())
    {
        passengers[num_passengers++] = passenger;
        return true;
    }
    return false;
}