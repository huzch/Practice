//#include<iostream>
//#include<vector>
//#include<queue>
//#include<algorithm>
//using namespace std;
//
//struct Node
//{
//    char ch;
//    int f, i;
//    Node* left;
//    Node* right;
//
//    Node(char ch, int f, int i)
//        : ch(ch)
//        , f(f)
//        , i(i)
//        , left(nullptr)
//        , right(nullptr)
//    {}
//};
//
//struct cmp
//{
//    bool operator()(Node* n1, Node* n2)
//    {
//        if (n1->f != n2->f) return n1->f > n2->f;
//        else return n1->ch < n2->ch;
//    }
//};
//
//void PostOrder(Node* root)
//{
//    if (!root) return;
//    PostOrder(root->left);
//    PostOrder(root->right);
//    if (!root->left && !root->right) cout << root->ch << endl;
//}
//
//int k, f;
//char ch;
//
//int main()
//{
//    cin >> k;
//    priority_queue<Node*, vector<Node*>, cmp> minHeap;
//    int i = 0;
//    for (; i < k; ++i)
//    {
//        cin >> ch >> f;
//        minHeap.push(new Node(ch, f, i));
//    }
//
//    while (minHeap.size() > 1)
//    {
//        Node* n1 = minHeap.top();
//        minHeap.pop();
//        Node* n2 = minHeap.top();
//        minHeap.pop();
//
//        Node* n3 = new Node('#', n1->f + n2->f, i++);
//        if (n1->f < n2->f)
//        {
//            n3->right = n1;
//            n3->left = n2;
//        }
//        else if (n1->f == n2->f)
//        {
//            if (n1->ch > n2->ch)
//            {
//                n3->right = n2;
//                n3->left = n1;
//            }
//            else if (n1->ch == n2->ch)
//            {
//                if (n1->i > n2->i)
//                {
//                    n3->right = n1;
//                    n3->left = n2;
//                }
//                else
//                {
//                    n3->right = n2;
//                    n3->left = n1;
//                }
//            }
//        }
//        minHeap.push(n3);
//    }
//
//    PostOrder(minHeap.top());
//
//    return 0;
//}

#include<iostream>
using namespace std;

struct Node
{
    double x, y;
    Node *lu, *ld, *ru, *rd;//leftup,leftdown,rightup,rightdown
    Node(double x, double y)
        : x(x)
        , y(y)
        , lu(nullptr)
        , ld(nullptr)
        , ru(nullptr)
        , rd(nullptr)
    {}
};

class Tree
{
public:
    bool Insert(double x, double y)
    {
        if (!root)
        {
            root = new Node(x, y);
            return true;
        }

        Node* parent = nullptr;
        Node* cur = root;
        while (cur)
        {
            parent = cur;
            if (cur->x < x && cur->y < y) cur = cur->ru;
            else if (cur->x < x && cur->y > y) cur = cur->rd;
            else if (cur->x > x && cur->y < y) cur = cur->lu;
            else if (cur->x > x && cur->y > y) cur = cur->ld;
            else return false;
        }

        cur = new Node(x, y);
        if (parent->x < x && parent->y < y) parent->ru = cur;
        else if (parent->x < x && parent->y > y) parent->rd = cur;
        else if (parent->x > x && parent->y < y) parent->lu = cur;
        else if (parent->x < x && parent->y < y) parent->ld = cur;
        return true;
    }
private:
    Node* root = nullptr;
};

int k;
double x, y;

int main()
{
    cin >> k;
    for (int i = 0; i < k; ++i)
    {
        cin >> x >> y;

    }
    return 0;
}

//#include<iostream>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//int t, x, y;
//
//int main()
//{
//    cin >> t;
//    while (t--)
//    {
//        cin >> x >> y;
//        vector<int> p1, p2;
//        while (x)
//        {
//            p1.push_back(x);
//            x /= 2;
//        }
//        while (y)
//        {
//            p2.push_back(y);
//            y /= 2;
//        }
//        reverse(p1.begin(), p1.end());
//        reverse(p2.begin(), p2.end());
//
//        int sz = min(p1.size(), p2.size());
//        int p = 0;
//        for (int i = 0; i < sz; ++i)
//        {
//            if (p1[i] == p2[i]) p = p1[i];
//            else break;
//        }
//        cout << p << endl;
//    }
//    return 0;
//}