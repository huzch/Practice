#include<iostream>
#include<string>
#include<queue>
#include<unordered_set>
using namespace std;

string rotate(string s, int i, int dx)
{
    s[i] = (s[i] - '0' + dx + 10) % 10 + '0';
    return s;
}

int bfs(const string& t, const unordered_set<string>& dead)
{
    unordered_set<string> vis;
    queue<pair<string, int>> q;

    q.push({ "0000", 0 });
    vis.insert("0000");
    if ("0000" != t && dead.count("0000")) return -1; //not target but deadend

    while (q.size())
    {
        auto [s, cnt] = q.front();
        q.pop();

        if (s == t) return cnt;
        for (int i = 0; i < 4; ++i)
        {
            for (int dx : {-1, 1})
            {
                string next = rotate(s, i, dx);
                if (!vis.count(next) && (next == t || !dead.count(next))) //not visited and (is target or (not target and not deadend))
                {
                    q.push({ next, cnt + 1 });
                    vis.insert(next);
                }
            }
        }
    }

    return -1;
}

int main()
{
    string t;
    int n;
    cin >> t >> n;
    unordered_set<string> dead;
    for (int i = 0; i < n; ++i)
    {
        string x;
        cin >> x;
        dead.insert(x);
    }

    int ret = bfs(t, dead);
    cout << ret << endl;

    return 0;
}



//#include<iostream>
//#include<string>
//#include<unordered_map>
//using namespace std;
//
//struct TreeNode
//{
//    char val;
//    TreeNode* left;
//    TreeNode* right;
//
//    TreeNode(char val)
//        : val(val)
//        , left(nullptr)
//        , right(nullptr)
//    {}
//};
//
//typedef TreeNode Node;
//
//int k;
//string pre, in;
//unordered_map<char, int> indexMap;
//
//Node* BuildTree(int begin, int end)
//{
//    if (begin > end) return nullptr;
//    char val = pre[k++];
//    int pos = indexMap[val];
//
//    Node* root = new Node(val);
//    root->left = BuildTree(begin, pos - 1);
//    root->right = BuildTree(pos + 1, end);
//    return root;
//}
//
//int Height(Node* root)
//{
//    if (!root) return 0;
//    if (!root->left && !root->right) return 1;
//    int leftH = Height(root->left), rightH = Height(root->right);
//    return leftH + rightH;
//}
//
//void PreOrder(Node* root)
//{
//    if (!root) return;
//    int h = Height(root);
//    for (int i = 0; i < h; ++i) cout << root->val;
//    cout << endl;
//    PreOrder(root->left);
//    PreOrder(root->right);
//}
//
//int main()
//{
//    cin >> pre >> in;
//    int n = in.size();
//    k = 0;
//    for (int i = 0; i < n; ++i) indexMap[in[i]] = i;
//    Node* root = BuildTree(0, n - 1);
//
//    PreOrder(root);
//    return 0;
//}