#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 6;
const ll MOD = 1e9 + 7;

ll dp_sum_total[MAXN];
ll dp_sum_mini[MAXN];
ll dp_mini_len[MAXN];

typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;

void init(){
	for(int i=0;i<MAXN;i++){
		dp_sum_total[i] = dp_sum_mini[i] = dp_mini_len[i] = -1;
	}
}

iii solve(int x){
	//cerr << "x = " << x << endl;
	if(x == 0){
		return make_pair(0, make_pair(1, 1));
	}

	if(dp_sum_total[x] != -1) return make_pair(dp_mini_len[x], make_pair(dp_sum_total[x], dp_sum_mini[x]));

	ll sum_total = 0;
	ll sum_mini = 0;
	ll mini_len = 1e9+7;

	ll r = 1;
	ll sm = 1;

	while(sm <= x){
		auto ret = solve(x - sm);

		sum_total += ret.second.first;
		if(ret.first < mini_len){
			mini_len = ret.first;
			sum_mini = ret.second.second;
		}
		else if(ret.first == mini_len){
			sum_mini += ret.second.second;
		}

		sum_total %= MOD;
		sum_mini %= MOD;

		r++;
		sm += r*r;
	}

	dp_sum_total[x] = sum_total;
	dp_sum_mini[x] = sum_mini;
	dp_mini_len[x] = mini_len + 1;

	return make_pair(mini_len + 1, make_pair(sum_total, sum_mini));
}

int main(){
	init();

	int g, m;
	cin >> g >> m;

	for(int i=0;i<MAXN;i++) solve(i);

	iii ans = solve(g);

	if(m == 1) cout << ans.second.first << endl;
	else cout << ans.second.second << endl;
}