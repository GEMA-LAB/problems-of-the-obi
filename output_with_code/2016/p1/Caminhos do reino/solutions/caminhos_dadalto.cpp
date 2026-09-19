/****************************************************************************
 * Arthur Pratti Dadalto
 * OBI 2016
 * Percurso em grafo - DFS (O(N + Q))
 ***************************************************************************/

#include <stdio.h>
#include <vector>

int f[112345], in[112345], h[112345], incycle[112345], link[112345];
int sz;

void dfs(int a)
{
	if(incycle[a] == 1)	return;
	dfs(f[a]);
	h[a] = h[f[a]] + 1, link[a] = link[f[a]];
}

int abs(int x) { return (x < 0) ? -x : x; }

int solve(int a, int b)
{
	if(link[a] == link[b])
		return abs(h[a] - h[b]);
	return std::min(std::max(h[b], h[a] + ((link[b] - link[a] + sz) % sz)), std::max(h[a], h[b] + ((link[a] - link[b] + sz) % sz)));
}

int main(void)
{
	int n, q, a, b;
	scanf("%d", &n);
	for(int i = 1; i <= n; in[f[i]]++, i++)
		scanf("%d", &f[i]);
	for(int i = 1; i <= n; i++)
		if(in[i] >= 2)
		{
			sz = 1, incycle[i] = 1;
			for(int j = f[i]; j != i; j = f[j])
				incycle[j] = 1, link[j] = sz++;
			break;
		}
	for(int i = 1; i <= n; i++)
		if(in[i] == 0)
			dfs(i);
	scanf("%d", &q);
	while(q--)
	{
		scanf("%d %d", &a, &b);
		printf("%d\n", solve(a,b));
	}
}