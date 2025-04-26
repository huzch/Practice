#include<iostream>
#include<vector>
using namespace std;

template<class T>
int Compare(vector<T>& A, vector<T>& B)
{
	int n1 = A.size(), n2 = B.size();
	int i = 0, j = 0;
	while (i < n1 && j < n2 && A[i] == B[j]) ++i, ++j;

	if (i == n1 && j == n2) return 0;
	else if (i == n1 && j < n2) return -1;
	else if (i < n1 && j < n2 && A[i] < B[j]) return -1;
	else return 1;
}

template<class T>
struct ListNode
{
	T _val;
	ListNode<T>* _prev;
	ListNode<T>* _next;

	ListNode(const T& val)
		: _val(val)
	{}
};

typedef ListNode<T> ListNode;


ListNode* Swap(ListNode* head, ListNode* n1, ListNode* n2)
{
	ListNode* Guard = new ListNode(-1);
	Guard->_next = head;

	ListNode* prev1 = Guard, *prev2 = Guard;
	while (prev1->_next != n1) prev1 = prev1->_next;
	while (prev2->_next != n2) prev2 = prev2->_next;

	ListNode* next1 = n1->_next, *next2 = n2->_next;
	n1->_next = next2;
	prev1->_next = n2;

	if (n1->_next == n2)
	{
		n2->_next = n1;
	}
	else
	{
		prev2->_next = n1;
		n2->_next = next1;
	}

	head = Guard->_next;
	delete Guard;
	return head;
}

pair<ListNode*, ListNode*> Group(ListNode* head)
{
	ListNode* odd = new ListNode(-1);
	ListNode* even = new ListNode(-1);

	ListNode* cur = head, *tail1 = odd, *tail2 = even;
	do
	{
		if (cur->_val % 2 != 0)
		{
			tail1->_next = cur;
			tail1 = tail1->_next;
		}
		else
		{
			tail2->_next = cur;
			tail2 = tail2->_next;
		}
		cur = cur->_next;
	} while (cur != head);

	return { odd, even };
}

void merge(ListNode* head1, ListNode* head2)
{
	ListNode* tail1 = head1, *tail2 = head2;
	while (tail1->_next != head1) tail1 = tail1->_next;
	while (tail2->_next != head2) tail2 = tail2->_next;

	tail1->_next = head2;
	tail2->_next = head1;
}