/****************************************************************************
 * Arthur Pratti Dadalto
 * OBI 2016
 * BFS (O(N + M))
 ***************************************************************************/
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> ans[2];
int times[112345];
vector<int> graph[112345];

int main(void)
{
	int n, m, a;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &m);
		for(int j = 0; j < m; j++)
		{
			scanf("%d", &a);
			graph[i].push_back(a);
		}
	}
	queue<int> q;
	q.push(1);
	ans[0].push_back(1);
	times[1] = 1;
	while(!q.empty())
	{
		a = q.front();
		q.pop();
		for(int i = 0; i < graph[a].size(); i++)
			if(times[graph[a][i]] == 0)
			{
				times[graph[a][i]] = (times[a] % 2) + 1;
				ans[times[graph[a][i]] - 1].push_back(graph[a][i]);
				q.push(graph[a][i]);
			}
	}
	sort(ans[0].begin(), ans[0].end());
	sort(ans[1].begin(), ans[1].end());
	printf("%d", ans[0][0]);
	for(int i = 1; i < ans[0].size(); i++)
		printf(" %d", ans[0][i]);
	printf("\n");
	printf("%d", ans[1][0]);
	for(int i = 1; i < ans[1].size(); i++)
		printf(" %d", ans[1][i]);
	printf("\n");
}