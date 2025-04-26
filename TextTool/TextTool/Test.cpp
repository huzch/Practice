#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
#include<queue>
#include<set>
#include<unordered_map>
using namespace std;

int Search(const string& t, const string& p)
{
	string s = p + '#' + t;
	int n = s.size(), m = p.size();
	vector<int> pi(n);

	int count = 0;
	for (int i = 1; i < n; ++i)
	{
		int len = pi[i - 1];
		while (len && s[i] != s[len]) len = pi[len - 1];
		if (s[i] == s[len])
		{
			pi[i] = len + 1;
			if (pi[i] == m) ++count;
		}
	}
	return count;
}

void CountWords(const string& filename, const set<string>& words, bool all = true)
{
	ifstream file(filename);
	string line;
	int lineNum = 1;

	unordered_map<string, pair<int, list<int>>> hash;
	while (getline(file, line))
	{
		for (auto& word : words)
		{
			int count = Search(line, word);
			if (count > 0)
			{
				hash[word].first += count;
				hash[word].second.push_back(lineNum);
			}
		}
		++lineNum;
	}

	if (all)
	{
		//全部打印
		for (auto& word : words)
		{
			cout << "word:" << word << endl;
			cout << "  count:" << hash[word].first << endl;
			cout << "  lines:";
			auto& lines = hash[word].second;
			for (auto& line : lines)
			{
				cout << line << " ";
			}
			cout << endl;
		}
	}
	else
	{
		//TopK打印
		typedef pair<int, string> PIS;
		int k = 5;
		priority_queue<PIS, vector<PIS>, greater<PIS>> heap;//小堆
		for (auto& word : words)
		{
			int count = hash[word].first;
			if (heap.size() < k)
			{
				heap.push({ count,word });
			}
			else
			{
				if (heap.top().first < count)
				{
					heap.pop();
					heap.push({ count,word });
				}
			}
		}

		while (heap.size())
		{
			auto kv = heap.top();
			heap.pop();
			string word = kv.second;

			cout << "word:" << word << endl;
			cout << "  count:" << hash[word].first << endl;
			cout << "  lines:";
			auto& lines = hash[word].second;
			for (auto& line : lines)
			{
				cout << line << " ";
			}
			cout << endl;
		}
	}
}


int main()
{
	set<string> words;
	string word;
	while (cin >> word)
	{
		words.insert(word);
	}

	string filename = "testCode.txt";
	CountWords(filename, words, false);

	return 0;
}

