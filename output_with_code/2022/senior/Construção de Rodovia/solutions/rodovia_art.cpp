#include <iostream>
#include <algorithm>
#include <vector>
#define pb push_back
#define ll long long
#define pii pair<int,int>
#define debug printf
using namespace std;

#define maxn 300300

int mrk[maxn];
int vis[maxn];

vector<int> L[maxn];

void dfs(int v,int i){

	if(vis[v] == i+1) return;
	vis[v] = i+1;
	
	if(v != i && mrk[v] == 0){
		printf("%d %d\n",i+1,v+1);
		exit(0);
	}

	for(int a : L[v])
		dfs(a,i);
	

}


int main(){

	int n,m;
	scanf("%d%d",&n,&m);

	for(int i=0;i<m;i++){
		int a,b;
		scanf("%d%d",&a,&b), a--, b--;
		L[a].pb(b);
	}

	for(int i=n-1;i>=0;i--){

		for(int a : L[i]) mrk[a] = 1;
		dfs(i,i);
		for(int a : L[i]) mrk[a] = 0;
	
	}

	printf("-1\n");

}
