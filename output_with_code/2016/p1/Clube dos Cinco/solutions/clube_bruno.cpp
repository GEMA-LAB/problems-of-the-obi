#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	int n, a, b, c, d, e, f, g;
	cin >> n >> a >> b >> c >> d >> e >> f >> g;
	n -= d+e+f+g;
	a -= d+e;
	b -= d+f;
	c -= e+f;
	cout << ((n < 0 || a < 0 || b < 0 || c < 0 || n != a+b+c) ? "S" : "N") << endl;
}

