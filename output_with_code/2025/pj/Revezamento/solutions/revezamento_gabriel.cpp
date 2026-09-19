#include <bits/stdc++.h>

using namespace std;

using i64 = int64_t;

vector<vector<i64>> m, f;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  cin >> n;


  for(int i = 0; i < n; i++) {
    int sex, a, b, c, d;
    cin >> sex;

    cin >> a >> b >> c >> d;

    if(sex == 0) f.push_back({a, b, c, d});
    else m.push_back({a, b, c, d});
  }

  if(m.size() < 2 or f.size() < 2) {
    cout << -1 << '\n';
    return 0;
  }

  const int inf = 1e9 + 10;
  vector<pair<int,int>> bests = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
  vector<pair<int,int>> best_pt = {{inf,inf}, {inf,inf}, {inf,inf}, {inf,inf}};

  for(int i = 0; i < m.size(); i++) {
    for(int j = 0; j < 4; j++) {
      if(m[i][j] < best_pt[j].first) {
        bests[j].second = bests[j].first;
        bests[j].first = i;
        best_pt[j].second = best_pt[j].first;
        best_pt[j].first = m[i][j];
        continue;
      }

      if(m[i][j] < best_pt[j].second) {
        bests[j].second = i;
        best_pt[j].second = m[i][j];
        continue;
      }
      
    }
  }

  set<int> st;

  for(int i = 0; i < bests.size(); i++) {
    if(bests[i].first != -1) st.insert(bests[i].first);
    if(bests[i].second != -1) st.insert(bests[i].second);
  }

  vector<vector<i64>> ansM;
  for(auto &i : st) {
    ansM.push_back(m[i]);
  }


  bests = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
  best_pt = {{inf,inf}, {inf,inf}, {inf,inf}, {inf,inf}};


  for(int i = 0; i < f.size(); i++) {
    for(int j = 0; j < 4; j++) {
      if(f[i][j] < best_pt[j].first) {
        bests[j].second = bests[j].first;
        bests[j].first = i;
        best_pt[j].second = best_pt[j].first;
        best_pt[j].first = f[i][j];
        continue;
      }

      if(f[i][j] < best_pt[j].second) {
        bests[j].second = i;
        best_pt[j].second = f[i][j];
        continue;
      }
    }
  }

  st.clear();
  for(int i = 0; i < bests.size(); i++) {
    if(bests[i].first != -1) st.insert(bests[i].first);
    if(bests[i].second != -1) st.insert(bests[i].second);
  }

  vector<vector<i64>> ansF;
  for(auto &i : st) {
    ansF.push_back(f[i]);
  }

  i64 ans = 1e16 + 10;

  for(int i = 0; i < (1 << ansM.size()); i++) {
    for(int j = 0; j < (1 << ansF.size()); j++) {
      if(__builtin_popcount(i) < 2 or __builtin_popcount(j) < 2) continue;

      int posM1 = -1, posM2 = -1;
      int posF1 = -1, posF2 = -1;

      for(int k = 0; k < ansM.size(); k++) {
        if(i & (1 << k)) {
          if(posM1 == -1) posM1 = k;
          else if(posM2 == -1) posM2 = k;
        }
      }

      for(int k = 0; k < ansF.size(); k++) {
        if(j & (1 << k)) {
          if(posF1 == -1) posF1 = k;
          else if(posF2 == -1) posF2 = k;
        }
      }

      vector<int> perm = {0, 1, 2, 3};


      do {
        ans = min(ans, ansM[posM1][perm[0]] + ansM[posM2][perm[1]] + ansF[posF1][perm[2]] + ansF[posF2][perm[3]]);
      } while (next_permutation(perm.begin(), perm.end()));

    }

  }

  cout << ans << '\n';

  return 0;
}