#include<bits/stdc++.h>

using namespace std;

const int N = 100010;

multiset <int> produtos[N];
multiset <pair <int, int>> todos_produtos;

void remover(int t, int p){
	produtos[t].erase(produtos[t].find(p));
	todos_produtos.erase(todos_produtos.find({p, t}));
}

int tt[N], pp[N];

int main(){
	int n, tam;
	cin >> n >> tam;
	for(int i = 1;i <= n;i++){
		cin >> tt[i];
	}
	for(int i = 1;i <= n;i++){
		cin >> pp[i];
	}
	for(int i = 1;i <= n;i++){
		produtos[tt[i]].insert(pp[i]);
		todos_produtos.insert({pp[i], tt[i]});
	}
	int c;
	cin >> c;
	long long res = 0;
	for(int i = 0;i < c;i++){
		int t;
		cin >> t;
		if(t == 0){
			if(todos_produtos.empty())
				continue;
			auto [p, t2] = *todos_produtos.begin();
			remover(t2, p);
			res += p;
		}
		else{
			if(produtos[t].empty())
				continue;
			int p = *produtos[t].begin();
			remover(t, p);
			res += p;
		}
	}
	cout << res << '\n';
}