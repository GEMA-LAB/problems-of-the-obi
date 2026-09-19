#include <iostream>
#include <algorithm>
#include <map>
#include <queue>

const int MAX = 1e5+10;

using namespace std;

int n, m;
int f[MAX], t[MAX];
priority_queue<pair<long long, int> > q;

int main(){
    cin >> m >> n;
    for(int i = 1; i <= m; i++){
        cin >> f[i];
    }
    for(int i = 1; i <= n; i++){
        cin >> t[i];
        q.push(make_pair(0, i));
    }

    sort(f+1, f+1+m);
    long long ans = 0;

    for(int i = m; i > 0; i--){
        pair<long long, int> p = q.top();
        q.pop();
        
        long long small = p.first;
        int ix = p.second;
        long long qtt = small/t[ix];

        ans -= small * f[i];

        q.push(make_pair((qtt-1)*t[ix], ix));
    }

    cout << ans << '\n';

}