#pragma once
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<iostream>
using namespace std;

template<class T>
class Counter
{
	friend ostream& operator<<(ostream& out, const Counter<T>& c)
	{
		vector<pair<T, int>> v(c._um.begin(), c._um.end());
		sort(v.begin(), v.end(), [](const pair<T, int>& kv1, const pair<T, int>& kv2)
			{return (kv1.second > kv2.second) || (kv1.second == kv2.second && kv1.first < kv2.first); });

		for (auto& kv : v)
		{
			out << kv.first << " " << kv.second << endl;
		}
		return out;
	}
public:
	void count(const T& word)
	{
		++_um[word];
	}

	void discard_less_than(int n)
	{
		auto it = _um.begin();
		while (it != _um.end())
		{
			if (it->second < n)
			{
				it = _um.erase(it);
			}
			else ++it;
		}
	}
private:
	unordered_map <T, int> _um;
};
