#include<iostream>
#include<stack>
#include<queue>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int m;
        cin >> m;
        queue<int> p, q;
        for (int i = 0; i < m; ++i)
        {
            int x;
            cin >> x;
            p.push(x);
        }
        for (int i = 0; i < m; ++i)
        {
            int x;
            cin >> x;
            q.push(x);
        }

        //p不空时：
        //队头元素不同，则出队入栈
        //队头元素相同，则出队
        //p空时：
        //不断比较栈顶与q队头，若不同则输出No
        //若最后栈空，则输出Yes
        stack<int> st;
        while (!p.empty())
        {
            int front = p.front(); p.pop();
            if (front == q.front()) q.pop();
            else st.push(front);
        }

        while (!st.empty())
        {
            int top = st.top(); st.pop();
            if (top != q.front())
            {
                cout << "No" << endl;
                break;
            }
            else q.pop();
        }
        if (q.empty()) cout << "Yes" << endl;
    }
    return 0;
}


//#include<iostream>
//#include<stack>
//#include<algorithm>
//using namespace std;
//
//int main()
//{
//    int t;
//    cin >> t;
//    while (t--)
//    {
//        string s, ret;
//        cin >> s;
//        stack<int> nums;
//        stack<char> ops;
//
//        int n = s.size();
//        for (int i = 0; i < n; ++i)
//        {
//            char ch = s[i];
//            if (ch == '[') ops.push(ch);
//            else if (ch == ']')
//            {
//                string tmp;
//                while (!ops.empty())
//                {
//                    char op = ops.top(); ops.pop();
//                    if (op == '[') break;
//                    else tmp += op;
//                }
//
//                reverse(tmp.begin(), tmp.end());
//                int num = nums.top(); nums.pop();
//                while (num--)
//                {
//                    for (int j = 0; j < tmp.size(); ++j)
//                    {
//                        ops.push(tmp[j]);
//                    }
//                }
//            }
//            else if (isdigit(ch))
//            {
//                int x = 0;
//                while (isdigit(s[i]))
//                {
//                    x = x * 10 + (s[i] - '0');
//                    ++i;
//                }
//
//                nums.push(x);
//                --i;
//            }
//            else ops.push(ch);
//        }
//
//        while (!ops.empty())
//        {
//            char op = ops.top(); ops.pop();
//            ret += op;
//        }
//        reverse(ret.begin(), ret.end());
//        cout << ret << endl;
//    }
//    return 0;
//}