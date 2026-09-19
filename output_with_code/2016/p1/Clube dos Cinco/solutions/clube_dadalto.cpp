#include <stdio.h>

int main(void)
{
	int n, a, b, c, d, e, f, g;
	scanf("%d %d %d %d %d %d %d %d", &n, &a, &b, &c, &d, &e, &f, &g);
	if(n == g + a + b + c - d - e - f)
		printf("N\n");
	else
		printf("S\n");
}