#pragma once

//struct Term
//{
//	double _coef;//系数
//	int _exp;//指数
//
//	Term(double coef = 0, int exp = 0)
//		: _coef(coef)
//		, _exp(exp)
//	{}
//};
//
//class Polynomial
//{
//public:
//	void Input()
//	{
//		int n;
//		cout << "请输入项数:";
//		cin >> n;
//		_terms.reserve(n);
//		for (int i = 0; i < n; ++i)
//		{
//			double coef;
//			int exp;
//			cout << "请输入第" << i + 1 << "项的系数和指数:";
//			cin >> coef >> exp;
//			if (coef != 0)
//			{
//				if (_hash.count(exp))
//				{
//					_terms[_hash[exp]]._coef += coef;
//				}
//				else
//				{
//					_terms.push_back({ coef, exp });
//					_hash[exp] = i;
//				}
//			}
//		}
//
//		sort(_terms.begin(), _terms.end(), [](const Term& t1, const Term& t2) {
//			return t1._exp > t2._exp;
//			});
//
//		for (int i = 0; i < _terms.size(); ++i)
//		{
//			_hash[_terms[i]._exp] = i;
//		}
//	}
//
//	void Print()
//	{
//		int n = _terms.size();
//		cout << "该多项式有" << n << "项: ";
//		for (int i = 0; i < n; ++i)
//		{
//			auto& term = _terms[i];
//
//			if (i != 0 && term._coef > 0) cout << "+";
//
//			if (term._coef != 1 && term._coef != -1) cout << term._coef;
//			if (term._coef != 0 && term._exp != 0)
//			{
//				cout << "x";
//				if (term._exp != 1) cout << "^" << term._exp;
//			}
//
//			//cout << term._coef << " " << term._exp << " ";
//		}
//		cout << endl;
//	}
//
//	Polynomial Add(Polynomial& p)
//	{
//		Polynomial ret = *this;
//		auto& terms = ret._terms;
//		auto& hash = ret._hash;
//		for (auto& term : p._terms)
//		{
//			double coef = term._coef;
//			int exp = term._exp;
//			if (hash.count(exp))
//			{
//				terms[hash[exp]]._coef += coef;
//			}
//			else
//			{
//				hash[exp] = terms.size();
//				terms.push_back({ coef, exp });
//			}
//		}
//
//		sort(terms.begin(), terms.end(), [](const Term& t1, const Term& t2) {
//			return t1._exp > t2._exp;
//			});
//
//		for (int i = 0; i < terms.size(); ++i)
//		{
//			if (terms[i]._coef == 0)
//			{
//				terms.erase(terms.begin() + i);
//				--i;
//			}
//		}
//		return ret;
//	}
//
//	Polynomial Sub(Polynomial& p)
//	{
//		Polynomial ret = *this;
//		auto& terms = ret._terms;
//		auto& hash = ret._hash;
//		for (auto& term : p._terms)
//		{
//			double coef = term._coef;
//			int exp = term._exp;
//			if (hash.count(exp))
//			{
//				terms[hash[exp]]._coef -= coef;
//			}
//			else
//			{
//				hash[exp] = terms.size();
//				terms.push_back({ coef, exp });
//			}
//		}
//
//		sort(terms.begin(), terms.end(), [](const Term& t1, const Term& t2) {
//			return t1._exp > t2._exp;
//			});
//
//		for (int i = 0; i < terms.size(); ++i)
//		{
//			if (terms[i]._coef == 0)
//			{
//				terms.erase(terms.begin() + i);
//				--i;
//			}
//		}
//		return ret;
//	}
//
//	double Eval(double x)
//	{
//		double ret = 0;
//		for (auto& term : _terms)
//		{
//			ret += term._coef * pow(x, term._exp);
//		}
//		return ret;
//	}
//
//	Polynomial Deriv()
//	{
//		Polynomial ret = *this;
//		auto& terms = ret._terms;
//		for (int i = 0; i < terms.size(); ++i)
//		{
//			terms[i]._coef *= terms[i]._exp;
//			--terms[i]._exp;
//		}
//		return ret;
//	}
//
//	Polynomial Mul(Polynomial& p)
//	{
//		Polynomial ret;
//		auto& terms = ret._terms;
//		auto& hash = ret._hash;
//		for (int i = 0; i < _terms.size(); ++i)
//		{
//			for (int j = 0; j < p._terms.size(); ++j)
//			{
//				double coef = _terms[i]._coef * p._terms[j]._coef;
//				int exp = _terms[i]._exp + p._terms[j]._exp;
//				if (hash.count(exp))
//				{
//					terms[hash[exp]]._coef += coef;
//				}
//				else
//				{
//					hash[exp] = terms.size();
//					terms.push_back({ coef, exp });
//				}
//			}
//		}
//
//		sort(terms.begin(), terms.end(), [](const Term& t1, const Term& t2) {
//			return t1._exp > t2._exp;
//			});
//
//		for (int i = 0; i < terms.size(); ++i)
//		{
//			if (terms[i]._coef == 0)
//			{
//				terms.erase(terms.begin() + i);
//				--i;
//			}
//		}
//		return ret;
//	}
//private:
//	vector<Term> _terms;
//	unordered_map<int, int> _hash;
//};

