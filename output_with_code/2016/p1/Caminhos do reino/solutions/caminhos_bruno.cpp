#include <bits/stdc++.h>
using namespace std;

const int N = 100001;
int n, q, vet[N], vis[N], cic[N], has[N], col[N], dis[N], fin[N], sz[N];

void mark(int p, int d)
{
	cic[p] = 1;
	dis[p] = d;
	int q = vet[p];
	if (!cic[q]) mark(q, d+1);
	else sz[0] = d+1;
}

void dfs(int p)
{
	vis[p] = 1;
	int q = vet[p];
	if (vis[q] == 1 && !cic[q]) mark(q, 0);
	if (!vis[q]) dfs(q);
	vis[p] = 2;
}

void go(int p, int d, int c)
{
	col[p] = c;
	dis[p] = d;
	int q = vet[p];
	if (!cic[q]) go(q, d+1, c);
	else fin[c] = q, sz[c] = d+1;
}

int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> vet[i], has[vet[i]] = 1;
	for (int i = 1; i <= n; ++i) if (!vis[i])
		dfs(i);
	for (int i = 1; i <= n; ++i) if (!has[i])
		go(i, 0, i);
	cin >> q;
	while (q--)
	{
		int a, b, resa = 0, resb = 0;
		cin >> a >> b;
		if (col[a] == col[b] && col[a] > 0)
		{
			cout << abs(dis[a]-dis[b]) << endl;
			continue;
		}
		if (col[a])
		{
			resa = sz[col[a]]-dis[a];
			a = fin[col[a]];
		}
		if (col[b])
		{
			resb = sz[col[b]]-dis[b];
			b = fin[col[b]];
		}
		int res = min(
			max(resa + (dis[a] <= dis[b] ? dis[b]-dis[a] : sz[0]-(dis[a]-dis[b])), resb),
			max(resa, resb + (dis[b] <= dis[a] ? dis[a]-dis[b] : sz[0]-(dis[b]-dis[a])))
		);
		cout << res << "\n";
	}
}

