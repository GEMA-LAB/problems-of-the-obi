#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b)
{
	if (!b) return a;
	return gcd(b, a%b);
}

int main()
{
	ll a, b;
	cin >> a >> b;
	// espacamento entre primos eh pequeno
	while (gcd(a, b) != 1) --b;
	cout << b << endl;
}

