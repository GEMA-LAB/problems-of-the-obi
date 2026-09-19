#include <bits/stdc++.h>
using namespace std;

const int N = 300001;

int vet[N][26], n;
char in[N];

int main()
{
	ios::sync_with_stdio(0);
	cin >> in;
	n = strlen(in);
	
	for (int i = 0; i < n; ++i)
	{
		int k = in[i]-'A';
		for (int j = 0; j < 26; ++j)
			vet[i+1][j] = vet[i][j];
		for (int j = k; j < 26; ++j)
			vet[i+1][j] = max(vet[i+1][j], vet[i][k]+1);
	}
	
	cout << vet[n][25] << endl;
}

