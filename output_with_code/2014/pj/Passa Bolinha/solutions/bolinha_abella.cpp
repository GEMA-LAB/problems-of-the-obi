#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int result;
vector< vector<int> > val;
vector< vector<bool> > mark;

int dy[] = {0, 1, 0, -1};
int dx[] = {1, 0, -1, 0};

void dfs(int y, int x, int n) {
  result++;
  mark[y][x] = true;

  for (int d = 0; d < 4; d++) {
    int y2 = y + dy[d], x2 = x + dx[d];
    if (0 <= min(y2, x2) && max(y2, x2) < n && !mark[y2][x2] && val[y2][x2] >= val[y][x])
      dfs(y2, x2, n);
  }
}

int main() {
  int n;
  cin >> n;
  int sy, sx;
  cin >> sy >> sx; sy--, sx--;

  val = vector< vector<int> >(n, vector<int>(n));
  
  for (int y = 0; y < n; y++)
    for (int x = 0; x < n; x++)
      cin >> val[y][x];

  mark = vector< vector<bool> >(n, vector<bool>(n, false));

  result = 0;
  dfs(sy, sx, n);

  cout << result << endl;

  return 0;
}
