//#include <iostream>
//#include <string>
//#include"Match.h"
//using namespace std;
//
//int main()
//{
//    string pattern;
//    int n;
//    cin >> pattern;
//    cin >> n;
//    for (int i = 0; i < n; i++)
//    {
//        string s;
//        cin >> s;
//        cout << boolalpha << match(pattern, s) << endl;
//    }
//    return 0;
//}

//#include <iostream>
//#include "ClockDisplay.h"
//using namespace std;
//
//int main() {
//
//	ClockDisplay time;
//	time.print();
//	ClockDisplay time2(23, 56);
//	time2.print();
//	int cnt = 30;
//	while (cnt--)
//	{
//		time2.increse();
//		time2.print();
//	}
//	return 0;
//}

//#include "Orcs.h"
//
//
//int main()
//{
//	cout << "*************** Testing class Creature ***************" << endl;
//
//	Creature* unknown = new Creature(2, 2);
//	cout << "Calling GetHands(): " << unknown->GetHands() << endl;
//	cout << "Calling GetLegs(): " << unknown->GetLegs() << endl;
//	delete unknown;
//	cout << endl;
//
//	cout << "*************** Testing class Beast ***************" << endl;
//
//	Creature* beast1 = new Beast(2, 4, "SpiderKing");
//	cout << "Calling GetHands(): " << beast1->GetHands() << endl;
//	cout << "Calling GetLegs(): " << beast1->GetLegs() << endl;
//	delete beast1;
//	cout << endl;
//
//	Beast* beast2 = new Beast(2, 3, "TripleLegCat");
//	cout << "Calling GetHands(): " << beast2->GetHands() << endl;
//	cout << "Calling GetLegs(): " << beast2->GetLegs() << endl;
//	cout << "Calling GetName(): " << beast2->GetName() << endl;
//	delete beast2;
//	cout << endl;
//
//	cout << "*************** Testing class Human ***************" << endl;
//
//	Creature* human1 = new Human(2, 2, "Talion");
//	cout << "Calling GetHands(): " << human1->GetHands() << endl;
//	cout << "Calling GetLegs(): " << human1->GetLegs() << endl;
//	delete human1;
//	cout << endl;
//
//	Human* human2 = new Human(2, 2, "Altariel");
//	cout << "Calling GetHands(): " << human2->GetHands() << endl;
//	cout << "Calling GetLegs(): " << human2->GetLegs() << endl;
//	cout << "Calling GetName(): " << human2->GetName() << endl;
//	delete human2;
//	cout << endl;
//
//	cout << "*************** Testing class Orc ***************" << endl;
//
//	Creature* orc1 = new Orc(2, 4, "Herkarim", "Centaur");
//	cout << "Calling GetHands(): " << orc1->GetHands() << endl;
//	cout << "Calling GetLegs(): " << orc1->GetLegs() << endl;
//	delete orc1;
//	cout << endl;
//
//	Beast* orc2 = new Orc(2, 2, "OgreMagi", "BlueFat");
//	cout << "Calling GetHands(): " << orc2->GetHands() << endl;
//	cout << "Calling GetLegs(): " << orc2->GetLegs() << endl;
//	cout << "Calling GetName(): " << orc2->GetName() << endl;
//	delete orc2;
//	cout << endl;
//
//	Human* orc3 = new Orc(4, 2, "Miranda", "NotreDame");
//	cout << "Calling GetHands(): " << orc3->GetHands() << endl;
//	cout << "Calling GetLegs(): " << orc3->GetLegs() << endl;
//	cout << "Calling GetName(): " << orc3->GetName() << endl;
//	delete orc3;
//	cout << endl;
//
//	Orc* orc4 = new Orc(2, 0, "Cassiopea", "SnakeWoman");
//	cout << "Calling GetHands(): " << orc4->GetHands() << endl;
//	cout << "Calling GetLegs(): " << orc4->GetLegs() << endl;
//	cout << "Calling GetBeastName(): " << orc4->GetBeastName() << endl;
//	cout << "Calling GetHumanName(): " << orc4->GetHumanName() << endl;
//	delete orc4;
//	cout << endl;
//
//	return 0;
//}


