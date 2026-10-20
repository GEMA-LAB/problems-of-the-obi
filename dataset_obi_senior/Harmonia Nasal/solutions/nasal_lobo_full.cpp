#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n+1),b(n+1);

    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int ans = 0;
    vector<int> bests(k+1,0);
    for(int i = 1; i <= n; i++) {
        cin >> b[i];

        if(a[i] >= b[i]) {
            ans+= a[i]-b[i];
            bests.push_back(b[i]);
        }
        else {
            bests.push_back(a[i]);
        }
    }

    sort(bests.begin(),bests.end(),greater<int>());

    for(int i = 0; i < k+1; i++) {
        ans+= bests[i];
    }    

    cout << ans << endl;
    

}
// full