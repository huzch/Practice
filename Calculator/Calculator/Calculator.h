#pragma once

//struct Term
//{
//	double _coef;//ϵ��
//	int _exp;//ָ��
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
//		cout << "����������:";
//		cin >> n;
//		_terms.reserve(n);
//		for (int i = 0; i < n; ++i)
//		{
//			double coef;
//			int exp;
//			cout << "�������" << i + 1 << "���ϵ����ָ��:";
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
//		cout << "�ö���ʽ��" << n << "��: ";
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
    // �������ʽ
    void Input()
    {
        int n;
        cout << "����������:";  // ��ʾ�������ʽ������
        cin >> n;
        for (int i = 0; i < n; ++i)
        {
            double coef, exp;
            cout << "�������" << i + 1 << "���ϵ����ָ��:";  // ��ʾ����ÿһ���ϵ����ָ��
            cin >> coef >> exp;
            _hash[exp] += coef;  // ʹ�ù�ϣ��ָ����Ϊ����ϵ����Ϊֵ��������ָͬ�����ϵ���ۼ�
        }

        // ��ϵ����0����浽_terms������
        for (auto& kv : _hash)
        {
            if (kv.second) _terms.push_back(kv);  // ���ϵ����Ϊ0���򽫸�����뵽_terms����
        }

        // ��ָ���Ӵ�С����
        sort(_terms.begin(), _terms.end(), [](const pair<double, double>& t1, const pair<double, double>& t2) {
            return t1.first > t2.first;  // ��ָ����������������
            });
    }

    // �������ʽ
    void Output()
    {
        int n = _terms.size();
        cout << "�ö���ʽ��" << n << "��: ";  // �������ʽ������
        for (int i = 0; i < n; ++i)
        {
            double exp = _terms[i].first, coef = _terms[i].second;

            // ������ţ������ǵ�һ����ϵ��Ϊ�������"+"
            if (i != 0 && coef > 0) cout << "+";

            // ���ϵ��
            if (coef == 1 && exp == 0) cout << "1";  // ������
            if (coef == -1 && exp == 0) cout << "-1";  // ������
            if (coef != 1 && coef != -1 && coef != 0) cout << coef;  // ϵ����Ϊ1��-1��0ʱ���

            // ���x��ָ��
            if (exp != 0)  // ��ָ����Ϊ0
            {
                if (coef == 1) cout << "x";  // ϵ��Ϊ1ʱ���"x"
                if (coef == -1) cout << "-x";  // ϵ��Ϊ-1ʱ���"-x"
                if (coef != 1 && coef != -1) cout << "x";  // ����ϵ�����"x"

                if (exp != 1) cout << "^" << exp;  // ָ����Ϊ1ʱ���ָ��
            }
        }
        cout << endl;
    }

    // ����ʽ���
    Polynomial Add(const Polynomial& p)
    {
        Polynomial ret = *this;  // ���Ƶ�ǰ����ʽ
        auto& terms = ret._terms;
        auto& hash = ret._hash;

        // ������������ʽ������ָͬ�����ϵ�����
        for (auto& kv : p._hash)
        {
            hash[kv.first] += kv.second;
        }

        // ���¹���_terms����������
        terms.clear();
        for (auto& kv : hash)
        {
            if (kv.second) terms.push_back(kv);
        }

        sort(terms.begin(), terms.end(), [](const pair<double, double>& t1, const pair<double, double>& t2) {
            return t1.first > t2.first;  // ��ָ����������
            });

        return ret;  // ������Ӻ�Ķ���ʽ
    }

    // ����ʽ���
    Polynomial Sub(const Polynomial& p)
    {
        Polynomial ret = *this;  // ���Ƶ�ǰ����ʽ
        auto& terms = ret._terms;
        auto& hash = ret._hash;

        // ������������ʽ������ָͬ�����ϵ�����
        for (auto& kv : p._hash)
        {
            hash[kv.first] -= kv.second;
        }

        // ���¹���_terms����������
        terms.clear();
        for (auto& kv : hash)
        {
            if (kv.second) terms.push_back(kv);
        }

        sort(terms.begin(), terms.end(), [](const pair<double, double>& t1, const pair<double, double>& t2) {
            return t1.first > t2.first;  // ��ָ����������
            });

        return ret;  // ���������Ķ���ʽ
    }

    // ����ʽ��ֵ������x��ֵ
    double Eval(double x)
    {
        double ret = 0;
        // ʹ�ø�����x�������ʽ��ֵ
        for (auto& kv : _terms)
        {
            ret += kv.second * pow(x, kv.first);  // ����ϵ����ָ������ÿһ���ֵ
        }
        return ret;  // ������ֵ���
    }

    // ����ʽ��
    Polynomial Deriv()
    {
        Polynomial ret = *this;  // ���Ƶ�ǰ����ʽ
        for (auto& kv : ret._terms)
        {
            kv.second *= kv.first;  // ϵ������ָ��
            --kv.first;  // ָ����1
        }
        return ret;  // �����󵼺�Ķ���ʽ
    }

    // ����ʽ���
    Polynomial Mul(const Polynomial& p)
    {
        Polynomial ret;
        auto& terms = ret._terms;
        auto& hash = ret._hash;

        // ��������ʽ��ÿһ�����
        for (auto& kv1 : _hash)
        {
            for (auto& kv2 : p._hash)
            {
                double coef = kv1.second * kv2.second;  // ���������ϵ��
                double exp = kv1.first + kv2.first;  // ���������ָ��
                hash[exp] += coef;  // �ϲ���ָͬ������
            }
        }

        // ���¹���_terms����������
        for (auto& kv : hash)
        {
            if (kv.second) terms.push_back(kv);
        }

        sort(terms.begin(), terms.end(), [](const pair<double, double>& t1, const pair<double, double>& t2) {
            return t1.first > t2.first;  // ��ָ����������
            });

        return ret;  // ������˺�Ķ���ʽ
    }

