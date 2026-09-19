#include <bits/stdc++.h>

using namespace std;

const int maxn = 100'001;
int a[maxn];

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    long long ans = 0;

    vector<int> c;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < (int) c.size(); ++j) {
            if (a[c[j]] == a[i]) {
                c.erase(c.begin() + j);
                break;
            }
        }
        c.push_back(i);
        if ((int) c.size() > k) {
            c.erase(c.begin());
        }
        if ((int) c.size() == k) {
            ans += c[0];
        }
    }

    cout << ans << '\n';

    return 0;
}
