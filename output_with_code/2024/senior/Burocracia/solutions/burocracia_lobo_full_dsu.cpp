#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+10;
const int lg = 20;

int n, p[maxn][lg+1];
vector<int> g[maxn];
int ds[maxn], dsz[maxn], rep[maxn];

void dfs(int u, int ant) {
	p[u][0] = ant;
	for(int i = 1; i <= lg; i++) {
		p[u][i] = p[p[u][i-1]][i-1];
	}

	for(auto v : g[u]) {
		dfs(v,u);
	}
}
vector<int> verts;
void dfspass(int u) {
	verts.push_back(u);
	for(auto v : g[u]) {
		dfspass(v);
	}
}

int find(int v) {
	if(v == ds[v]) return ds[v];
	return ds[v] = find(ds[v]);
}

void join(int u, int v, int rp) {
	if(dsz[u] > dsz[v]) swap(u,v);
	ds[v] = u;
	dsz[u]+= dsz[v];

	rep[u] = rp;
}

int main() {
	cin >> n;

	for(int i = 2; i <= n; i++) {
		int v;
		cin >> v;
		g[v].push_back(i);
	}

	dfs(1,1);

	for(int i = 1; i <= n; i++) {
		ds[i] = i;
		dsz[i] = 1;
		rep[i] = i;
	}

	int q;
	cin >> q;
	for(int it = 1; it <= q; it++) {
		int op;
		cin >> op;

		if(op == 1) {
			int v,k;
			cin >> v >> k;
			v = find(v);
			v = rep[v];
			for(int i = lg; i >= 0; i--) {
				if(k-(1<<i) >= 0) {
					k-= (1<<i);
					v = p[v][i];
				}
			}
			cout << v << endl;
		}
		else {
			int u;
			cin >> u;
			u = find(u);
			if((int) g[u].size() == 0) continue;

			verts.clear();
			for(auto v : g[u]) {
				dfspass(v);
			}

			int v0 = verts[0];
			for(int i = 1; i < (int) verts.size(); i++) {
				int v1 = verts[i];
				v1 = find(v1);
				v0 = find(v0);
				join(v0,v1,rep[v0]);
			}
			v0 = find(v0);
			g[u].clear();
			g[u].push_back(v0);
			g[v0].clear();
		}
	}
}
