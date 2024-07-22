#include<iostream>
using namespace std;

void AdjustDown(int* a, int n, int parent)
{
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n && a[child] < a[child + 1])
		{
			++child;
		}

		if (a[parent] < a[child])
		{
			swap(a[child], a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else break;
	}
}

void HeapSort(int* a, int n)
{
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(a, n, i);
	}

	int end = n - 1;
	while (end >= 0)
	{
		swap(a[0], a[end]);
		AdjustDown(a, end, 0);
		--end;
	}
}

int GetRandom(int* a, int begin, int end)
{
	int i = begin + rand() % (end - begin + 1);
	return a[i];
}

void QuickSort(int* a, int begin, int end)
{
	if (begin >= end) return;

	int key = GetRandom(a, begin, end);

	int left = begin, cur = begin, right = end;
	while (cur <= right)
	{
		if (a[cur] < key) swap(a[left++], a[cur++]);
		else if (a[cur] > key) swap(a[cur], a[right--]);
		else cur++;
	}

	QuickSort(a, begin, left - 1);
	QuickSort(a, right + 1, end);
}

void MergeSort(int* a, int begin, int end, int* tmp)
{
	if (begin >= end) return;

	int mid = begin + (end - begin) / 2;
	MergeSort(a, begin, mid, tmp);
	MergeSort(a, mid + 1, end, tmp);

	int cur1 = begin, cur2 = mid + 1, k = begin;
	while (cur1 <= mid && cur2 <= end)
	{
		if (a[cur1] < a[cur2])
		{
			tmp[k++] = a[cur1++];
		}
		else
		{
			tmp[k++] = a[cur2++];
		}
	}

	while (cur1 <= mid)
	{
		tmp[k++] = a[cur1++];
	}
	while (cur2 <= end)
	{
		tmp[k++] = a[cur2++];
	}
	for (int i = begin; i <= end; ++i)
	{
		a[i] = tmp[i];
	}
}

void InsertSort(int* a, int n)
{
	for (int i = 1; i < n; ++i)
	{
		int end = i - 1;
		int tmp = a[i];

		while (end >= 0)
		{
			if (a[end] > tmp)
			{
				a[end + 1] = a[end];
				--end;
			}
			else break;
		}
		a[end + 1] = tmp;
	}
}

void ShellSort(int* a, int n)
{
	int gap = n;
	while (gap > 1)
	{
		gap = gap / 3 + 1;

		for (int i = gap; i < n; ++i)
		{
			int end = i - gap;
			int tmp = a[i];

			while (end >= 0)
			{
				if (a[end] > tmp)
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else break;
			}
			a[end + gap] = tmp;
		}
	}
}

void SelectSort(int* a, int n)
{
	int end = n - 1;
	while (end >= 0)
	{
		int maxi = 0;
		for (int i = 0; i <= end; ++i)
		{
			if (a[i] > a[maxi])
			{
				maxi = i;
			}
		}
		swap(a[end], a[maxi]);
		--end;
	}
}

void BubbleSort(int* a, int n)
{
	for (int i = n - 1; i > 0; --i)
	{
		bool flag = false;
		for (int j = 0; j < i; ++j)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
				flag = true;
			}
		}
		if (!flag) break;
	}
}

int main()
{
	int* a = new int[15];
	for (int i = 0; i < 15; ++i)
	{
		a[i] = 15 - i;
	}
	
	for (int i = 0; i < 15; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;

	//HeapSort(a, 15);
	//srand(0);
	//QuickSort(a, 0, 14);
	//int* tmp = new int[15];
	//MergeSort(a, 0, 14, tmp);
	//InsertSort(a, 15);
	//ShellSort(a, 15);
	//SelectSort(a, 15);
	BubbleSort(a, 15);

	for (int i = 0; i < 15; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;
}