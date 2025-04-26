#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//
//bool vis[105];
//vector<vector<int>> edges;
//vector<int> apples;//以当前结点为根的子树中所有的苹果数
//int n, q;
//
//int dfs(int srci)
//{
//    vis[srci] = true;
//    for (int i = 1; i <= n; ++i)
//    {
//        if (edges[srci][i] != -1 && !vis[i])
//        {
//            apples[srci] += edges[srci][i] + dfs(i);
//        }
//    }
//    return apples[srci];
//}
//
//int main()
//{
//    cin >> n >> q;
//    edges.resize(n + 1, vector<int>(n + 1, -1));
//    apples.resize(n + 1);
//
//    for (int i = 0; i < n - 1; ++i)
//    {
//        int u, v, w;
//        cin >> u >> v >> w;
//        edges[u][v] = edges[v][u] = w;
//    }
//
//    dfs(1);
//    sort(apples.begin(), apples.end());
//
//    int del = 0;
//    for (int i = 0; i < n + 1 - q; ++i) del += apples[i];
//    cout << apples.back() - del << endl;
//    return 0;
//}


const int N = 110;
int dp[N][N];
int e[N * 2], ne[N * 2], h[N * 2], w[N * 2];
int idx = 0;
void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int n, m;
void dfs(int u, int father) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == father)continue;
        dfs(j, u);
        for (int v = m; v; v--)
            for (int k = 0; k < v; k++)
                dp[u][v] = max(dp[u][v], dp[u][v - k - 1] + dp[j][k] + w[i]);
    }
}
int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        add(x, y, z);
        add(y, x, z);
    }
    dfs(1, -1);
    cout << dp[1][m];
}