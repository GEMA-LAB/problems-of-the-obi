#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 100010;

struct DSU{
	int pai[N], sz[N];
	void build(int n){
		for(int i = 1;i <= n;i++){
			pai[i] = i;
			sz[i] = 1;
		}
	}
	int find(int x){
		return pai[x] = (x == pai[x] ? x : find(pai[x]));
	}
	void join(int a, int b){
		a = find(a);
		b = find(b);
		if(a == b)
			return;
		if(sz[a] > sz[b])
			swap(a, b);
		pai[a] = b;
		sz[b] += sz[a];
	}
} dsu;

vector <pair <int, int>> g[N];
vector <int> esp;
int s, t;
int dist[N], pai[N];
int n, m;

bool check(int c){
	for(int i = 1;i <= n;i++){
		dist[i] = 1e18;
		pai[i] = -1;
	}	
	priority_queue <pair <int, int>> pq;
	dist[s] = dist[t] = 0;
	for(auto x : esp){
		dist[x] = 0;
		pai[x] = x;
	}
	for(int i = 1;i <= n;i++){
		if(dist[i] == 0)
			pq.push({0, i});
	}
	dsu.build(n);
	while(!pq.empty()){
		auto [d, v] = pq.top();
		pq.pop();
		d *= -1;
		if(dist[v] != d)
			continue;
		for(auto [x, w] : g[v]){
			if(dist[x] > dist[v] + w){
				pai[x] = pai[v];
				dist[x] = dist[v] + w;
				pq.push({-dist[x], x});
			}
			else if(dist[x] + dist[v] + w <= c){
				dsu.join(pai[x], pai[v]);
			}
		}
	}
	return dsu.find(s) == dsu.find(t);
}

int32_t main(){
	cin >> n >> m;
	for(int i = 0;i < m;i++){
		int a, b, c;
		cin >> a >> b >> c;
		g[a].push_back({b, c});
		g[b].push_back({a, c});
	}
	int k;
	cin >> k;
	for(int i = 0;i < k;i++){
		int x;
		cin >> x;
		esp.push_back(x);
	}
	s = 1, t = n;
	esp.push_back(t);
	int l = 0, r = 1e18;
	int ans = 1e18;
	while(l <= r){
		int mid = (l+r)/2;
		if(check(mid)){
			ans = mid;
			r = mid-1;
		}
		else{
			l = mid+1;
		}
	}
	cout << ans << '\n';
}