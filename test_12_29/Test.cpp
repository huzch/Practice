#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5 + 10;
vector<int> edges[N];
bool st[N];
int n, m;
int t;

bool dfs(int u, int k) {
	if(k == 0) return u == t;

	st[u] = true;
	for(int v : edges[u]) {
		if(!st[v]) {
			if(dfs(v, k - 1)) {
				return true;
			}
		}
	}

	st[u] = false;
	return false;
}

int main() {
	cin >> n >> m;
	for(int i=1; i<=m; ++i) {
		int u, v; cin >> u >> v;
		edges[u].push_back(v);
		edges[v].push_back(u);
	}

	int u, k; cin >> u >> t >> k;
	cout << dfs(u, k) << endl;

	return 0;
}
