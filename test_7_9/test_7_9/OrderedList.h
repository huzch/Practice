#pragma once
#include<iostream>
using namespace std;

struct ListNode
{
	int _val;
	ListNode* _prev;
	ListNode* _next;

	ListNode(int val = 0)
		: _val(val)
		, _prev(nullptr)
		, _next(nullptr)
	{}
};

class OrderedList
{
public:
	OrderedList()
		: _head(new ListNode)
	{
		_head->_prev = _head;
		_head->_next = _head;
	}

	~OrderedList()
	{
		auto cur = _head->_next;
		while (cur != _head)
		{
			auto next = cur->_next;
			delete cur;
			cur = next;
		}
		delete _head;
	}

	void printList() const
	{
		auto cur = _head->_next;
		while (cur != _head)
		{
			cout << cur->_val << " ";
			cur = cur->_next;
		}
		cout << endl;
	}

	virtual void insert(int val) = 0;
protected:
	ListNode* _head;
};

class AscendOrderedList :public OrderedList
{
	virtual void insert(int val)
	{
		auto cur = _head->_next;
		while (cur != _head && cur->_val < val)
		{
			cur = cur->_next;
		}

		auto node = new ListNode(val);
		auto prev = cur->_prev;
		prev->_next = node;
		node->_prev = prev;
		node->_next = cur;
		cur->_prev = node;
	}
};

class DescendOrderedList :public OrderedList
{
	virtual void insert(int val)
	{
		auto cur = _head->_next;
		while (cur != _head && cur->_val > val)
		{
			cur = cur->_next;
		}

		auto node = new ListNode(val);
		auto prev = cur->_prev;
		prev->_next = node;
		node->_prev = prev;
		node->_next = cur;
		cur->_prev = node;
	}
};