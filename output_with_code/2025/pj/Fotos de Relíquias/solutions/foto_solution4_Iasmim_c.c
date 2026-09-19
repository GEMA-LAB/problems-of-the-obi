#include <stdio.h>

#define ll long long
#define maxn 100001

ll a[maxn], f[maxn], ans[maxn], psum[maxn], last[maxn], sum[maxn];

int main(){

    int n, it=0;
    scanf("%d", &n);

    for(int i=0; i < n; i++) scanf("%lld", &a[i]);
    a[n] = 1e9;
    for(int i=0; i < n; i++) scanf("%lld", &f[i]);

    last[0] = 1e9;

    for(int i=n-1; i >= 0; i--){
        int p = it-f[i];
        if(it < f[i]) ans[i] = -1;
        else ans[i] = psum[it] - psum[p] - p*(sum[it]-sum[p]);
        while(a[i] >= last[it]) it--;
        ++it;
        psum[it] = psum[it-1] + it*a[i];
        last[it] = a[i];
        sum[it] = a[i] + sum[it-1];
    }

    for(int i=0; i < n; i++) printf("%lld ", ans[i]);
    printf("\n");

    return 0;
}