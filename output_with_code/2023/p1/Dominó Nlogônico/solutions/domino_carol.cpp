#include <iostream>
#include <algorithm>
#include <stack>
const int MAXN =3e5+10;
const int INF = 2e9+10;

using namespace std;

int n;
int x[MAXN], h[MAXN];
int dp[MAXN];

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> x[i];
    }
    for(int i = 1; i <=n ;i ++){
        cin >> h[i];
    }

    x[n+1] = INF;
    stack<int> q;
    q.push(n+1);

    for(int i = n; i > 0; i--){
        int next = x[i]+h[i];
        int topo = q.top();

        while(x[topo] <= next){
            q.pop();
            topo = q.top();
        }
        dp[i] = q.top()-i;
        q.push(i);
    }

    for(int i = 1;i < n; i++){
        cout << dp[i] << " ";
    }
    cout << dp[n] << "\n";

}