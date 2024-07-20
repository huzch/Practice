//#include<iostream>
//#include"Counter.h"
//using namespace std;
//
//int main()
//{
//	Counter<string> counter; // you need to implement this class
//	while (cin) {
//		string word;
//		cin >> word;
//		counter.count(word); // increase the counter for 'word'
//	}
//	counter.discard_less_than(2); // remove the words that occur less than twice
//	cout << counter; // print the words and their counts in a decreasing order
//}

//#include"OrderedList.h"
//
//int main()
//{
//    int n, x;
//    OrderedList* a = new AscendOrderedList, * d = new DescendOrderedList;
//    std::cin >> n;
//    for (int i = 0; i < n; ++i)
//    {
//        std::cin >> x;
//        a->insert(x);
//        d->insert(x);
//    }
//    a->printList();
//    d->printList();
//    delete a;
//    delete d;
//    return 0;
//}

//#include"BankSystem.h"
//
//int main()
//{
//	int n;
//	cin >> n;
//	string operation;
//	BankSystem bankSystem;
//	for (int i = 0; i < n; ++i)
//	{
//		cin >> operation;
//
//		try
//		{
//			if (operation == "R")
//			{
//				string name;
//				cin >> name;
//				bankSystem.removeAccount(name);
//			}
//			else if (operation == "A")
//			{
//				string name;
//				int initialBalance;
//				cin >> name >> initialBalance;
//				bankSystem.addAccount(name, initialBalance);
//			}
//			else if (operation == "T")
//			{
//				string fromName, toName;
//				int amount;
//				cin >> fromName >> toName >> amount;
//				bankSystem.transfer(fromName, toName, amount);
//			}
//		}
//		catch (const runtime_error& e)
//		{
//			cout << e.what() << endl;
//		}
//	}
//	bankSystem.getBalances();
//	return 0;
//}
//
//#include"String.h"
//
//int main()
//{
//    String s1, s2;
//    cin >> s1;
//    cin >> s2;
//    cout << s1;
//    cout << s2;
//    StringJoiner join(',');
//    cout << join(s1, s2);
//
//    cin >> s1;
//    int size = s1.getSize();
//    for (int i = 0; i < size; i++)
//    {
//        cout << s1[i];
//    }
//    return 0;
//}

#include"CatFamily.h"

int main_menu()
{
	cout << "1. Add a cat" << endl;
	cout << "2. Remove a cat" << endl;
	cout << "3. Find a cat" << endl;
	cout << "4. Print all cats" << endl;
	cout << "0. Exit this game" << endl;
	int choice;
	cin >> choice;
	return choice;
}

void add_a_cat(CatFamily& cat_family)
{
	string cat_name;
	int cat_age;
	cin >> cat_name >> cat_age;
	if (cat_family.add_a_cat(cat_name, cat_age))
		cout << "Successfully added cat: " << cat_name << endl;
	else
		cout << "Fail to add cat: " << cat_name << endl;
}

void remove_a_cat(CatFamily& cat_family)
{
	string cat_name;
	cin >> cat_name;
	if (cat_family.remove_a_cat(cat_name))
		cout << "Successfully removed cat: " << cat_name << endl;
	else
		cout << "Fail to remove cat: " << cat_name << endl;
}

void find_a_cat(CatFamily& cat_family)
{
	string cat_name;
	cin >> cat_name;
	if (cat_family.has_cat(cat_name))
	{
		cout << "Here is your cat: "
			<< cat_family.get_cat(cat_name).cat_name
			<< " of " << cat_family.get_cat(cat_name).cat_age << "years old" << endl;
	}
	else
		cout << "No such cat: " << cat_name << endl;
}

void print_all_cats(CatFamily& cat_family) {
	cout << "We have these cats:" << endl;
	for (int i = 0; i < cat_family.number_of_cats(); ++i) {
		string cat_name = cat_family.get_nth_cat(i);
		cout << '\t' << cat_family.get_cat(cat_name).cat_name
			<< " of " << cat_family.get_cat(cat_name).cat_age << "years old" << endl;
	}
}

int main()
{
	CatFamily cat_family;
	while (true) {
		int choice = main_menu();
		switch (choice) {
		case 0: cout << "See you" << endl; exit(0);
		case 1: add_a_cat(cat_family); break;
		case 2: remove_a_cat(cat_family); break;
		case 3: find_a_cat(cat_family); break;
		case 4: print_all_cats(cat_family);
		}
	}
}