/****************************************************************************
 * Arthur Pratti Dadalto
 * OBI 2016
 * Algoritmo de Euclides
/***************************************************************************/
#include <stdio.h>

long long gcd(long long a, long long b)
{
	return (b == 0) ? a : gcd(b, a % b);
}

int main(void)
{
	long long n, m;
	scanf("%lld %lld", &n, &m);
	for(long long i = m; i >= 1; i--)
		if(gcd(i, n) == 1)
		{
			printf("%lld\n", i);
			return 0;
		}
}