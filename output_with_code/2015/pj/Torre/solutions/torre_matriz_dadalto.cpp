#include <stdio.h>
#include <vector>

int sline[1123], scol[1123], a[1123][1123];

int
main(void)
{
	int n, ans = 0;
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; sline[i] += a[i][j], scol[j] += a[i][j], j++)
			scanf("%d", &a[i][j]);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			ans = std::max(ans, sline[i] + scol[j] - 2*a[i][j]);
	printf("%d\n", ans);
}