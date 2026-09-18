#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define pb push_back
#define ll long long
#define pii pair<int,int>
#define debug 
using namespace std;

#define maxn 505

int freq[maxn];

int dp[maxn][maxn];

int get(int pos,int k){

	if(pos <= 1) return 0;

	int & ret = dp[pos][k];
	if(ret+1) return ret;

	ret = 999999999;
	int tot = 0;

	for(int i=pos;i>=1;i--){

		tot += (pos-i) * freq[i];
		if(k > 1 || i == 1) ret = min(ret, get(i-1,k-1) + tot);	

	}

	return ret;

}

int main(){

	int n,k;
	scanf("%d%d",&n,&k);

	int mx = 0;

	for(int i=0;i<n;i++){
		int a;
		scanf("%d",&a);
		mx = max(mx,a);
		freq[a]++;
	}

	memset(dp,-1,sizeof(dp));

	printf("%d\n",get(mx,k));

}
