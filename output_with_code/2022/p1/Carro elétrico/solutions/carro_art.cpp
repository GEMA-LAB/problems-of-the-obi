#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define maxn 400400
#define mod 1000000007
#define debug(args...) fprintf(stderr,args)
using namespace std;

int n,d;
int x[maxn];
int y[maxn];

int p[maxn];

int find(int x){
	return p[x] = (x == p[x]) ? x : find(p[x]);
}

int main(){

	scanf("%*d%*d%d%d",&n,&d);

	for(int i=0;i<n;i++)
		scanf("%d%d",x+i,y+i), p[i] = i;

	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			if(100*(abs(x[i]-x[j]) + abs(y[i]-y[j])) <= d)	
				p[find(i)] = find(j);

	int ans = -1;
	for(int i=0;i<n;i++)
		if(p[i] == i) ans++;

	printf("%d\n",ans);	


}
