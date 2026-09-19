#include <bits/stdc++.h>
using namespace std;

const int N = 1000;

int mat[N][N];

int main()
{
	ios::sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			cin >> mat[i][j];
	int res = INT_MAX;
	for (int j = 0; j < m; ++j)
	{
		int tmp = 0;
		for (int i = 0; i < n; ++i)
			tmp += mat[i][j];
		res = min(res, tmp);
	}
	cout << res << endl;
}

