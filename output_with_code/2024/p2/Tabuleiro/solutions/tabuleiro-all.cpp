/*
Pieces available, no rotation available
A  BB  CC   D  E   FF  GG  I   HH
A  B    C  DD  EE  F    G  II   H
A  BB  CC   D  E

Cases 
n = 1
A
A
A

n = 2
FF  HH
FG  IH
GG  II

n = 3
BBD  ECC
BDD  EEC
BBD  ECC

Recurence
f(n) = f(n-1) + 2*f(n-2) + 2*f(n-3)
*/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100100, MOD = 1e9 + 7;
int memo[MAXN];

int f(int n){
    if(n <= 0)
        return 0;
    if(n == 1)
        return 1;
    if(n == 2)
        return 3;
    if(n == 3)
        return 2 + 2 + 2 + 1;
    if(memo[n] != -1)
        return memo[n];
    return memo[n] = (1ll * f(n-1) + 2ll * f(n-2) % MOD + 2ll * f(n-3) % MOD) % MOD;
}

int main(){
    memset(memo, -1, sizeof memo);
    int n;
    cin >> n;
    cout << f(n) << "\n";
}
