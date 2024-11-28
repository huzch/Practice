#pragma once

struct TreeNode
{
	double _num;
	char _ch;
	bool _isCh;
	bool _isOp;
	TreeNode* _left;
	TreeNode* _right;

	TreeNode(double num)
		: _num(num)
		, _ch(0)
		, _isCh(false)
		, _isOp(false)
		, _left(nullptr)
		, _right(nullptr)
	{}

	TreeNode(char ch, bool isOp)
		: _num(0)
		, _ch(ch)
		, _isCh(true)
		, _isOp(isOp)
		, _left(nullptr)
		, _right(nullptr)
	{}
};

class ExpressionTree
{
	typedef TreeNode Node;
	friend ExpressionTree Compound(char op, const ExpressionTree& t1, const ExpressionTree& t2)
	{
		Node* root = new Node(op, true);
		ExpressionTree t3(root);
		root->_left = t3.CopyTree(t1._root);
		root->_right = t3.CopyTree(t2._root);
		return t3;
	}
public:
	ExpressionTree(Node* root)
		: _root(root)
	{}

	ExpressionTree(const string& s)
	{
		int i = 0;
		_root = BuildTree(s, i);
	}

	ExpressionTree(const ExpressionTree& t)
	{
		_root = CopyTree(t._root);
	}

	~ExpressionTree()
	{
		DestroyTree(_root);
	}

	void Print()
	{
		_Print(_root);
	}

	void Assign(char var, double x)
	{
		_Assign(_root, var, x);
	}

	double Value()
	{
		return _Value(_root);
	}

	void Diff(char var, double x)
	{
		_Diff(_root, var, x);
	}

private:
	Node* BuildTree(const string& s, int& i)
	{
		if (i == s.size())
		{
			return nullptr;
		}

		if (isspace(s[i])) //空白字符，跳过
		{
			while (i < s.size() && isspace(s[i]))
			{
				++i;
			}

			if (i == s.size())
			{
				return nullptr;
			}
		}

		Node* root = nullptr;
		if (isdigit(s[i])) //运算常量，为叶子节点
		{
			root = new Node(s[i++] - '0');
		}
		else if (isalpha(s[i])) //运算变量，为叶子节点
		{
			root = new Node(s[i++], false);
		}
		else //运算符，为非叶节点
		{
			root = new Node(s[i++], true);
			root->_left = BuildTree(s, i);
			root->_right = BuildTree(s, i);
		}

		return root;
	}

	Node* CopyTree(Node* root)
	{
		if (root == nullptr)
		{
			return nullptr;
		}

		Node* copyRoot = new Node(0);
		copyRoot->_num = root->_num;
		copyRoot->_ch = root->_ch;
		copyRoot->_isCh = root->_isCh;
		copyRoot->_isOp = root->_isOp;
		copyRoot->_left = CopyTree(root->_left);
		copyRoot->_right = CopyTree(root->_right);
		return copyRoot;
	}

	void DestroyTree(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		DestroyTree(root->_left);
		DestroyTree(root->_right);
		delete root;
	}

	void _Print(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		if (root->_isOp)
		{
			cout << "(";
		}
		_Print(root->_left);

		if (root->_isCh)
		{
			cout << root->_ch;
		}
		else
		{
			cout << root->_num;
		}

		_Print(root->_right);
		if (root->_isOp)
		{
			cout << ")";
		}
	}

	void _Assign(Node* root, char var, double x)
	{
		if (root == nullptr)
		{
			return;
		}

		if (IsVar(root))
		{
			root->_num = x;
			root->_isCh = false;
		}
		_Assign(root->_left, var, x);
		_Assign(root->_right, var, x);
	}

	double _Value(Node* root)
	{
		if (root->_left == nullptr && root->_right == nullptr) //叶子节点为运算数
		{
			return root->_num;
		}

		double leftVal = _Value(root->_left);
		double rightVal = _Value(root->_right);

		return Calc(root->_ch, leftVal, rightVal); //非叶节点为运算符
	}

	double Calc(char op, double x, double y)
	{
		if (op == '+')
		{
			return x + y;
		}
		else if (op == '-')
		{
			return x - y;
		}
		else if (op == '*')
		{
			return x * y;
		}
		else if (op == '/')
		{
			return x / y;
		}
		else if (op == '^')
		{
			return pow(x, y);
		}
	}

	void _Diff(Node* root, char var, double x)
	{
		if (root->_isOp)
		{
			if (root->_ch == '+' || root->_ch == '-')
			{
				if (IsCon(root->_left) && IsCon(root->_right))
				{
					ToZero(root->_left);
					ToZero(root->_right);
				}
				else if (IsCon(root->_left) && IsVar(root->_right))
				{
					ToZero(root->_left);
					ToOne(root->_right);
				}
				else if (IsVar(root->_left) && IsCon(root->_right))
				{
					ToOne(root->_left);
					ToZero(root->_right);
				}
				else if (IsVar(root->_left) && IsVar(root->_right))
				{
					ToOne(root->_left);
					ToOne(root->_right);
				}
			}
			else if (root->_ch == '*')
			{
				if (IsCon(root->_left) && IsCon(root->_right))
				{
					ToZero(root->_left);
					ToZero(root->_right);
				}
				else if (IsCon(root->_left) && IsVar(root->_right))
				{
					ToOne(root->_right);
				}
				else if (IsVar(root->_left) && IsCon(root->_right))
				{
					ToOne(root->_left);
				}
				else if (IsVar(root->_left) && IsVar(root->_right))
				{
					ToTwo(root->_left);
				}
			}
			else if (root->_ch == '/')
			{
				if (IsCon(root->_left) && IsCon(root->_right))
				{
					ToZero(root->_left);
					ToOne(root->_right);
				}
				else if (IsCon(root->_left) && IsVar(root->_right))
				{
					//dy/dx = -a/x^2
				}
				else if (IsVar(root->_left) && IsCon(root->_right))
				{
					ToOne(root->_left);
				}
				else if (IsVar(root->_left) && IsVar(root->_right))
				{
					ToZero(root->_left);
					ToOne(root->_right);
				}
			}
			else if (root->_ch == '^')
			{
				if (IsCon(root->_left) && IsCon(root->_right))
				{
					ToZero(root->_left);
					ToOne(root->_right);
				}
				else if (IsCon(root->_left) && IsVar(root->_right))
				{
					//dy/dx = a^x*lna
				}
				else if (IsVar(root->_left) && IsCon(root->_right))
				{
					//dy/dx = a*x^(a-1)
				}
				else if (IsVar(root->_left) && IsVar(root->_right))
				{
					//dy/dx = (lnx+1)*x^x
				}
			}
		}
	}

	bool IsVar(Node* root)
	{
		return root->_isCh && !root->_isOp;
	}

	bool IsCon(Node* root)
	{
		return !root->_isCh;
	}

	void ToTwo(Node* root)
	{
		root->_num = 2;
		root->_isCh = false;
		root->_isOp = false;
	}

	void ToOne(Node* root)
	{
		root->_num = 1;
		root->_isCh = false;
		root->_isOp = false;
	}

	void ToZero(Node* root)
	{
		root->_num = 0;
		root->_isCh = false;
		root->_isOp = false;
	}

private:
	Node* _root;
};
