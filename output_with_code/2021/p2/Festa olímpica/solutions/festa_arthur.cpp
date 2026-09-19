#include <bits/stdc++.h>
#define ll long long
#define maxn 10100
#define pii pair<int,int>
#define pb push_back
#define debug 
using namespace std;

int ans[maxn];
int v[maxn];

int main(){

	int n,m;
	scanf("%d%d",&n,&m);

	for(int i=0;i<min(n,maxn);i++)
		ans[i] = i;

	for(int i=0;i<m;i++)
		scanf("%d",v+i), assert(v[i] == 2);

	for(int i=m-1;i>=0;i--)
		for(int j=0;j<min(n,maxn) && ans[j] < n;j++)
			ans[j] += ans[j] / (v[i]-1);

	for(int i=0;i<min(n,10000) && ans[i] < n;i++)
		printf("%d\n",ans[i]+1);

}
