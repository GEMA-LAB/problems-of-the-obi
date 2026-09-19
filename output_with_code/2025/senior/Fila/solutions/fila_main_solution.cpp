#include<bits/stdc++.h>
using namespace std;

int main(){
	int n, q; cin >> n >> q;
	vector<int> fila(n);
	vector<pair<int, int>> qs(q);
	for(int& x : fila)cin >> x;
	for(auto& [a, b] : qs)cin >> a >> b;
	vector<vector<int>> t(n/2+1);
	vector<int> st = {0}; int id = 1;
	vector<int> created(n, -1);
	for(int i = 0, last = 0, v = 0; i < n; i++){
		int cur = fila[i];
		if (cur > last){
			int nv = id++;
			created[i] = nv;
			t[v].push_back(nv);
			v = nv;
			st.push_back(v);
		}
		else{
			st.pop_back();
			v = st.back();
		}
		last = cur;
	}
	vector<vector<int>> alturas(n/2+1); //altura[v][SZ-h] = quantos vértices tem a altura h na subárvore de v
	vector<pair<int, int>> ans(n/2+1);
	auto small_to_large = [&](auto rec, int v, int h)->void{
		if (t[v].size() == 0){
			alturas[v].push_back(1);
			ans[v] = {h-1, 1}; return;
		}
		for(int f : t[v])rec(rec, f, h+1);
		for(int f : t[v])if (alturas[f].size() > alturas[v].size())
			swap(alturas[f], alturas[v]), ans[v] = ans[f];
		int MY_SZ = alturas[v].size();
		for(int f : t[v]){
			int SZ = alturas[f].size();
			for(int ch = 1; ch <= SZ; ch++){
				alturas[v][MY_SZ-ch] += alturas[f][SZ-ch];
				if (alturas[v][MY_SZ-ch] > ans[v].second)ans[v] = {h+ch, alturas[v][MY_SZ-ch]};
				else if (alturas[v][MY_SZ-ch] == ans[v].second)
					if (h+ch < ans[v].first)ans[v] = {h+ch, alturas[v][MY_SZ-ch]};
			}
		}
		alturas[v].push_back(1+t[v].size());
		if (alturas[v].back() >= ans[v].second)ans[v] = {h, alturas[v].back()};
	};
	small_to_large(small_to_large, 0, 0);
	for(auto[l, r] : qs){
		auto [a, b] = ans[created[l-1]];
		cout << a << ' ' << b << '\n';
	}
}