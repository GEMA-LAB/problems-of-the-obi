#include <bits/stdc++.h>
using namespace std;

// Brute force just to guarantee :)

int main()
{
    vector<int> v;
    for (int i = 0; i < 4; ++i)
    {
        int x; cin >> x;
        v.push_back(x);
    }
    int res = 1e9;
    do
    {
        res = min(res, abs(v[0]+v[1]-v[2]-v[3]));
    } while (next_permutation(v.begin(), v.end()));
    cout << res << endl;
}

