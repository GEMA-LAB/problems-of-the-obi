/*
	Matheus Leal V

	OBI 2019 - Fase 03 - Coleção

	Observe que colocar os Upas com maiores cores primeiros é sempre vantajoso
	pois 2^i > 2^0 + 2^1 + ... + 2^(i - 1)
*/
#include <bits/stdc++.h>
#define N 100020
using namespace std;

int n, m;

vector<int> block[N];

set<int> ans;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>m;

	for(int i = 1, u, v; i <= m; i++)
	{
		cin>>u>>v;

		block[u].push_back(v);

		block[v].push_back(u);
	}

	for(int i = n; i >= 1; i--)
	{
		bool can = true;

		for(auto w: block[i])
		{
			if(ans.count(w))
				can = false;
		}

		if(can) ans.insert(i);
	}

	cout<<(int)(ans.size())<<"\n";

	int i = 1;

	for(auto w: ans)
	{
		if(i < ans.size()) cout<<w<<" ";

		else cout<<w<<"\n";

		i ++;
	}
}