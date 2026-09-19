#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200010;
int a[MAXN], esq[MAXN], dir[MAXN];
int main() {
	int n; scanf("%d", &n);
	int last = -1;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		esq[i] = last;
		if(a[i] != -1) last = i;
	}
	last = -1;
	for(int i = n; i >= 1; i--) {
		dir[i] = last;
		if(a[i] != -1) last = i;
	}

	for(int i = 1; i <= n; i++) {
		if(a[i] != -1) {
			printf("%d", a[i]);

			if(i != n) printf(" ");
			else printf("\n");

			continue;
		}

		if(esq[i] == -1)
			printf("%d", a[dir[i]] + (dir[i] - i));
		else if(dir[i] == -1)
			printf("%d", a[esq[i]] + (i - esq[i]));
		else
			printf("%d", min(a[esq[i]] + (i - esq[i]), a[dir[i]] + (dir[i] - i)));

		if(i != n) printf(" ");
		else printf("\n");
	}
}