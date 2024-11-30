#pragma once

#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
using namespace std;

struct TreeNode
{
	double _num;
	char _ch;
	string _func;
	bool _isCh;
	bool _isOp;
	bool _isFunc;
	TreeNode* _left;
	TreeNode* _right;

	TreeNode(double num)
		: _num(num)
		, _ch(0)
		, _func("")
		, _isCh(false)
		, _isOp(false)
		, _isFunc(false)
		, _left(nullptr)
		, _right(nullptr)
	{}

	TreeNode(char ch, bool isOp, TreeNode* left = nullptr, TreeNode* right = nullptr)
		: _num(0)
		, _ch(ch)
		, _func("")
		, _isCh(true)
		, _isOp(isOp)
		, _isFunc(false)
		, _left(left)
		, _right(right)
	{}

	TreeNode(string func, TreeNode* right = nullptr)
		: _num(0)
		, _ch(0)
		, _func(func)
		, _isCh(false)
		, _isOp(false)
		, _isFunc(true)
		, _left(nullptr)
		, _right(right)
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

	void Diff(char var)
	{
		_Diff(_root, var);
	}

	void MergeConst()
	{
		_MergeConst(_root);
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
		else if (isalpha(s[i])) 
		{
			string func = "";
			int j = i;
			int cnt = 0;
			while (j < s.size() && isalpha(s[j]) && cnt < 3) //默认函数名长度都为3
			{
				func += s[j++];
				++cnt;
			}

			if (j < s.size() && s[j] == '(' && cnt == 3) //运算函数，为叶子节点
			{
				i = j + 1; //跳过'('
				root = new Node(func);
				int k = s.find(')', i);
				string t = s.substr(i, k - i);
				int tmp = 0;
				root->_right = BuildTree(t, tmp); //默认使用右指针指向函数参数
				i = k + 1; //跳过')'
			}
			else //运算变量，为叶子节点
			{
				root = new Node(s[i++], false);
			}
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
		copyRoot->_func = root->_func;
		copyRoot->_isCh = root->_isCh;
		copyRoot->_isOp = root->_isOp;
		copyRoot->_isFunc = root->_isFunc;
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
		else if (root->_isFunc)
		{
			cout << root->_func;
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
			ToNum(root, x);
		}
		_Assign(root->_left, var, x);
		_Assign(root->_right, var, x);
	}

	double _Value(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}

		if (root->_left == nullptr && root->_right == nullptr) //叶子节点为运算数
		{
			return root->_num;
		}

		double leftVal = _Value(root->_left);
		double rightVal = _Value(root->_right);

		if (root->_isFunc) //非叶节点为运算函数
		{
			return Calc(root->_func, rightVal);
		}
		else //非叶节点为运算符
		{
			return Calc(root->_ch, leftVal, rightVal); 
		}
	}

