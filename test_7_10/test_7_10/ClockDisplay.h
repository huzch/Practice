#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class NumberDispaly
{
private:
	const int limit;   // 用于进位
	int value;
public:
	NumberDispaly() = default;

	NumberDispaly(int l, int v = 0)
		: limit(l)
		, value(v)
	{}

	bool increse()   // return的bool可以用来反馈是否进位了  
	{
		++value;
		if (value == limit)
		{
			value = 0;
			return true;
		}
		return false;
	}

	void print()
	{
		if (value < 10) cout << "0";
		cout << value;
	}
};

class ClockDisplay
{
private:
	NumberDispaly hour;
	NumberDispaly minute;
public:
	ClockDisplay()
		: hour(24)
		, minute(60)
	{}

	ClockDisplay(int hour, int minute)
		: hour(24, hour)
		, minute(60, minute)
	{}

	void increse()
	{
		if (minute.increse())
		{
			hour.increse();
		}
	}

	void print()
	{
		hour.print();
		cout << ":";
		minute.print();
		cout << endl;
	}
};