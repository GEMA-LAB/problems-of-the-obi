#include <bits/stdc++.h>

using namespace std;


const int N = 1002;

double  dp[N];
double D;
double P[N], C[N];

int main (void) { 

	int n;
	scanf ("%d %lf", &n, &D);

	for (int i = 0; i < n; ++i) {
		scanf ("%lf %lf", &P[i], &C[i]);
	}
	
	P[n] = D;	
	for (int i = 0; i <= n; ++i) {
		dp[i] = (P[i]*P[i])/C[0];
		for (int j = 0; j < i; ++j) {
			dp[i] = min (dp[i], dp[j]+((P[i]-P[j])*(P[i]-P[j]))/C[j]);
		}
	}

	printf ("%.3lf\n", dp[n]);	
	
	return 0;
}