class Polynomial
{
public:
    // 输入多项式
    void Input()
    {
        int n;
        cout << "请输入项数:";  // 提示输入多项式的项数
        cin >> n;
        for (int i = 0; i < n; ++i)
        {
            double coef, exp;
            cout << "请输入第" << i + 1 << "项的系数和指数:";  // 提示输入每一项的系数和指数
            cin >> coef >> exp;
            _hash[exp] += coef;  // 使用哈希表将指数作为键，系数作为值，处理相同指数项的系数累加
        }

        // 将系数非0的项保存到_terms向量中
        for (auto& kv : _hash)
        {
            if (kv.second) _terms.push_back(kv);  // 如果系数不为0，则将该项加入到_terms向量
        }

        // 按指数从大到小排序
        sort(_terms.begin(), _terms.end(), [](const pair<double, double>& t1, const pair<double, double>& t2) {
            return t1.first > t2.first;  // 按指数（键）降序排序
            });
    }

    // 输出多项式
    void Output()
    {
        int n = _terms.size();
        cout << "该多项式有" << n << "项: ";  // 输出多项式的项数
        for (int i = 0; i < n; ++i)
        {
            double exp = _terms[i].first, coef = _terms[i].second;

            // 输出符号：若不是第一项且系数为正，输出"+"
            if (i != 0 && coef > 0) cout << "+";

            // 输出系数
            if (coef == 1 && exp == 0) cout << "1";  // 常数项
            if (coef == -1 && exp == 0) cout << "-1";  // 常数项
            if (coef != 1 && coef != -1 && coef != 0) cout << coef;  // 系数不为1、-1或0时输出

            // 输出x和指数
            if (exp != 0)  // 若指数不为0
            {
                if (coef == 1) cout << "x";  // 系数为1时输出"x"
                if (coef == -1) cout << "-x";  // 系数为-1时输出"-x"
                if (coef != 1 && coef != -1) cout << "x";  // 其他系数输出"x"

                if (exp != 1) cout << "^" << exp;  // 指数不为1时输出指数
            }
        }
        cout << endl;
    }

    // 多项式相加
    Polynomial Add(const Polynomial& p)
    {
        Polynomial ret = *this;  // 复制当前多项式
        auto& terms = ret._terms;
        auto& hash = ret._hash;

        // 遍历参数多项式，将相同指数项的系数相加
        for (auto& kv : p._hash)
        {
            hash[kv.first] += kv.second;
        }

        // 重新构建_terms向量并排序
        terms.clear();
        for (auto& kv : hash)
        {
            if (kv.second) terms.push_back(kv);
        }

        sort(terms.begin(), terms.end(), [](const pair<double, double>& t1, const pair<double, double>& t2) {
            return t1.first > t2.first;  // 按指数降序排序
            });

        return ret;  // 返回相加后的多项式
    }

    // 多项式相减
    Polynomial Sub(const Polynomial& p)
    {
        Polynomial ret = *this;  // 复制当前多项式
        auto& terms = ret._terms;
        auto& hash = ret._hash;

        // 遍历参数多项式，将相同指数项的系数相减
        for (auto& kv : p._hash)
        {
            hash[kv.first] -= kv.second;
        }

        // 重新构建_terms向量并排序
        terms.clear();
        for (auto& kv : hash)
        {
            if (kv.second) terms.push_back(kv);
        }

        sort(terms.begin(), terms.end(), [](const pair<double, double>& t1, const pair<double, double>& t2) {
            return t1.first > t2.first;  // 按指数降序排序
            });

        return ret;  // 返回相减后的多项式
    }

