#include <iostream>
using namespace std;


struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution
{
public:
	ListNode* reverseKGroup(ListNode* head, int k)
	{
		int count = 0;
		ListNode* temp = head;
		while (temp)
		{
			++count;
			temp = temp->next;
		}

		int num = count / k;
		ListNode* dummyhead = new ListNode(0);
		dummyhead->next = head;
		ListNode* pre = dummyhead;
		ListNode* cur = head;
		ListNode* beg = cur;
		ListNode* end = cur->next;

		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < k - 1; j++)
			{
				beg->next = end->next;
				end->next = pre->next;
				pre->next = end;
				end = beg->next;
			}
			pre = beg;
			cur = end;
			beg = beg->next;
			end = end->next;
			//print(dummyhead->next);
		}
		cur = dummyhead->next;
		delete dummyhead;
		return cur;
	}
	void print(ListNode* head)
	{
		ListNode* temp = head;
		while (temp)
		{
			cout << temp->val << ' ';
			temp = temp->next;
		}
		cout << endl;
	}
};

int main()
{
	ListNode* n1 = new ListNode(1);
	ListNode* n2 = new ListNode(2);
	ListNode* n3 = new ListNode(3);
	ListNode* n4 = new ListNode(4);
	ListNode* n5 = new ListNode(5);
	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = n5;

	ListNode* ret = Solution().reverseKGroup(n1, 1);
	return 0;
}