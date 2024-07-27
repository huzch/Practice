#include<iostream>
#include<vector>
using namespace std;

template<class K, class V>
struct HashNode
{
	HashNode<K, V>* _next;
	pair<K, V> _kv;

	HashNode(const pair<K, V>& kv)
		: _next(nullptr)
		, _kv(kv)
	{}
};

template<class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>
struct HashFunc<string>
{
	size_t operator()(const string& s)
	{
		size_t hash = 0;
		for (auto& ch : s)
		{
			hash = hash * 31 + ch;
		}
		return hash;
	}
};

template<class K, class V, class Hash = HashFunc<K>>
class HashTable
{
	typedef HashNode<K, V> Node;
public:
	HashTable()
		: _n(0)
	{
		_tables.resize(10);
	}

	~HashTable()
	{
		for (auto& bucket : _tables)
		{
			Node* cur = bucket;
			while (cur)
			{
				Node* next = cur->_next;
				delete cur;
				cur = next;
			}
		}
	}

	Node* Find(const K& key)
	{
		for (auto& bucket : _tables)
		{
			Node* cur = bucket;
			while (cur)
			{
				if (Hash()(cur->_kv.first) == Hash()(key))
				{
					return cur;
				}
				else
				{
					cur = cur->_next;
				}
			}
		}
		return nullptr;
	}

	bool Insert(const pair<K, V>& kv)
	{
		if (Find(kv.first))
		{
			return false;
		}

		if (_n == _tables.size())
		{
			size_t newSize = 2 * _n;
			vector<Node*> newTable(newSize);
			for (auto& bucket : _tables)
			{
				Node* cur = bucket;
				while (cur)
				{
					Node* next = cur->_next;
					size_t hashi = Hash()(cur->_kv.first) % newSize;
					cur->_next = newTable[hashi];
					newTable[hashi] = cur;
					cur = next;
				}
			}
			_tables.swap(newTable);
		}

		Node* newNode = new Node(kv);
		size_t hashi = Hash()(kv.first) % _tables.size();
		newNode->_next = _tables[hashi];
		_tables[hashi] = newNode;
		++_n;
		return true;
	}

	bool Erase(const K& key)
	{
		size_t hashi = key % _tables.size();
		Node* prev = nullptr;
		Node* cur = _tables[hashi];
		while (cur)
		{
			if (Hash()(cur->_kv.first) == Hash()(key))
			{
				if (prev == nullptr)
				{
					_tables[hashi] = cur->_next;
				}
				else
				{
					prev->_next = cur->_next;
				}
				delete cur;
				return true;
			}
			else
			{
				prev = cur;
				cur = cur->_next;
			}
		}
		return false;
	}
protected:
	vector<Node*> _tables;
	size_t _n;
};

int main()
{
	HashTable<int, int> h;
	for (int i = 0; i < 100; ++i)
	{
		h.Insert({ i,i });
	}

	for (int i = 0; i < 100; ++i)
	{
		h.Erase(i);
	}
	return 0;
}