//#include"Queue.h"
//
//class Job
//{
//public:
//    explicit Job(int pri = 0)
//    {
//        id = number++;
//        priority = pri;
//    }
//    string toString()
//    {
//        stringstream ss;
//        ss << "[" << id << ":" << priority << "]";
//        return ss.str();
//    }
//private:
//    static int number;
//    int id;
//    int priority;
//};
//
//int Job::number = 0;
//
//template<class T>
//void print(Queue<T> queue)
//{
//    while (!queue.empty())
//    {
//        cout << queue.front() << " ";
//        queue.pop();
//    }
//    cout << endl;
//}
//
//int main()
//{
//    // test case 1: integer..
//    Queue<int> que;
//    int m, n;
//    cin >> m >> n;
//    for (int i = 0; i < m; i++) que.push(i + 0.01);
//    for (int i = 0; i < n; i++) que.pop();
//    if (!que.empty()) {
//        cout << que.front() << endl;
//        cout << que.back() << endl;
//    }
//    cout << "The size is: " << que.size() << endl;
//    if (que.empty()) cout << "The queue is empty!" << endl;
//    else cout << "The queue is NOT empty!" << endl;
//
//    // test case 2: double..
//    Queue<double> que1;
//    cin >> m >> n;
//    for (int i = 0; i < m; i++) que1.push(i + 0.01);
//    for (int i = 0; i < n; i++) que1.pop();
//    if (!que1.empty()) {
//        cout << que1.front() << endl;
//        cout << que1.back() << endl;
//    }
//    cout << "The size is: " << que1.size() << endl;
//    if (que1.empty()) cout << "The queue is empty!" << endl;
//    else cout << "The queue is NOT empty!" << endl;
//
//    // test case 3: user defined class..
//    Queue<Job> que2;
//    cin >> m >> n;
//    for (int i = 0; i < m; i++) que2.push(Job(i));
//    for (int i = 0; i < n; i++) que2.pop();
//
//    if (!que2.empty()) {
//        cout << que2.front().toString() << endl;
//        cout << que2.back().toString() << endl;
//    }
//    cout << "The size is: " << que2.size() << endl;
//    if (que2.empty()) cout << "The queue is empty!" << endl;
//    else cout << "The queue is NOT empty!" << endl;
//
//    // test case 4: swap function..
//    Queue<int> que3, que4;
//    for (int i = 0; i < m; i++) que3.push(i);
//    for (int i = 0; i < n; i++) que4.push(m - i);
//    cout << "Before Swap...." << endl;
//    print(que3);
//    print(que4);
//
//    que3.swap(que4);
//    cout << "After Swap...." << endl;
//    cout << endl;
//    print(que3);
//    print(que4);
//}

//#include"Stack.h"
//
//int main() //程序EX6_4.cpp
//{
//    Stack<int> stack; // 实例化一个保存int型元素的栈
//
//    for (int i = 1; i < 9; i++) // 向栈中压入8个元素
//        stack.push(i);
//
//    while (!stack.isEmpty())
//    {                                  // 栈不为空时循环
//        cout << stack.getTop() << " "; // 显示栈顶元素
//        stack.pop();                   // 弹出栈顶元素
//    }
//    return 0;
//}

//#include<iostream>
//#include<queue>
//using namespace std;
//
//int main()
//{
//    int t;
//    cin >> t;
//    while (t--)
//    {
//        int n, m;
//        cin >> n >> m;
//
//        queue<pair<int, int>> q;//<优先级,序号>
//        priority_queue<int> pq;
//        for (int i = 0; i < n; ++i)
//        {
//            int p;
//            cin >> p;
//            q.push({ p, i });
//            pq.push(p);
//        }
//
//        int time = 0;
//        while (!q.empty())
//        {
//            auto kv = q.front();
//            q.pop();
//            if (kv.first < pq.top())
//            {
//                q.push(kv);
//            }
//            else if (kv.second == m)
//            {
//                cout << time + 1 << endl;
//                break;
//            }
//            else
//            {
//                pq.pop();
//                ++time;
//            }
//        }
//    }
//    return 0;
//}

#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> v;
    unordered_map<int, string> hash;
    for (int i = 0; i < n; ++i)
    {
        int id;
        string mes;
        cin >> id >> mes;
        auto it = find(v.begin(), v.end(), id);
        if (it != v.end())
        {
            v.erase(it);
        }
        v.push_back(id);
        hash[id] = mes;
    }

    for (int i = v.size() - 1; i >= 0; --i)
    {
        cout << v[i] << ": " << hash[v[i]] << endl;
    }
    return 0;
}