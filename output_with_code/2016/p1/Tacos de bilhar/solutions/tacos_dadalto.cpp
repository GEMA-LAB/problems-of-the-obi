/****************************************************************************
 * Arthur Pratti Dadalto
 * OBI 2016
 ***************************************************************************/
#include <stdio.h>

int tab[1123456];

int main(void)
{
	int n, a, ans = 0;
	scanf("%d", &n);
	for(int i = 0; i < n; tab[a]++, i++)
		scanf("%d", &a);
	for(int i = 0; i < 1123456; i++)
		ans += (tab[i] + (tab[i] % 2));
	printf("%d\n", ans);
}