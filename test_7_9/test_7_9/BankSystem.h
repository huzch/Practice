#pragma once
#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

class BankSystem
{
public:
	void addAccount(const string& name, int initialBalance)
	{
		if (_m.count(name))
		{
			throw runtime_error("Account already exists!");
		}
		_v.push_back(name);
		_m[name] = initialBalance;
	}

	void removeAccount(const string& name)
	{
		auto it = find(_v.begin(), _v.end(), name);
		if (it == _v.end())
		{
			throw runtime_error("Account not found!");
		}
		_v.erase(it);
		_m.erase(name);
	}

	void transfer(const string& fromName, const string& toName, int amount)
	{
		if (amount < 0)
		{
			throw runtime_error("Invalid transfer amount!");
		}
		if (_m.count(fromName) == 0 || _m.count(toName) == 0)
		{
			throw runtime_error("Account not found!");
		}
		if (_m[fromName] < amount)
		{
			throw runtime_error("Insufficient balance!");
		}
		_m[fromName] -= amount;
		_m[toName] += amount;
	}

	void getBalances()
	{
		for (auto& name : _v)
		{
			cout << name << " " << _m[name] << endl;
		}
	}
protected:
	vector<string> _v;
	unordered_map<string, int> _m;
};