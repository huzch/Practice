#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

const int N = 1e5 + 10;
int a[N], b[N];
vector<int> ans;
unordered_map<int, int> mp;
int n, m;

int main() {
	cin >> n;
	for(int i=1; i<=n; ++i) {
		cin >> a[i];
	}

	cin >> m;
	for(int i=1; i<=m; ++i) {
		cin >> b[i];
		mp[b[i]] = i;
	}

	for(int i=1; i<=n; ++i) {
		if(mp.count(a[i])) {
			int p = mp[a[i]];
			bool st = false;
			for(int j=p; j<=m; ++j) {
				if(b[j] > a[i]) {
					ans.push_back(b[j]);
					st = true;
					break;
				}
			}
			if(!st) ans.push_back(-1);
		}
		else ans.push_back(0);
	}

	for(int x : ans) {
		cout << x << " ";
	}
	cout << endl;

	return 0;
}



















// #include <iostream>
// #include <vector>
// using namespace std;
//
// const int N = 1e3 + 10;
// vector<int> edges[N];
// bool st[N];
// int n, m;
//
// void dfs(int u) {
// 	st[u] = true;
// 	for(int v : edges[u]) {
// 		if(!st[v]) {
// 			dfs(v);
// 		}
// 	}
// }
//
// int main() {
// 	cin >> n >> m;
// 	for(int i=1; i<=m; ++i) {
// 		int u, v; cin >> u >> v;
// 		edges[u].push_back(v);
// 	}
//
// 	int cnt = 0;
// 	for(int i=1; i<=n; ++i) {
// 		if(!st[i]) {
// 			dfs(i);
// 			++cnt;
// 		}
// 	}
// 	cout << cnt << endl;
//
// 	return 0;
// }
//

















// template<typename T>
// struct ListNode {
//     T val;
//     ListNode* next = nullptr;
//     ListNode() : val(0), next(nullptr) {}
// };
//
// template<typename T>
// ListNode<T>* merge(ListNode<T>* head1, ListNode<T>* head2) {
// 	auto Guard = new ListNode<T>(), tail = Guard;
// 	auto cur1 = head1, cur2 = head2;
// 	while(cur1 && cur2) {
// 		if(cur1->val < cur2->val) {
// 			tail->next = cur1;
// 			cur1 = cur1->next;
// 		}
// 		else {
// 			tail->next = cur2;
// 			cur2 = cur2->next;
// 		}
// 		tail = tail->next;
// 	}
//
// 	if(cur1) tail->next = cur1;
// 	if(cur2) tail->next = cur2;
//
// 	auto head = Guard->next;
// 	delete Guard;
// 	return head;
// }
//
// template<typename T>
// ListNode<T>* mergeSort(ListNode<T>* head) {
// 	if(!head || !head->next) return head;
//
// 	auto prev = head, slow = head, fast = head;
// 	while(fast && fast->next) {
// 		prev = slow;
// 		slow = slow->next;
// 		fast = fast->next->next;
// 	}
// 	prev->next = nullptr;
//
// 	return merge(mergeSort(head), mergeSort(slow));
// }
//
// template<typename T>
// ListNode<T>* sortList(ListNode<T>* head) {
// 	head->next = mergeSort(head->next);
// 	return head;
// } 























// #include <iostream>
// #include <utility>
// using namespace std;
//
// void Heapfy(int A[],int idx,int max)//建立最大堆
// {
// 	int parent = idx, child = parent * 2 + 1;
// 	while(child < max) {
// 		if(child + 1 < max && A[child] < A[child + 1]) {
// 			++child;
// 		}
//
// 		if(A[parent] < A[child]) {
// 			swap(A[parent], A[child]);
// 			parent = child;
// 			child = parent * 2 + 1;
// 		}
// 		else break;
// 	}
// }
//
// void buildHeap(int A[], int len)
// {
// 	for(int i=len/2-1;i>=0;--i)
// 	{
// 		Heapfy(A,i,len);     //建立最大堆，将堆中最大的值交换到根节点
// 	}
//
// 	for(int i=len-1;i>=1;--i)
// 	{
// 		int temp=A[0];   //将当前堆的根节点交换到堆尾的指定位置
// 		A[0]=A[i];
// 		A[i]=temp;
//
// 		Heapfy(A,0,i);  //建立下一次的最大堆
// 	}
// }
//
// int main(){
// 	int data[] = {9,6,7,22,20,33,16,20};
//     cout << "Before sorted:" << endl;
//     for(int i=0; i<=7; i++)
//         cout<<data[i]<<" ";
//     cout<<endl;
//
//     cout << "After sorted:" << endl;
//     buildHeap(data,sizeof(data)/sizeof(data[0]));
//     for(int i=0; i<=7; i++)
//         cout<<data[i]<<" ";
//     cout<<endl;
//     return 0;
// }
















// #include <cstdlib>
// #include <iostream>
// #include <utility>
// using namespace std;
//
// const int N = 1e5 + 10;
// int a[N], n;
//
// int GetKey(int l, int r) {
// 	int i = rand() % (r - l + 1) + l;
// 	return a[i];
// }
//
// void QuickSort(int begin, int end) {
// 	if(begin >= end) return;
//
// 	int key = GetKey(begin, end);
//
// 	int left = begin - 1, cur = begin, right = end + 1;
// 	while(cur < right) {
// 		if(a[cur] < key) {
// 			swap(a[++left], a[cur++]);
// 		}
// 		else if(a[cur] > key) {
// 			swap(a[--right], a[cur]);
// 		}
// 		else ++cur;
// 	}
//
// 	QuickSort(begin, left);
// 	QuickSort(right, end);
// }
//
// int main() {
// 	cin >> n;
// 	for(int i=1; i<=n; ++i) {
// 		cin >> a[i];
// 	}
//
// 	srand(0);
// 	QuickSort(1, n);
//
// 	for(int i=1; i<=n; ++i) {
// 		cout << a[i] << " ";
// 	}
// 	cout << endl;
//
// 	return 0;
// }
//
//







// #include <iostream>
// using namespace std;
//
// const int N = 1e3 + 10;
// int a[N], n;
//
// void print() {
// 	for(int i=1; i<=n; ++i) {
// 		cout << a[i] << " ";
// 	}
// 	cout << endl;
// }
//
// int main() {
// 	cin >> n;
// 	for(int i=1; i<=n; ++i) {
// 		cin >> a[i];
// 	}
//
// 	for(int i=2; i<=n; ++i) {
// 		int tmp = a[i];
// 		int j = i - 1;
// 		while(j >= 1) {
// 			if(a[j] > tmp) {
// 				a[j + 1] = a[j];
// 				--j;
// 			}
// 			else break;
// 		}
// 		a[j + 1] = tmp;
//
// 		print();
// 	}
// 	return 0;
// }
