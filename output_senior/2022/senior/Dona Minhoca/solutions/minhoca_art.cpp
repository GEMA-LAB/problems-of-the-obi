#include <iostream>
#include <algorithm>
#include <vector>
#define pb push_back
#define ll long long
#define pii pair<int,int>
#define debug printf
using namespace std;

#define maxn 300300

vector<int> L[maxn];

int tot;

int dfs(int v,int r,int p=-1){

	int max_need = 0, max_give = 0;

	for(int kid : L[v]){

		if(kid == p) continue;

		int val = dfs(kid,r,v);

		if(val < 0) max_need = max(max_need, -val);
		else max_give = max(max_give,val);

	}

	if(max_need == r){
		tot++;
		return r;
	}

	if(max_give - 1 >= max_need){
		if(max_give == 0) return -1;
		return max(max_give - 1, 0);
	}

	else {
		if(v == 0 && (max_need > 0  || max_give == 0)   ) tot++;
		if(max_need == 0){
			if(max_give > 0) return 0;
			else return -1;
		}
		return -(max_need + 1);
	}


}

int main(){

	int n,k;
	scanf("%d%d",&n,&k);

	for(int i=0;i<n-1;i++){
		int a,b;
		scanf("%d%d",&a,&b), a--, b--;
		L[a].pb(b);
		L[b].pb(a);
	}

	int lo = 0, hi = n;

	while(lo < hi){
	
		int mid = (lo+hi)/2;

		tot = 0;

		dfs(0,mid);

		if(tot <= k)
			hi = mid;
		else
			lo = mid+1;

	}

	printf("%d\n",lo);
}
