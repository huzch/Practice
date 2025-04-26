#include<iostream>
#include<vector>
#include<queue>
#include<functional>
using namespace std;

int main()
{
    int n, r;
    cin >> n >> r;
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> v[i];
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    for (int i = 0; i < n; ++i)
    {
        int sum = v[i];
        int left = i - 1, right = i + 1;

        int count = 0;
        while (left >= 0 && count < r)
        {
            sum += v[left--];
            ++count;
        }

        count = 0;
        while (right < n && count < r)
        {
            sum += v[right++];
            ++count;
        }

        minHeap.push({ sum, i });
    }

    auto top = minHeap.top();
    cout << top.second << endl << top.first;
    return 0;
}





//#include <iostream>
//#include <vector>
//
//#include "list.h"
//using namespace std;
//
//int main() {
//    SqList sq;
//    int T;
//    cin >> T;
//    while (T--) {
//        string op_str;
//        cin >> op_str;
//        if (op_str == "default_constructor") {
//            sq = SqList();
//        }
//        else if (op_str == "array_constructor") {
//            int n;
//            cin >> n;
//            vector<int> a(n);
//            sq = SqList(a.data(), n);
//        }
//        else if (op_str == "copy_constructor") {
//            SqList sq2 = sq;
//            sq2.print();
//        }
//        else if (op_str == "size") {
//            cout << sq.size() << endl;
//        }
//        else if (op_str == "empty") {
//            cout << (sq.empty() ? "true" : "false") << endl;
//        }
//        else if (op_str == "clear") {
//            sq.clear();
//        }
//        else if (op_str == "get") {
//            size_t i;
//            cin >> i;
//            if (i >= sq.size()) {
//                cout << "error: out of range" << endl;
//            }
//            else {
//                cout << sq[i] << endl;
//            }
//        }
//        else if (op_str == "back") {
//            if (sq.empty()) {
//                cout << "error: empty" << endl;
//            }
//            else {
//                cout << sq.back() << endl;
//            }
//        }
//        else if (op_str == "insert") {
//            size_t i;
//            int e;
//            cin >> i >> e;
//            if (i > sq.size()) {
//                cout << "error: out of range" << endl;
//            }
//            else {
//                sq.insert(i, e);
//            }
//        }
//        else if (op_str == "erase") {
//            size_t i;
//            cin >> i;
//            if (i >= sq.size()) {
//                cout << "error: out of range" << endl;
//            }
//            else {
//                sq.erase(i);
//            }
//        }
//        else if (op_str == "push_back") {
//            int e;
//            cin >> e;
//            sq.push_back(e);
//        }
//        else if (op_str == "push_front") {
//            int e;
//            cin >> e;
//            sq.push_front(e);
//        }
//        else if (op_str == "pop_back") {
//            if (sq.empty()) {
//                cout << "error: empty" << endl;
//            }
//            else {
//                cout << sq.pop_back() << endl;
//            }
//        }
//        else if (op_str == "pop_front") {
//            if (sq.empty()) {
//                cout << "error: empty" << endl;
//            }
//            else {
//                cout << sq.pop_front() << endl;
//            }
//        }
//        else if (op_str == "print") {
//            sq.print();
//        }
//        else {
//            cout << "error: unknown operation" << endl;
//        }
//    }
//}
