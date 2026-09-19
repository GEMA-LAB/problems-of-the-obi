#include <bits/stdc++.h>
#define int long long

using namespace std;

struct E {
    int x, y, d;
    bool operator<(const E e) const {
        return d > e.d;
    }
};

const int maxn = 1010, inf = 1e18;
const int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int v[maxn][maxn], dist[maxn][maxn], vis[maxn][maxn];
int n, m, t, xa, ya, xb, yb;

void dijkstra(int k) {
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            dist[i][j] = inf;
    dist[xa][ya] = 0;
    
    priority_queue<E> q;
    q.push({xa, ya, 0});
    while (!q.empty()) {
        E s = q.top(); q.pop();
        if (vis[s.x][s.y] || v[s.x][s.y] == -1) continue;
        vis[s.x][s.y] = true;
        for (int d = 0; d < 4; ++d) {
            int nx = s.x + dir[d][0], ny = s.y + dir[d][1];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (dist[nx][ny] > dist[s.x][s.y] + v[s.x][s.y] * k) {
                dist[nx][ny] = dist[s.x][s.y] + v[s.x][s.y] * k;
                q.push({nx, ny, dist[nx][ny]});
            }
        }
    }
}

bool ok(int k) {
    dijkstra(k);
    return dist[xb][yb] <= t;
}

void solve() {
    cin >> n >> m >> t;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> v[i][j];
    cin >> xa >> ya >> xb >> yb;
    xa--, ya--, xb--, yb--;

    int l = 0, r = 2e9, ans = -1;
    while (l <= r) {
        int mid = (l+r)/2;
        if (ok(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}