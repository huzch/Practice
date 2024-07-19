#include<iostream>
using namespace std;

//auto f1(int x)
//{}
//
//int main()
//{
//	int x;
//	cin >> x;
//	cout << x;
//	//auto p = nullptr;
//	//delete p;
//
//	f1(1);
//	return 0;
//}

//class date
//{
//private:
//    int y, m, d;
//public:
//    date() : y(0), m(0), d(0) {}
//    int year() const;
//    int month() const;
//    int day() const {
//        return d;
//    }
//    int day() {
//        return d++;
//    }
//    int addyear(int i) {
//        return y + i;
//    }
//};
//
//class A
//{
//
//};
//
//int main()
//{
//    const date d;
//    int test;
//    test = d.year();  //lineB
//    //test = d.addyear(10); //lineC
//    date d2;
//    test = d2.year();
//    test = d2.day();  //lineD
//    return 0;
//}

//int main()
//{
//	int a = 0;
//	const int& ra = a;
//	a = 2;
//	cout << a << " " << ra << endl;
//	return 0;
//}

//class Person
//{
//public:
//	virtual ~Person() { cout << "~Person()" << endl; }
//};
//
//class Student : public Person
//{
//public:
//	virtual ~Student() { cout << "~Student()" << endl; }
//};
//
//int main()
//{
//	Person* p1 = new Person;
//	Person* p2 = new Student;
//
//	delete p1;
//	delete p2;
//	return 0;
//}

#include <vector>
#include <algorithm>

int main() {
	int n = 5;
	vector<int> a;
	for (int i = 0; i < n; i++) {
		a.push_back(i + 1);
	}
	auto it1 = a.begin() + 2;
	auto it2 = a.begin() + 3;
	sort(a.begin(), a.end(), [](int a, int b) {return a > b; });
	cout << *(it1) << " " << *(it2) << endl;
	sort(it1, it2);
	cout << *(it1) << " " << *(it2) << endl;
}