#include <bits/stdc++.h>
#define pb push_back
#define ll long long
#define pii pair<int,int>
#define debug printf
using namespace std;

#define maxn 300300

int v[maxn];

main(){

	int n,s = 0;
	scanf("%d",&n);

	for(int i=0;i<n;i++){
		scanf("%d",v+i);
		s += v[i];
	}

	s /= n;

	for(int i=0;i<n;i++)
		printf("%d\n",s-v[i]);

}
