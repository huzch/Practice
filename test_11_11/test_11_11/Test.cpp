//#include<iostream>
//#include<vector>
//using namespace std;
//
//const int N = 1e4 + 10;
//int edges[N][N];
//bool vis[N];
//
//int t, n, m, x, y;
//
//void dfs(int srci)
//{
//    vis[srci] = true;
//    for (int i = 1; i <= n; ++i)
//    {
//        if (!vis[i] && edges[srci][i] == 1) dfs(i);
//    }
//}
//
//int main()
//{
//    cin >> t;
//    while (t--)
//    {
//        cin >> n >> m;
//        memset(edges, 0, sizeof edges);
//        memset(vis, 0, sizeof vis);
//        for (int i = 0; i < m; ++i)
//        {
//            cin >> x >> y;
//            edges[x][y] = edges[y][x] = 1;
//        }
//
//        bool isTree = true;
//        if (n != m + 1) isTree = false;
//        else
//        {
//            dfs(1);
//            for (int i = 1; i <= n; ++i)
//            {
//                if (!vis[i])
//                {
//                    isTree = false;
//                    break;
//                }
//            }
//        }
//
//        if (isTree) cout << "YES" << endl;
//        else cout << "NO" << endl;
//    }
//    return 0;
//}

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

const int N = 1e5 + 10;
struct Node
{
    int val, child, bro;
}a[N];

int n, parent;
vector<vector<int>> b;
queue<int> q;

int main()
{
    cin >> n;
    b.resize(n + 1);
    for (int i = 2; i <= n; ++i)
    {
        cin >> parent;
        b[parent].push_back(i);
    }

    for (int i = 1; i <= n; ++i)
    {
        a[i].val = i;
        int sz = b[i].size();
        if (sz) a[i].child = b[i][0];

        for (int j = 0; j < sz - 1; ++j)
        {
            a[b[i][j]].bro = b[i][j + 1];
        }
    }

    q.push(1);
    while (q.size())
    {
        int n = q.front();
        q.pop();
        cout << a[n].val << " ";

        int child = a[n].child, bro = a[n].bro;
        if (child) q.push(child);
        if (bro) q.push(bro);
    }
    return 0;
}