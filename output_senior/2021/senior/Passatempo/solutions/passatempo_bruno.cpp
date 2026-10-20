#include <bits/stdc++.h>
using namespace std;

const int N = 100, M = 26*26;

int con[2*N][N], val[2*N], res[M], l, c;
set<string> p;

int calc(string s)
{
	assert(s.size() == 2);
	return (s[0]-'a')*26+(s[1]-'a');
}

void solve()
{
	vector<int> use; // pegando varios candidatos, so pra validar
	for (int i = 0; i < l+c; ++i)
	{
		int m = i >= l ? l : c;
		int cnt = -1;
		for (int j = 0; j < m && cnt != -2; ++j) if (res[con[i][j]] == INT_MIN)
		{
			if (cnt == -1) cnt = con[i][j];
			else if (cnt != con[i][j]) cnt = -2;
		}
		if (cnt < 0) continue;
		use.push_back(i);
	}
	assert(use.size() > 0);
	int i = use[rand()%use.size()];
	int m = i >= l ? l : c, s = val[i], k, d = 0;
	for (int j = 0; j < m; ++j)
	{
		if (res[con[i][j]] != INT_MIN) s -= res[con[i][j]];
		else k = con[i][j], ++d;
	}
	assert(s%d==0);
	res[k] = s/d;
}

int main()
{
	srand(time(0));
	ios::sync_with_stdio(0);
	cin >> l >> c;
	for (int i = 0; i < M; ++i)
		res[i] = INT_MIN;
	for (int i = 0; i < l; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			string s; cin >> s;
			p.insert(s);
			int k = calc(s);
			con[i][j] = k;
			con[l+j][i] = k;
		}
		cin >> val[i];
	}
	for (int i = 0; i < c; ++i)
		cin >> val[l+i];
	for (int i = 0; i < (int) p.size(); ++i)
		solve();
	for (set<string>::iterator it = p.begin(); it != p.end(); ++it)
	{
		assert(res[calc(*it)] != INT_MIN);
		cout << *it << " " << res[calc(*it)] << "\n";
	}
}

