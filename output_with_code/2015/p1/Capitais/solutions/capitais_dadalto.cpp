/****************************************************************************
 * Arthur Pratti Dadalto
 * OBI 2015 - Capitais
 * DFS
 ***************************************************************************/

#include <stdio.h>
#include <vector>
using namespace std;

#define inf 0x3f3f3f3f

vector<int> graph[112345];
int ans = inf;

int dfs(int a, int p)
{
	pair<int,int> best(inf, inf);
	if(graph[a].size() == 1)
		best.first = 0;
	for(int i = 0; i < graph[a].size(); i++)
		if(graph[a][i] != p)
		{
			int x = dfs(graph[a][i], a);
			if(x < best.second)
				best.second = x;
			if(best.second < best.first)
				swap(best.second, best.first);
		}
	ans = min(ans, best.first + best.second);
	return best.first + 1;
}

int
main(void)
{
	int n, a, b;
	scanf("%d", &n);
	for(int i = 0; i < n - 1; i++)
	{
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	dfs(1,1);
	printf("%d\n", ans);
}