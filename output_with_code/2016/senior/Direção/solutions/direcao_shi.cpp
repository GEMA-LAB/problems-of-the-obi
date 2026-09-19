#include <bits/stdc++.h>

using namespace std;

int main (void) {
	string a, b;
	string N = "norte", S = "sul", L = "leste", O = "oeste";
	cin >> a >> b;
	if (a == N) {
		if (b == S) cout << 180 << endl;
		else if (b != N) cout << 90 << endl;
		else cout << 0 << endl;
	} else if (a == S) {
		if (b == N) cout << 180 << endl;
		else if (b != S) cout << 90 << endl;
		else cout <<  0 << endl;
	} else if (a == L) {
		if ( b == O ) cout << 180 << endl;
		else if (b != a) cout << 90 << endl;
		else cout << 0 << endl;
	} else {
		if (b == L) cout << 180 << endl;
		else if (a != b) cout << 90 << endl;
		else cout << 0 << endl;
	}
	return 0;
}
