#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2000010;

int n, d;
long long int p, sp[MAXN];

struct maxqueue
{
	int ini = 1, fim = 0;
	deque<pair<long long int, int > > mq;

	void insert(long long int val)
	{
		fim++;
		while(!mq.empty() && mq.back().first <= val)	mq.pop_back();
		mq.push_back({val, fim});
	}

	void erase()
	{
		if(mq.front().second == ini)	mq.pop_front();
		ini++;
	}

	long long int max()
	{
		if(mq.empty())	return 0;
		return mq.front().first;		
	}
};

maxqueue mq;

int main ()
{
	scanf("%d %d %lld", &n, &d, &p);

	for(int i = 1, a; i <= n; i++)
		scanf("%d", &a), sp[i] = sp[i - 1] + a;

	int ini = 1, fim = d, ans = d;
	mq.insert(sp[fim]);
	while(fim <= n)
	{
		if(sp[fim] - sp[ini - 1] - mq.max() > p)	ini++, mq.erase();
		else
		{
			ans = max(ans, fim - ini + 1);
			fim++;
			mq.insert(sp[fim] - sp[fim - d]);
		}
	}

	printf("%d\n", ans);
}