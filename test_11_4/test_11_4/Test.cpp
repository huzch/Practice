#include<iostream>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
};

typedef TreeNode Node;
int ret;

pair<int, int> dfs(Node* root)
{
    if (!root) return { -1, -1 };
    auto left = dfs(root->left);
    auto right = dfs(root->right);
    ret = max(ret, max(left.second + 1, right.first + 1));
    return { left.second + 1, right.first + 1 };
}

int longestZigZag(Node* root)
{
    ret = 0;
    dfs(root);
    return ret;
}

//#include<iostream>
//#include<vector>
//using namespace std;
//
//struct Node
//{
//    int _val;
//    Node* _left;
//    Node* _right;
//
//    Node(int val)
//        : _val(val)
//        , _left(nullptr)
//        , _right(nullptr)
//    {}
//};
//
//class BST
//{
//public:
//    ~BST()
//    {
//        Destroy(_root);
//    }
//
//    void Destroy(Node* root)
//    {
//        if (root == nullptr) return;
//
//        Destroy(root->_left);
//        Destroy(root->_right);
//        delete root;
//    }
//
//    bool Insert(int val)
//    {
//        if (_root == nullptr)
//        {
//            _root = new Node(val);
//            return true;
//        }
//
//        Node* parent = nullptr;
//        Node* cur = _root;
//        while (cur)
//        {
//            if (cur->_val < val)
//            {
//                parent = cur;
//                cur = cur->_right;
//            }
//            else if (cur->_val > val)
//            {
//                parent = cur;
//                cur = cur->_left;
//            }
//            else return false;
//        }
//
//        cur = new Node(val);
//        if (parent->_val < val) parent->_right = cur;
//        else parent->_left = cur;
//        return true;
//    }
//
//    Node* _root = nullptr;
//};
//
//int n, m, x;
//vector<vector<int>> ret;
//
//int Sum(vector<int>& v)
//{
//    int sum = 0;
//    for (int e : v) sum += e;
//    return sum;
//}
//
//void _GetPath(vector<int> path, Node* root)
//{
//    if (root == nullptr) return;
//    else path.push_back(root->_val);
//
//    int sum = Sum(path);
//    if (sum == m && !root->_left && !root->_right)
//    {
//        ret.push_back(path);
//        return;
//    }
//
//    _GetPath(path, root->_left);
//    _GetPath(path, root->_right);
//}
//
//void GetPath(Node* root)
//{
//    ret.clear();
//    vector<int> path;
//    _GetPath(path, root);
//}
//
//int main()
//{
//    while (cin >> n >> m)
//    {
//        BST t;
//        while (n--)
//        {
//            cin >> x;
//            t.Insert(x);
//        }
//
//        GetPath(t._root);
//        if (ret.size())
//        {
//            for (auto& path : ret)
//            {
//                for (int i = 0; i < path.size() - 1; ++i)
//                {
//                    cout << path[i] << "->";
//                }
//                cout << path.back() << endl;
//            }
//        }
//        else cout << "NULL" << endl;
//    }
//    return 0;
//}



//#include<iostream>
//#include<queue>
//using namespace std;
//
//struct Node
//{
//    int _val;
//    Node* _left;
//    Node* _right;
//
//    Node(int val)
//        : _val(val)
//        , _left(nullptr)
//        , _right(nullptr)
//    {}
//};
//
//class BST
//{
//public:
//    ~BST()
//    {
//        Destroy(_root);
//    }
//
//    void Destroy(Node* root)
//    {
//        if (root == nullptr) return;
//
//        Destroy(root->_left);
//        Destroy(root->_right);
//        delete root;
//    }
//
//    bool Insert(int val)
//    {
//        if (_root == nullptr)
//        {
//            _root = new Node(val);
//            return true;
//        }
//
//        Node* parent = nullptr;
//        Node* cur = _root;
//        while (cur)
//        {
//            if (cur->_val < val)
//            {
//                parent = cur;
//                cur = cur->_right;
//            }
//            else if (cur->_val > val)
//            {
//                parent = cur;
//                cur = cur->_left;
//            }
//            else return false;
//        }
//
//        cur = new Node(val);
//        if (parent->_val < val) parent->_right = cur;
//        else parent->_left = cur;
//        return true;
//    }
//
//    Node* _root = nullptr;
//};
//
//int m, n, x;
//
//int main()
//{
//    cin >> m;
//    while (m--)
//    {
//        BST t;
//        int ret = 0;
//        cin >> n;
//        while (n--)
//        {
//            cin >> x;
//            t.Insert(x);
//        }
//
//        queue<Node*> q;
//        q.push(t._root);
//        while (q.size())
//        {
//            int sz = q.size();
//            ret = max(ret, sz);
//            for (int i = 0; i < sz; ++i)
//            {
//                Node* front = q.front();
//                q.pop();
//                if (front->_left) q.push(front->_left);
//                if (front->_right) q.push(front->_right);
//            }
//        }
//        cout << ret << endl;
//    }
//    return 0;
//}