#include<iostream>
using namespace std;

enum Color
{
	RED,
	BLACK
};

template<class K, class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	pair<K, V> _kv;
	Color _col;

	RBTreeNode(const pair<K, V>& kv)
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _col(RED)
	{}
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
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
			else return false;
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
		cur->_parent = parent;

		while (parent && parent->_col == RED)
		{
			Node* grandparent = parent->_parent;
			if (grandparent->_right == parent)
			{
				Node* uncle = grandparent->_left;
				if (uncle && uncle->_col == RED)
				{
					uncle->_col = parent->_col = BLACK;
					grandparent->_col = RED;

					cur = grandparent;
					parent = cur->_parent;
				}
				else
				{
					if (parent->_right == cur)
					{
						RotateL(grandparent);
						grandparent->_col = RED;
						parent->_col = BLACK;
					}
					else
					{
						RotateR(parent);
						RotateL(grandparent);
						grandparent->_col = RED;
						cur->_col = BLACK;
					}
				}
			}
			else
			{
				Node* uncle = grandparent->_right;
				if (uncle && uncle->_col == RED)
				{
					uncle->_col = parent->_col = BLACK;
					grandparent->_col = RED;

					cur = grandparent;
					parent = cur->_parent;
				}
				else
				{
					if (parent->_left == cur)
					{
						RotateR(grandparent);
						grandparent->_col = RED;
						parent->_col = BLACK;
					}
					else
					{
						RotateL(parent);
						RotateR(grandparent);
						grandparent->_col = RED;
						cur->_col = BLACK;
					}
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}

	void RotateL(Node* parent)
	{
		Node* grandparent = parent->_parent;
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}

		subR->_left = parent;
		parent->_parent = subR;

		if (grandparent)
		{
			if (grandparent->_right = parent)
			{
				grandparent->_right = subR;
			}
			else
			{
				grandparent->_left = subR;
			}
		}
		else
		{
			_root = subR;
		}
		subR->_parent = grandparent;
	}

	void RotateR(Node* parent)
	{
		Node* grandparent = parent->_parent;
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}

		subL->_right = parent;
		parent->_parent = subL;

		if (grandparent)
		{
			if (grandparent->_right = parent)
			{
				grandparent->_right = subL;
			}
			else
			{
				grandparent->_left = subL;
			}
		}
		else
		{
			_root = subL;
		}
		subL->_parent = grandparent;
	}

	bool IsBalance()
	{
		if (_root && _root->_col == RED)
		{
			cout << "根节点为红" << endl;
			return false;
		}

		int benchMark = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK) ++benchMark;
			cur = cur->_right;
		}

		return check(_root, 0, benchMark);
	}

	bool check(Node* root, int blackCount, int benchMark)
	{
		if (root == nullptr)
		{
			if (blackCount != benchMark)
			{
				cout << "某条路径黑色结点数量异常" << endl;
				return false;
			}
			else return true;
		}

		if (root->_col == BLACK) ++blackCount;

		if (root->_col == RED && root->_parent && root->_parent->_col == RED)
		{
			cout << "存在连续红色结点" << endl;
			return false;
		}

		return check(root->_left, blackCount, benchMark)
			&& check(root->_right, blackCount, benchMark);
	}

	void InOrder()
	{
		_InOrder(_root);
	}
protected:
	void _InOrder(Node* root)
	{
		if (root == nullptr) return;

		_InOrder(root->_left);
		cout << root->_kv.second << endl;
		_InOrder(root->_right);
	}

	Node* _root = nullptr;
};

int main()
{
	RBTree<int, int> t1;
	for (int i = 0; i < 100; ++i)
	{
		t1.Insert({ i,i });
	}
	cout << t1.IsBalance() << endl;

	t1.InOrder();
	return 0;
}