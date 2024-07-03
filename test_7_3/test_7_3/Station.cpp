#include "Station.hpp"


Station::Station(int id)
    : id(id)
    , passengers(new Passenger* [MAX_NUM_PASSENGERS])
    , num_passengers(0)
{}

Station::~Station()
{
    delete[] passengers;
}

bool Station::add_passenger(Passenger* passenger)
{
    if (num_passengers < MAX_NUM_PASSENGERS)
    {
        passengers[num_passengers++] = passenger;
        return true;
    }
    return false;
}

// �˿��ϳ�������ǰ��ĳ˿����ϳ�������ʵ���ϳ�����
int Station::get_on(Bus* bus)
{
    int count = 0;
    for (int i = 0; i < num_passengers; )
    {
        if (bus->get_num_passengers() < bus->get_capacity() && bus->get_on(passengers[i]))
        {
            for (int j = i; j < num_passengers - 1; ++j)
            {
                passengers[j] = passengers[j + 1];
            }
            --num_passengers;
            ++count;
        }
        else ++i;
    }
    return count;
}