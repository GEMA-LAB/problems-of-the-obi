/*
	Matheus Leal V
	
	OBI 2019 - Fase 03 - Coleção

	Complexidade O(N + M)
*/
#include <bits/stdc++.h>
#define N 100001
using namespace std;

int n, m, mark[N];

vector<int> block[N];

vector<int> ans;

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
			if(mark[w])
				can = false;
		}

		if(can) mark[i] = 1;
	}

	for(int i = 1; i <= n; i++) if(mark[i]) ans.push_back(i);

	cout<<(int)(ans.size())<<"\n";

	int i = 1;

	for(auto w: ans)
	{
		if(i < ans.size()) cout<<w<<" ";

		else cout<<w<<"\n";

		i ++;
	}
}