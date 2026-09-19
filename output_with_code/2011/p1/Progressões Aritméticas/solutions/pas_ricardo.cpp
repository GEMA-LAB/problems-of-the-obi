#include <stdio.h>

#define MAX 100100

int v[MAX];

int main()
{
	int r,prev;
	int now;
	int n;
	int resp=1;
	r = 200200;
	prev=0;

	scanf("%d",&n);

	for(int i=0;i<n;++i)
		scanf("%d",&v[i]);
	for(int i=2;i<n;++i)
		if(2*v[i-1] != v[i-2]+v[i])
		{
			++resp;
			v[i-1]=2*v[i]-v[i+1];
		}

	printf("%d\n",resp);
	return 0;
}

