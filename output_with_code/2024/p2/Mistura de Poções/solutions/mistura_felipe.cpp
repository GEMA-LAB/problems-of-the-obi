#include<bits/stdc++.h>

using namespace std;

int main(){
    int n, k;
    cin>>n>>k;
    vector<int>a(n + 1);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<int>x(n, n), y(n, n);
    for(int i=n-2;i>=0;i--){
        if(a[i] == a[i+1]) x[i] = x[i+1], y[i] = y[i+1];
        else{
            x[i] = i+1;
            if(a[x[i+1]] == a[i]) y[i] = y[i+1];
            else y[i] = x[i+1];
        }
    }
    long long ans = 0;
    for(int i=0;i<n;i++) ans += k == 2 ? n - x[i] : n - y[i];
    cout<<ans<<"\n";
}