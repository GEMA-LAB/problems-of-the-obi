#include <stdio.h>
#include <vector>
using namespace std;

int a[112345];

int main(void)
{
	int n, m, ok = 1;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for(int i = 1; i <= n; i++)
	{
		if(min(a[i], m - a[i]) >= a[i-1])
			a[i] = min(a[i], m - a[i]);
		else if(max(a[i], m - a[i]) >= a[i-1])
			a[i] = max(a[i], m - a[i]);
		else
		{
			printf("-1\n");
			return 0;
		}
	}
	long long ans = 0;
	for(int i = 1; i <= n; i++)
		ans += a[i];
	printf("%lld\n", ans);
}
