#include <stdio.h>

int main(void)
{
	int n, ans = 0, a;
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &a);
		if(a == 2)
			ans = 1 - ans;
	}
	printf("%d\n%d\n", n % 2, ans);
}