private:
    vector<pair<double, double>> _terms;  // �洢����ʽ�����<ָ��, ϵ��>�洢
    unordered_map<double, double> _hash;  // �ù�ϣ��洢�ָ��Ϊ����ϵ��Ϊֵ
};

class Expression
{
public:
    // ������ʽ��ֵ
    double Calculator(const string& s)
    {
        // ��������ȼ���
        unordered_map<char, int> hash = { {'(', 0}, {')', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3} };
        stack<double> nums;  // �洢������
        stack<char> ops;  // �洢�����
        int n = s.size();

        for (int i = 0; i < n; ++i)
        {
            char ch = s[i];
            if (ch == ' ') continue;  // ���Կո�
            else if (ch == '(')
            {
                ops.push(ch);  // ������ֱ����ջ
                if (!isdigit(s[i + 1])) nums.push(0);  // ��������(-2)�����������һ��0
            }
            else if (ch == ')')
            {
                // ���������ţ�ִ�������ڵ�����
                while (!ops.empty())
                {
                    char op = ops.top(); ops.pop();
                    if (op == '(') break;  // ����������ֹͣ
                    else calc(nums, op);  // ���м���
                }
            }
            else if (isdigit(ch))
            {
                // ��������
                double x = 0;
                while (isdigit(s[i]))
                {
                    x = x * 10 + (s[i] - '0');  // ��������
                    ++i;
                }
                nums.push(x);  // ������ջ
                --i;  // ����ѭ���е�++i
            }
            else
            {
                // ���������
                if (nums.empty()) nums.push(0);  // ������Ը��ſ�ͷ������0

                // �Ƚ���������ȼ�����������ȼ�����
                while (!ops.empty() && hash[ops.top()] >= hash[ch])
                {
                    char op = ops.top(); ops.pop();
                    calc(nums, op);  // ִ������
                }
                ops.push(ch);  // ��ǰ�������ջ
            }
        }

        // ����ջ��ʣ��������
        while (!ops.empty())
        {
            char op = ops.top(); ops.pop();
            calc(nums, op);  // ���ִ������
        }
        return nums.top();  // �������ս��
    }

private:
    // ��������������������Ľ��
    void calc(stack<double>& nums, char op)
    {
        if (nums.size() < 2) return;  // ���ջ�в������������򷵻�
        double b = nums.top(); nums.pop();  // ȡ���ڶ���������
        double a = nums.top(); nums.pop();  // ȡ����һ��������
        double ret = 0;

        // ���������ִ����Ӧ����
        if (op == '+') ret = a + b;
        else if (op == '-') ret = a - b;
        else if (op == '*') ret = a * b;
        else if (op == '/')
        {
            if (b == 0) throw string("�������");  // ��������쳣
            ret = a / b;
        }
        else if (op == '^') ret = pow(a, b);  // ������
        nums.push(ret);  // ����������ջ
    }
};