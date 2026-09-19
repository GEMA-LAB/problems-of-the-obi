#include<bits/stdc++.h>
using namespace std;
using lint = int64_t;

int main(){
    int n, m, t;
    cin>>n>>m>>t;
    vector<vector<int>>p(n, vector<int>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>p[i][j];
        }
    }
    int x1, y1, x2, y2;
    cin>>x1>>y1>>x2>>y2;
    x1--, y1--, x2--, y2--;
    vector<int>dx = {0, 1, 0, -1};
    vector<int>dy = {1, 0, -1, 0};
    int lo = 0, hi = 1e9;
    const lint inf = 1e18;
    for(int z=0;z<80;z++){
        int mid = (lo + hi) / 2;
        vector<vector<lint>>dist(n, vector<lint>(m, inf));
        priority_queue<pair<lint, pair<int, int>>, vector<pair<lint, pair<int, int>>>, greater<pair<lint, pair<int, int>>>>pq;
        dist[x1][y1] = 0;
        pq.push({0, {x1, y1}});
        while(!pq.empty()){
            auto [d, id] = pq.top();
            pq.pop();
            auto [x, y] = id;
            if(dist[x][y] < d || p[x][y] == -1) continue;
            for(int k=0;k<4;k++){
                int nx = x + dx[k];
                int ny = y + dy[k];
                if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                lint nd = d + lint(p[x][y]) * mid;
                if(nd < dist[nx][ny]){
                    dist[nx][ny] = nd;
                    pq.push({nd, {nx, ny}});
                }
            }
        }
        if(dist[x2][y2] > t) hi = mid - 1;
        else lo = mid + 1;
    }
    cout<<hi<<"\n";
}