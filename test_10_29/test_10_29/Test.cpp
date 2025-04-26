#include<iostream>
#include<unordered_set>
using namespace std;

string changeStr(string& s)
{
	int n = s.size();
	string s1, s2;
	for (int i = 0; i < n; i += 2) s1 += s[i];
	for (int i = 1; i < n; i += 2) s2 += s[i];
	reverse(s2.begin(), s2.end());
	return s1 + s2;
}

struct ListNode
{
	char val;
	ListNode* next;
};

char findDiff(ListNode* s, ListNode* t)
{
	unordered_set<char> hash;
	ListNode* cur = t;
	while (cur)
	{
		hash.insert(t->val);
		cur = cur->next;
	}

	cur = s;
	while (cur)
	{
		if (!hash.count(cur->val)) return cur->val;
		cur = cur->next;
	}
	return '\0';
}

void findDot(vector<vector<int>>& mat)
{
	int m = mat.size(), n = mat[0].size();
	vector<int> minRow(m, INT_MAX), maxCol(n, INT_MIN);
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			minRow[i] = min(minRow[i], mat[i][j]);
			maxCol[j] = max(maxCol[j], mat[i][j]);
		}
	}

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (mat[i][j] == minRow[i] && mat[i][j] == maxCol[j])
			{
				printf("mat[%d][%d]:%d\n", i, j, mat[i][j]);
			}
		}
	}
}

int main()
{
	string s = "ABCDEFGHIJKL";
	cout << changeStr(s) << endl;
	return 0;
}