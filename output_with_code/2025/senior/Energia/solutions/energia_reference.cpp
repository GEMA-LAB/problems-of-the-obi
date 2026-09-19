#include<bits/stdc++.h>
using namespace std;
#define int long long

const int maxn = 2e5+10;

int n, q, K, a[maxn], ans, cntid;
int myid[maxn], lid[maxn], rid[maxn];
vector<int> map1[maxn],map2[maxn];
vector<int> cc1, cc2;

int getansr(int i) {
    int id = myid[i];
    int myans = 0;
    {
        // j < i, a[j] <= a[i] -> gap(i,j) = i-j+a[i]-a[j] = K -> j+a[j] = i+a[i]-K
        // i-j <= k -> i-k <= j <= i-1

        int to = lower_bound(cc1.begin(),cc1.end(),i+a[i]-K) - cc1.begin();
        if(to != cc1.size() and cc1[to] == i+a[i]-K) {
            int l = max(i-K,lid[id]);
            int r = min(i-1,rid[id]);

            myans+= max((int) 0,(int) (upper_bound(map1[to].begin(),map1[to].end(),r) - lower_bound(map1[to].begin(),map1[to].end(),l)));
        }
        
    }

    {
        // j < i, a[j] > a[i] -> gap(i,j) = i-j+a[j]-a[i] = K -> j-a[j] = i-a[i]-K

        // i-j < k ->  i-k+1 <= j <= i-1

        int to = lower_bound(cc2.begin(),cc2.end(),i-a[i]-K) - cc2.begin();
        if(to != cc2.size() and cc2[to] == i-a[i]-K) {
            int l = max(i-K+1,lid[id]);
            int r = min(i-1,rid[id]);

            myans+= max((int) 0,(int) (upper_bound(map2[to].begin(),map2[to].end(),r) - lower_bound(map2[to].begin(),map2[to].end(),l)));
        }
    }

    return myans;
}

int getansl(int i) {
    int id = myid[i];
    int myans = 0;
    {
        // i < j, a[i] <= a[j] -> gap(i,j) = j-i+a[j]-a[i] = K -> j+a[j] = i+a[i]+K

        // j-i <= k -> i+1 <= j <= i+k

        int to = lower_bound(cc1.begin(),cc1.end(),i+a[i]+K) - cc1.begin();
        if(to != cc1.size() and cc1[to] == i+a[i]+K) {
            int l = max(i+1,lid[id]);
            int r = min(i+K,rid[id]);

            myans+= max((int) 0,(int) (upper_bound(map1[to].begin(),map1[to].end(),r) - lower_bound(map1[to].begin(),map1[to].end(),l)));
        }
    }

    {
        // i < j, a[i] > a[j] -> gap(i,j) = j-i+a[i]-a[j] = K -> j-a[j] = i-a[i]+K

        // j-i < k -> i+1 <= j <= i+k-1
        int to = lower_bound(cc2.begin(),cc2.end(),i-a[i]+K) - cc2.begin();
        if(to != cc2.size() and cc2[to] == i-a[i]+K) {
            int l = max(i+1,lid[id]);
            int r = min(i+K-1,rid[id]);

            myans+= max((int) 0,(int) (upper_bound(map2[to].begin(),map2[to].end(),r) - lower_bound(map2[to].begin(),map2[to].end(),l)));
        }
    }

    return myans;
}

void create(int l, int r) {
    int id = ++cntid;
    lid[id] = l;
    rid[id] = l-1;

    for(int i = l; i <= r; i++) {
        rid[id]++;
        myid[i] = id;

        ans+= getansr(i);
    }
}

void removel(int id) {
    int i = lid[id];
    ans-= getansl(i);
    myid[i] = -1;
    lid[id]++;
}

void remover(int id) {
    int i = rid[id];
    ans-= getansr(i);
    myid[i] = -1;
    rid[id]--;
}

int32_t main() {
    cin >> n >> q >> K;

    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        cc1.push_back(i+a[i]);
        cc2.push_back(i-a[i]);
    }

    sort(cc1.begin(),cc1.end());
    cc1.erase(unique(cc1.begin(),cc1.end()),cc1.end());
    sort(cc2.begin(),cc2.end());
    cc2.erase(unique(cc2.begin(),cc2.end()),cc2.end());

    for(int i = 1; i <= n; i++) {
        int to1 = lower_bound(cc1.begin(),cc1.end(),i+a[i]) - cc1.begin();
        int to2 = lower_bound(cc2.begin(),cc2.end(),i-a[i]) - cc2.begin();
        map1[to1].push_back(i);
        map2[to2].push_back(i);
    }

    create(1,n);

    cout << ans << endl;

    while(q--) {
        int i;
        cin >> i;

        int id = myid[i];

        int l = lid[id];
        int r = rid[id];

        if(i == l) {
            removel(id);
        }
        else if(i == r) {
            remover(id);
        }
        else if((i-l) < (r-i)) {
            for(int j = l; j <= i; j++) removel(id);
            create(l,i-1);
        }
        else {
            for(int j = r; j >= i; j--) remover(id);
            create(i+1,r);
        }

        cout << ans << endl;
    }
}
