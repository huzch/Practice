#pragma once
#include "Stack.h"

struct Edge
{
	int _v;
	int _w;
	Edge* _next;

	Edge(int v, int w) : _v(v), _w(w), _next(nullptr) {}
};

struct Node
{
	int _v;
	vector<Node*> _children;

	Node(int v) : _v(v) {}
};

class AdjList
{
public:
	AdjList(const string* v, int n)
	{
		_vertexs.reserve(n);
		for (int i = 0; i < n; i++)
		{
			_vertexs.push_back(v[i]);
			_vertexMap[v[i]] = i;
		}
		_edges.resize(n, nullptr);
	}

	~AdjList()
	{}

	void AddEdge(const string& v1, const string& v2, int w = 0)
	{
		int i1 = _vertexMap[v1];
		int i2 = _vertexMap[v2];
		Edge* e1 = new Edge(i1, w);
		Edge* e2 = new Edge(i2, w);
		e1->_next = _edges[i2];
		_edges[i2] = e1;
		e2->_next = _edges[i1];
		_edges[i1] = e2;
	}

	void DFS(const string& src)
	{
		int i = _vertexMap[src];
		int n = _vertexs.size();
		vector<bool> vis(n, false);

		Node* root = new Node(i);
		_DFS(i, vis, root);

		Print(root);
	}

	void _DFS(int i, vector<bool>& vis, Node* root)
	{
		vis[i] = true;
		Edge* p = _edges[i];
		while (p)
		{
			if (!vis[p->_v])
			{
				Node* child = new Node(p->_v);
				root->_children.push_back(child);
				_DFS(p->_v, vis, child);
			}
			p = p->_next;
		}
	}

	void BFS(const string& src)
	{
		int i = _vertexMap[src];
		int n = _vertexs.size();
		vector<bool> vis(n, false);
		queue<Node*> q;

		Node* root = new Node(i);
		q.push(root);
		vis[i] = true;

		while (!q.empty())
		{
			Node* cur = q.front();
			q.pop();
			int i = cur->_v;
			
			Edge* p = _edges[i];
			while (p)
			{
				if (!vis[p->_v])
				{
					Node* child = new Node(p->_v);
					cur->_children.push_back(child);
					q.push(child);
					vis[p->_v] = true;
				}
				p = p->_next;
			}
		}

		Print(root);
	}

	void Print(Node* root, int depth = 0)
	{
		for (int i = 0; i < depth; i++)
		{
			cout << "  ";
		}
		cout << _vertexs[root->_v] << endl;

		for (Node* child : root->_children)
		{
			Print(child, depth + 1);
		}
	}

	void DFSNonR(const string& src)
	{
		int i = _vertexMap[src];
		int n = _vertexs.size();
		vector<bool> vis(n, false);
		Stack<int> st;

		st.Push(i);

		vector<vector<int>> edges(n);
		for (int i = 0; i < n; ++i)
		{
			Edge* p = _edges[i];
			while (p)
			{
				edges[i].push_back(p->_v);
				p = p->_next;
			}
		}

		while (!st.Empty())
		{
			int i = st.Top();
			st.Pop();
			if (!vis[i])
			{
				cout << _vertexs[i] << " ";
				vis[i] = true;
			}

			for(auto it = edges[i].rbegin(); it != edges[i].rend(); ++it)
			{
				int j = *it;
				if (!vis[j])
				{
					st.Push(j);
				}
			}
		}
	}

	void Dijkstra(const string& src)
	{
		int i = _vertexMap[src];
		int n = _vertexs.size();
		vector<bool> vis(n, false);
		vector<int> dist(n, INT_MAX);
		vector<int> prev(n, -1);
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
		vis[i] = true;
		dist[i] = 0;
		prev[i] = i;
		minHeap.push({ 0, i });

		while (minHeap.size())
		{
			auto [d, u] = minHeap.top();
			minHeap.pop();

			Edge* p = _edges[u];
			while (p)
			{
				int v = p->_v;
				int w = p->_w;
				if (!vis[v] && d + w < dist[v])
				{
					vis[v] = true;
					dist[v] = d + w;
					prev[v] = u;
					minHeap.push({ dist[v], v });
				}
				p = p->_next;
			}
		}

		for (int j = 0; j < n; ++j)
		{
			cout << _vertexs[i] << "->" << _vertexs[j] << ":" << dist[j] << endl;

			vector<int> path;
			for (int k = j; k != i; k = prev[k])
			{
				path.push_back(k);
			}
			path.push_back(i);

			cout << "Path: ";
			for (int k = path.size() - 1; k >= 1; --k)
			{
				cout << _vertexs[path[k]] << "->";
			}
			cout << _vertexs[path[0]] << endl << endl;
		}
	}

private:
	vector<string> _vertexs;
	unordered_map<string, int> _vertexMap;
	vector<Edge*> _edges;
};