#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
using namespace std;

#include"ExpressionTree.h"

void Test1()
{
	string s = "+*5^x2*8x";
	ExpressionTree t(s);

	t.Print();
	cout << endl;

	t.Assign('x', 9);
	t.Print();
	cout << endl;

	cout << t.Value() << endl;
}

void Test2()
{
	string s = "+*5^x2*8x";
	ExpressionTree t1(s);
	ExpressionTree t2(t1);
	t1.Print();
	cout << endl;
	t2.Print();
	cout << endl;

	ExpressionTree t3 = Compound('+', t1, t2);
	t3.Print();
	cout << endl;
}

int main()
{
	Test1();

	return 0;
}