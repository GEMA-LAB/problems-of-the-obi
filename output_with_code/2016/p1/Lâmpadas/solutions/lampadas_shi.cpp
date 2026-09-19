#include <bits/stdc++.h>

using namespace std;

int main (void) {
	int n;
	ios::sync_with_stdio(0);
	cin >> n;
	int a = 0, b = 0;
	for (int i = 0; i < n; ++i) {
		int x; cin >> x;
		if (x == 1) a = 1-a;
		else {
			a = 1-a;
			b = 1-b;
		}
	}
	cout << a << endl;
	cout << b << endl;
	return 0;
}
