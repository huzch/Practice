#include<iostream>
using namespace std;

template<class K, class V>
struct BSTreeNode
{
	BSTreeNode<K, V>* _left;
	BSTreeNode<K, V>* _right;
	pair<K, V> _kv;

	BSTreeNode(const pair<K, V>& kv)
		: _left(nullptr)
		, _right(nullptr)
		, _kv(kv)
	{}
};

template<class K, class V>
class BSTree
{
	typedef BSTreeNode<K, V> Node;
public:
	BSTree()
	{}

	BSTree(const BSTree<K, V>& t)
	{
		_root = Copy(t._root);
	}

	~BSTree()
	{
		Destroy(_root);
	}

	BSTree<K, V>& operator=(BSTree<K, V> t)
	{
		swap(_root, t._root);
		return* this;
	}

	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(kv);
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		return true;
	}

	bool InsertR(const pair<K, V>& kv)
	{
		return _InsertR(_root, kv);
	}

	bool Find(const pair<K, V>& kv)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				cur = cur->_left;
			}
			else
			{
				return true;
			}
		}
		return false;
	}

	bool FindR(const pair<K, V>& kv)
	{
		return _FindR(_root, kv);
	}

	bool Erase(const pair<K, V>& kv)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				if (cur->_right == nullptr)
				{
					if (parent == nullptr)
					{
						_root = _root->_left;
					}
					else
					{
						if (parent->_right == cur)
						{
							parent->_right = cur->_left;
						}
						else
						{
							parent->_left = cur->_left;
						}
					}
					delete cur;
				}
				else if (cur->_left == nullptr)
				{
					if (parent == nullptr)
					{
						_root = _root->_right;
					}
					else
					{
						if (parent->_right == cur)
						{
							parent->_right = cur->_right;
						}
						else
						{
							parent->_left = cur->_right;
						}
					}
					delete cur;
				}
				else
				{
					Node* pminRight = cur;
					Node* minRight = cur->_right;
					while (minRight->_left)
					{
						pminRight = minRight;
						minRight = minRight->_left;
					}
					
					swap(cur->_kv, minRight->_kv);

					if (pminRight->_right == minRight)
					{
						pminRight->_right = minRight->_right;
					}
					else
					{
						pminRight->_left = minRight->_right;
					}
					delete minRight;
				}
				return true;
			}
		}
		return false;
	}

	bool EraseR(const pair<K, V>& kv)
	{
		return _EraseR(_root, kv);
	}

	void InOrder()
	{
		_InOrder(_root);
	}
protected:
	Node* Copy(Node* root)
	{
		if (root == nullptr)
		{
			return nullptr;
		}

		Node* newRoot = new Node(root->_kv);
		newRoot->_left = Copy(root->_left);
		newRoot->_right = Copy(root->_right);

		return newRoot;
	}

	void Destroy(Node*& root)
	{
		if (root == nullptr)
		{
			return;
		}

		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
		root = nullptr;
	}

	bool _InsertR(Node*& root, const pair<K, V>& kv)
	{
		if (root == nullptr)
		{
			root = new Node(kv);
			return true;
		}

		if (root->_kv.first < kv.first)
		{
			return _InsertR(root->_right, kv);
		}
		else if (root->_kv.first > kv.first)
		{
			return _InsertR(root->_left, kv);
		}
		else
		{
			return false;
		}
	}

	bool _FindR(Node* root, const pair<K, V>& kv)
	{
		if (root == nullptr)
		{
			return false;
		}

		if (root->_kv.first < kv.first)
		{
			return _FindR(root->_right, kv);
		}
		else if (root->_kv.first > kv.first)
		{
			return _FindR(root->_left, kv);
		}
		else
		{
			return true;
		}
	}

	bool _EraseR(Node*& root, const pair<K, V>& kv)
	{
		if (root == nullptr)
		{
			return false;
		}

		if (root->_kv.first < kv.first)
		{
			return _EraseR(root->_right, kv);
		}
		else if (root->_kv.first > kv.first)
		{
			return _EraseR(root->_left, kv);
		}
		else
		{
			Node* del = root;
			if (root->_right == nullptr)
			{
				root = root->_left;
			}
			else if (root->_left == nullptr)
			{
				root = root->_right;
			}
			else
			{
				Node* minRight = root->_right;
				while (minRight->_left)
				{
					minRight = minRight->_left;
				}

				swap(root->_kv, minRight->_kv);

				return _EraseR(root->_right, kv);//优化，使代码更简洁
			}
			delete del;
			return true;
		}
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_kv.first << endl;
		_InOrder(root->_right);
	}

	Node* _root = nullptr;
};

int main()
{
	BSTree<int, int> t1;
	for (int i = 0; i < 100; ++i)
	{
		t1.Insert({ i,i });
		t1.InsertR({ i + 100, i + 100 });
	}

	t1.InOrder();

	for (int i = 0; i < 50; ++i)
	{
		t1.Erase({ i,i });
		t1.EraseR({ i + 100, i + 100 });
	}

	t1.InOrder();

	return 0;
}