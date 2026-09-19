#include <bits/stdc++.h>
using namespace std;

const int N = 100001;

int vis[N], n;
vector<int> adj[N];

void dfs(int p, int c)
{
	vis[p] = c;
	for (int i = 0; i < adj[p].size(); ++i)
	{
		int q = adj[p][i];
		if (!vis[q]) dfs(q, 3-c);
	}
}

void print(int c)
{
	bool b = 0;
	for (int i = 1; i <= n; ++i) if (vis[i] == c)
		(cout << (b?" ":"") << i), b = 1;
	cout << endl;
}

int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		int m; cin >> m;
		while (m--)
		{
			int x; cin >> x;
			adj[i].push_back(x);
		}
	}
	for (int i = 1; i <= n; ++i) if (!vis[i])
		dfs(i, 1);
	print(1);
	print(2);
}

