/*
	Matheus Leal V
	OBI 2019 - Fase 01 - Calçada Imperial
*/

#include <bits/stdc++.h>
#define N 200020
using namespace std;
typedef long long ll;

int n;

ll v[N], ans;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n;

	for(int i = 1; i <= n; i++) cin>>v[i];

	ll melhor = -1000000000000000LL;

	for(int i = 1; i <= n; i++)
	{
		ans = max(ans, v[i] + i + melhor);

		melhor = max(melhor, v[i] - i);
	}

	cout<<ans<<'\n';
}