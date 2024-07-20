#pragma once
#include<iostream>
using namespace std;

struct Cat
{
	string cat_name;
	int cat_age;

	Cat(const string& name = "", int age = 0)
		: cat_name(name)
		, cat_age(age)
	{}
};

struct CatFamily
{
	Cat _c[100];
	int _size = 0;
	int _capacity = 100;

	bool add_a_cat(const string& name, int age)
	{
		if (has_cat(name) || _size == _capacity) return false;
		_c[_size++] = Cat(name, age);
		return true;
	}

	bool remove_a_cat(const string& name)
	{
		for (int i = 0; i < _size; ++i)
		{
			if (_c[i].cat_name == name)
			{
				for (int j = i; j < _size - 1; ++j)
				{
					_c[j] = _c[j + 1];
				}
				--_size;
				return true;
			}
		}
		return false;
	}

	bool has_cat(const string& name) const
	{
		for (int i = 0; i < _size; ++i)
		{
			if (_c[i].cat_name == name)
			{
				return true;
			}
		}
		return false;
	}

	Cat& get_cat(const string& name)
	{
		for (int i = 0; i < _size; ++i)
		{
			if (_c[i].cat_name == name)
			{
				return _c[i];
			}
		}
	}

	string& get_nth_cat(int i)
	{
		return _c[i].cat_name;
	}

	int number_of_cats() const
	{
		return _size;
	}
};