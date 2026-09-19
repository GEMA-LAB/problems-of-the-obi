#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int inf = 2e9;

int32_t main() {
	int n;
	cin >> n;

	vector<int> ids;
	int a[n+1];
	for(int i = 1; i <= n; i++) {
		cin >> a[i];

		if(a[i] != -1) ids.push_back(i);
	}

	for(int i = 1; i <= n; i++) {
		int ans = inf;

		auto it = upper_bound(ids.begin(),ids.end(),i);
		if(it != ids.end()) {
			ans = min(ans,a[*it]+*it-i);
		}

		it = upper_bound(ids.begin(),ids.end(),i);
		if(it != ids.begin()) {
			it--;
			ans = min(ans,a[*it]+i-*it);
		}

		cout << ans << " ";
	}
	


}