	double Calc(const string& func, double x)
	{
		if (func == "sin")
		{
			return sin(x);
		}
		else if (func == "cos")
		{
			return cos(x);
		}
		else if (func == "tan")
		{
			return tan(x);
		}
		else if (func == "exp")
		{
			return exp(x);
		}
		else if (func == "log")
		{
			return log(x);
		}
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

	void _Diff(Node* root, char var)
	{
		if (root == nullptr)
		{
			return;
		}

		if (IsCon(root)) //常量
		{
			ToNum(root, 0);
		}
		else if (IsVar(root)) //变量
		{
			if (root->_ch == var)
			{
				ToNum(root, 1);
			}
			else
			{
				ToNum(root, 0);
			}
		}
		else if (root->_isFunc)
		{
			Node* x = root->_right;
			if (root->_func == "sin")
			{
				ToOp(root, '*');
				
				root->_left = x;

				root->_right = new Node("cos", CopyTree(x));
				//root->_right = CopyTree(x);

				_Diff(x, var);
			}
			else if (root->_func == "cos")
			{
				ToOp(root, '*');

				root->_left = x;

				root->_right = new Node('*', true);
				root->_right->_left = new Node(-1);
				root->_right->_right = new Node("sin", CopyTree(x));
				//root->_right->_right->_right = CopyTree(x);

				_Diff(x, var);
			}
			else if (root->_func == "tan")
			{
				ToOp(root, '*');

				root->_left = x;

				root->_right = new Node('/', true);
				root->_right->_left = new Node(1);
				root->_right->_right = new Node('*', true);
				root->_right->_right->_left = new Node("cos", CopyTree(x));
				//root->_right->_right->_left->_right = CopyTree(x);
				root->_right->_right->_right = new Node("cos", CopyTree(x));
				//root->_right->_right->_right->_right = CopyTree(x);
			}
			else if (root->_func == "exp")
			{
				ToOp(root, '*');

				root->_left = x;

				root->_right = new Node("exp", CopyTree(x));
				//root->_right->_right = CopyTree(x);

				_Diff(x, var);
			}
			else if (root->_func == "log")
			{
				ToOp(root, '*');

				root->_left = x;

				root->_right = new Node('/', true, new Node(1), CopyTree(x));
				//root->_right->_left = new Node(1);
				//root->_right->_right = CopyTree(x);

				_Diff(x, var);
			}
		}
		else //运算符
		{
			Node* u = root->_left;
			Node* v = root->_right;
			if (root->_ch == '+' || root->_ch == '-')
			{
				_Diff(u, var);
				_Diff(v, var);
			}
			else if (root->_ch == '*')
			{
				root->_ch = '+';

				root->_left = new Node('*', true, u, v);
				//root->_left->_left = u;
				//root->_left->_right = v;

				root->_right = new Node('*', true, CopyTree(u), CopyTree(v));
				//root->_right->_left = CopyTree(u);
				//root->_right->_right = CopyTree(v);

				_Diff(u, var);
				_Diff(root->_right->_right, var);
			}
			else if (root->_ch == '/')
			{
				root->_left = new Node('-', true);
				root->_left->_left = new Node('*', true, u, v);
				//root->_left->_left->_left = u;
				//root->_left->_left->_right = v;
				root->_left->_right = new Node('*', true, CopyTree(u), CopyTree(v));
				//root->_left->_right->_left = CopyTree(u);
				//root->_left->_right->_right = CopyTree(v);

				root->_right = new Node('^', true, CopyTree(v), new Node(2));
				//root->_right->_left = CopyTree(v);
				//root->_right->_right = new Node(2);

				_Diff(u, var);
				_Diff(root->_left->_right->_right, var);
			}
			else if (root->_ch == '^')
			{
				root->_ch = '*';

				root->_left = new Node('^', true, u, v);
				//root->_left->_left = u;
				//root->_left->_right = v;

				root->_right = new Node('+', true);
				root->_right->_left = new Node('*', true);
				root->_right->_left->_left = CopyTree(v);
				root->_right->_left->_right = new Node("log", CopyTree(u));
				//root->_right->_left->_right->_right = CopyTree(u);
				root->_right->_right = new Node('*', true);
				root->_right->_right->_left = CopyTree(v);
				root->_right->_right->_right = new Node('/', true, CopyTree(u), CopyTree(u));
				//root->_right->_right->_right->_left = CopyTree(u);
				//root->_right->_right->_right->_right = CopyTree(u);

				_Diff(root->_right->_left->_left, var);
				_Diff(root->_right->_right->_right->_left, var);
			}
		}
	}

	bool IsVar(Node* root)
	{
		return root && root->_isCh && !root->_isOp;
	}

	bool IsCon(Node* root)
	{
		return root && !root->_isCh && !root->_isFunc;
	}

	void ToNum(Node* root, double x)
	{
		root->_num = x;
		root->_isCh = false;
		root->_isOp = false;
		root->_isFunc = false;
		DestroyTree(root->_left);
		root->_left = nullptr;
		DestroyTree(root->_right);
		root->_right = nullptr;
	}

	void ToOp(Node* root, char op)
	{
		root->_ch = op;
		root->_isCh = true;
		root->_isOp = true;
		root->_isFunc = false;
	}

	void _MergeConst(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		if (root->_isFunc)
		{
			_MergeConst(root->_right);

			Node* x = root->_right;
			if (IsCon(x))
			{
				double ret = Calc(root->_func, x->_num);
				ToNum(root, ret);
			}
		}
		else if (root->_isOp)
		{
			_MergeConst(root->_left);
			_MergeConst(root->_right);

			Node* x = root->_left;
			Node* y = root->_right;
			if (IsCon(x) && IsCon(y))
			{
				double ret = Calc(root->_ch, x->_num, y->_num);
				ToNum(root, ret);
			}
			else if (IsCon(x) && !IsCon(y))
			{
				if ((root->_ch == '+' && x->_num == 0) || (root->_ch == '*' && x->_num == 1))
				{
					ToCh(root, y);
				}
				else if ((root->_ch == '*' && x->_num == 0) || (root->_ch == '/' && x->_num == 0) 
					  || (root->_ch == '^' && x->_num == 0))
				{
					ToNum(root, 0);
				}
			}
			else if (!IsCon(x) && IsCon(y))
			{
				if ((root->_ch == '+' && y->_num == 0) || (root->_ch == '*' && y->_num == 1))
				{
					ToCh(root, x);
				}
				else if (root->_ch == '*' && y->_num == 0)
				{
					ToNum(root, 0);
				}
				else if (root->_ch == '^' && y->_num == 0)
				{
					ToNum(root, 1);
				}
			}
		}
	}

	void ToCh(Node* root, Node* ch)
	{
		root->_ch = ch->_ch;
		root->_isCh = true;
		root->_isOp = true;
		root->_isFunc = false;
		root->_left = ch->_left;
		root->_right = ch->_right;
	}

private:
	Node* _root;
};
