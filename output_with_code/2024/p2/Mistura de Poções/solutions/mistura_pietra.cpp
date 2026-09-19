#include<bits/stdc++.h>
using namespace std ; 
 
const int maxn = 1e5 + 5 ; 
 
int a[maxn], freq[maxn], ctr ; 
 
void add(int val){
    freq[val]++ ; 
    if(freq[val] == 1) ctr++ ; 
}
 
void remove(int val){
    freq[val]-- ; 
    if(freq[val] == 0) ctr-- ; 
}
 
int main(){
 
    int n, k ; cin >> n >> k ; 
 
    for(int i = 1; i <= n ; i++){
        cin >> a[i] ; 
    }
 
    long long int ans = 0 ; 
 
    for(int l = 1, r = 0 ; l <= n ; l++){
        while(ctr < k && r < n){
            add(a[++r]) ; 
        }
        if(ctr>=k) ans += (n-r+1) ;
        remove(a[l]) ;  
    }
 
    cout << ans << " \n" ; 
 
}