    // 多项式求值，给定x的值
    double Eval(double x)
    {
        double ret = 0;
        // 使用给定的x计算多项式的值
        for (auto& kv : _terms)
        {
            ret += kv.second * pow(x, kv.first);  // 根据系数和指数计算每一项的值
        }
        return ret;  // 返回求值结果
    }

    // 多项式求导
    Polynomial Deriv()
    {
        Polynomial ret = *this;  // 复制当前多项式
        for (auto& kv : ret._terms)
        {
            kv.second *= kv.first;  // 系数乘以指数
            --kv.first;  // 指数减1
        }
        return ret;  // 返回求导后的多项式
    }

    // 多项式相乘
    Polynomial Mul(const Polynomial& p)
    {
        Polynomial ret;
        auto& terms = ret._terms;
        auto& hash = ret._hash;

        // 两个多项式的每一项相乘
        for (auto& kv1 : _hash)
        {
            for (auto& kv2 : p._hash)
            {
                double coef = kv1.second * kv2.second;  // 计算新项的系数
                double exp = kv1.first + kv2.first;  // 计算新项的指数
                hash[exp] += coef;  // 合并相同指数的项
            }
        }

        // 重新构建_terms向量并排序
        for (auto& kv : hash)
        {
            if (kv.second) terms.push_back(kv);
        }

        sort(terms.begin(), terms.end(), [](const pair<double, double>& t1, const pair<double, double>& t2) {
            return t1.first > t2.first;  // 按指数降序排序
            });

        return ret;  // 返回相乘后的多项式
    }

private:
    vector<pair<double, double>> _terms;  // 存储多项式的项，按<指数, 系数>存储
    unordered_map<double, double> _hash;  // 用哈希表存储项，指数为键，系数为值
};

class Expression
{
public:
    // 计算表达式的值
    double Calculator(const string& s)
    {
        // 运算符优先级表
        unordered_map<char, int> hash = { {'(', 0}, {')', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3} };
        stack<double> nums;  // 存储操作数
        stack<char> ops;  // 存储运算符
        int n = s.size();

        for (int i = 0; i < n; ++i)
        {
            char ch = s[i];
            if (ch == ' ') continue;  // 忽略空格
            else if (ch == '(')
            {
                ops.push(ch);  // 左括号直接入栈
                if (!isdigit(s[i + 1])) nums.push(0);  // 处理类似(-2)的情况，补充一个0
            }
            else if (ch == ')')
            {
                // 遇到右括号，执行括号内的运算
                while (!ops.empty())
                {
                    char op = ops.top(); ops.pop();
                    if (op == '(') break;  // 遇到左括号停止
                    else calc(nums, op);  // 进行计算
                }
            }
            else if (isdigit(ch))
            {
                // 处理数字
                double x = 0;
                while (isdigit(s[i]))
                {
                    x = x * 10 + (s[i] - '0');  // 解析数字
                    ++i;
                }
                nums.push(x);  // 数字入栈
                --i;  // 抵消循环中的++i
            }
            else
            {
                // 处理运算符
                if (nums.empty()) nums.push(0);  // 如果是以负号开头，补充0

                // 比较运算符优先级，处理高优先级运算
                while (!ops.empty() && hash[ops.top()] >= hash[ch])
                {
                    char op = ops.top(); ops.pop();
                    calc(nums, op);  // 执行运算
                }
                ops.push(ch);  // 当前运算符入栈
            }
        }

        // 处理栈中剩余的运算符
        while (!ops.empty())
        {
            char op = ops.top(); ops.pop();
            calc(nums, op);  // 逐个执行运算
        }
        return nums.top();  // 返回最终结果
    }

private:
    // 根据运算符计算两个数的结果
    void calc(stack<double>& nums, char op)
    {
        if (nums.size() < 2) return;  // 如果栈中不足两个数，则返回
        double b = nums.top(); nums.pop();  // 取出第二个操作数
        double a = nums.top(); nums.pop();  // 取出第一个操作数
        double ret = 0;

        // 根据运算符执行相应运算
        if (op == '+') ret = a + b;
        else if (op == '-') ret = a - b;
        else if (op == '*') ret = a * b;
        else if (op == '/')
        {
            if (b == 0) throw string("除零错误");  // 处理除零异常
            ret = a / b;
        }
        else if (op == '^') ret = pow(a, b);  // 幂运算
        nums.push(ret);  // 将运算结果入栈
    }
};