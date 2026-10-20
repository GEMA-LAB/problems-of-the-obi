#include<iostream>
using namespace std;

const int inf = 2e9;

int32_t main() {
	int n;
	cin >> n;

	int a[n+1], ans[n+1];

	for(int i = 1; i <= n; i++) {
		cin >> a[i];

		if(a[i] == -1) {
			ans[i] = inf;
		}
		else {
			ans[i] = a[i];
		}
	}

	int l = -1;

	for(int i = 1; i <= n; i++) {
		if(a[i] != -1) l = i;

		if(l != -1) {
			ans[i] = min(ans[i], a[l]+(i-l));
		}
	}

	int r = -1;
	for(int i = n; i >= 1; i--) {
		if(a[i] != -1) r = i;

		if(r != -1) {
			ans[i] = min(ans[i], a[r]+(r-i));
		}
	}

	for(int i = 1; i < n; i++) {
		cout << ans[i] << " ";
	}
    cout << ans[n] << endl;
}