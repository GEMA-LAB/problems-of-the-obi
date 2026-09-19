#include <bits/stdc++.h>
using namespace std;

const int N = 100001;
int vet[N], aux[N], n;

int merge(int p, int n)
{
	if (n <= 1) return 0;
	int c = merge(p, n/2)+merge(p+n/2, n-n/2), d = 0, a = 0, b = n/2;
	while (d < n)
	{
		if (a != n/2 && (b == n || vet[p+a] < vet[p+b])) aux[d] = vet[p+a], ++a;
		else aux[d] = vet[p+b], c += n/2-a, ++b;
		++d;
	}
	for (int i = 0; i < n; ++i)
		vet[p+i] = aux[i];
	return c;
}

int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> vet[i];
	cout << merge(0, n) << "\n";
}

