#include <bits/stdc++.h>
using namespace std;

int main() {

  int n, m, k;
  cin >> n >> m >> k;

  if(n/k < m) {
    cout << -1 << "\n";
    return 0;
  }

  vector<int> rating;
  int mini = 0;
  int maxi = 0;

  for(int i=0;i<n;i++) {
    int x;
    cin >> x;
    rating.push_back(x);
    maxi = max(maxi, x);
  }

  int l = mini;
  int r = maxi+1;
  while(l < r) {
    int p = (l+r)/2;
  
    int groups = 0;
    int cnt_less = 0;
    for(int i=0;i<rating.size();i++) {
      if(rating[i] < p) cnt_less++;
      if(cnt_less == m) cnt_less = 0, groups++; 
    }
    

    if(groups < k) l = p+1;
    else r = p;
  }

  cout << l << "\n";
}
