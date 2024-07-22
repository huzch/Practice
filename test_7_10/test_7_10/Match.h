#pragma once
#include <iostream>
#include <string>
using namespace std;

bool match(const string& p, const string& s)
{
    int cur1 = 0, cur2 = 0;
    while (cur1 < p.size() && cur2 < s.size())
    {
        if (p[cur1] == s[cur2])
        {
            ++cur1;
            ++cur2;
        }
        else if (p[cur1] == '+')
        {
            ++cur1;
            while (cur2 < s.size() && s[cur2 - 1] == s[cur2])
            {
                ++cur2;
            }
        }
        else return false;
    }
    return cur2 == s.size();
}