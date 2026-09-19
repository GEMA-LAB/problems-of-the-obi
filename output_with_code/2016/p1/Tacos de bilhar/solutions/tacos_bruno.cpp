#include <bits/stdc++.h>
using namespace std;

set<int> s;
int m;

int main()
{
	ios::sync_with_stdio(0);
	cin >> m;
	int res = 0;
	while (m--)
	{
		int a;
		cin >> a;
		if (s.count(a)) s.erase(a);
		else s.insert(a), res += 2;
	}
	cout << res << endl;
}

