#include"ExpressionTree.h"

void Test1()
{
	string s = "+++*3^ *3*2^ x2x6";
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

void Test3()
{
	string s = "^ x ^ x 2 ";
	ExpressionTree t(s);
	t.Print();
	cout << endl;

	t.Diff('x');
	t.Print();
	cout << endl;

	t.Assign('x', 3);
	cout << t.Value() << endl;
}

void Test4()
{
	string s = "+++*3^ *3*2^ x2x6";
	ExpressionTree t(s);
	t.Print();
	cout << endl;

	t.Diff('x');
	t.Print();
	cout << endl;

	t.MergeConst();
	t.Print();
	cout << endl;
}

int main()
{
	Test4();

	return 0;
}