#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
using namespace std;

int findSubstringInWraproundString(string s)
{
    int n = s.size();
    vector<int> dp(n + 1, 1);
    s = ' ' + s;

    unordered_map<char, int> hash;
    for (int i = 1; i <= n; ++i)
    {
        if (s[i] - s[i - 1] == 'b' - 'a'
            || s[i] - s[i - 1] == 'a' - 'z')
        {
            dp[i] += dp[i - 1];
        }

        if (!hash.count(s[i])) hash[s[i]] = dp[i];
        else if (dp[i] > hash[s[i]]) hash[s[i]] = dp[i];
    }

    int ret = 0;
    for (auto& kv : hash) ret += kv.second;
    return ret;
}

int main()
{
    string s = "cac";
    int ret = findSubstringInWraproundString(s);
    return 0;
}