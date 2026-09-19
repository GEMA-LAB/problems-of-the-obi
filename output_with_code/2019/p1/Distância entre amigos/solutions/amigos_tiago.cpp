#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
vector<int> v;


int32_t main(){
	cin>>n;
	v.resize(n);
	ll maxi = 0; 
	ll ans = 0;
	for(int i = 0 ; i < n; i ++){
		cin>>v[i];
		ans = max(ans ,  ((ll) v[i] + i) + maxi);
		maxi = max(maxi , (ll)(v[i] - i));
	}
	cout<<ans<<endl;
}