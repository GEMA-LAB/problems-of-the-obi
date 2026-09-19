#include<iostream>
#include<queue>
using namespace std;

int32_t main() {
	int n;
	cin >> n;

	int a[n+1];

	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		if(a[i] != -1) {
			pq.push({a[i],i});
		}
	}

	while(pq.size()) {
		int i = pq.top().second;
		int ai = pq.top().first;
		pq.pop();

		if(ai != a[i]) continue;

		if(i != 1 and a[i-1] == -1) {
			a[i-1] = a[i]+1;
			pq.push({a[i-1],i-1});
		}

		if(i != n and a[i+1] == -1) {
			a[i+1] = a[i]+1;
			pq.push({a[i+1],i+1});
		}
	}

	for(int i = 1; i <= n; i++) {
		cout << a[i] << " ";
	}

	
}