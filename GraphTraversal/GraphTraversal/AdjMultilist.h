#pragma once


struct MultiEdge
{
	int _v1;
	int _v2;
	MultiEdge* _next1;
	MultiEdge* _next2;

	MultiEdge(int v1, int v2) : _v1(v1), _v2(v2), _next1(nullptr), _next2(nullptr) {}
};

class AdjMultilist
{
	typedef MultiEdge Edge;
public:
	AdjMultilist(const string* v, int n)
	{
		_vertexs.reserve(n);
		for (int i = 0; i < n; i++)
		{
			_vertexs.push_back(v[i]);
			_vertexMap[v[i]] = i;
		}
		_edges.resize(n, nullptr);
	}

	~AdjMultilist()
	{}

	void AddEdge(const string& v1, const string& v2)
	{
		int i1 = _vertexMap[v1];
		int i2 = _vertexMap[v2];
		Edge* e = new Edge(i1, i2);
		e->_next1 = _edges[i1];
		_edges[i1] = e;
		e->_next2 = _edges[i2];
		_edges[i2] = e;
	}

	void DFS(const string& src)
	{
		int i = _vertexMap[src];
		int n = _vertexs.size();
		vector<bool> vis(n, false);
		vector<int> vertexs;
		vector<Edge*> edges;
		_DFS(i, vis, vertexs, edges);

		for (int i : vertexs)
		{
			cout << _vertexs[i] << " ";
		}
		cout << endl;

		for (Edge* e : edges)
		{
			cout << _vertexs[e->_v1] << "-" << _vertexs[e->_v2] << " ";
		}
		cout << endl;
	}

	void _DFS(int i, vector<bool>& vis, vector<int>& vertexs, vector<Edge*>& edges)
	{
		vis[i] = true;
		vertexs.push_back(i);
		Edge* p = _edges[i];
		while (p)
		{
			int j = p->_v1 == i ? p->_v2 : p->_v1;
			if (!vis[j])
			{
				edges.push_back(p);
				_DFS(j, vis, vertexs, edges);
			}
			p = p->_v1 == i ? p->_next1 : p->_next2;
		}
	}

	void BFS(const string& src)
	{
		int i = _vertexMap[src];
		int n = _vertexs.size();
		vector<bool> vis(n, false);
		vector<int> vertexs;
		vector<Edge*> edges;

		queue<int> q;
		q.push(i);
		vis[i] = true;
		while (!q.empty())
		{
			int i = q.front();
			q.pop();
			vertexs.push_back(i);
			Edge* p = _edges[i];
			while (p)
			{
				int j = p->_v1 == i ? p->_v2 : p->_v1;
				if (!vis[j])
				{
					edges.push_back(p);
					vis[j] = true;
					q.push(j);
				}
				p = p->_v1 == i ? p->_next1 : p->_next2;
			}
		}

		for (int i : vertexs)
		{
			cout << _vertexs[i] << " ";
		}
		cout << endl;

		for (Edge* e : edges)
		{
			cout << _vertexs[e->_v1] << "-" << _vertexs[e->_v2] << " ";
		}
		cout << endl;
	}
private:
	vector<string> _vertexs;
	unordered_map<string, int> _vertexMap;
	vector<Edge*> _edges;
};