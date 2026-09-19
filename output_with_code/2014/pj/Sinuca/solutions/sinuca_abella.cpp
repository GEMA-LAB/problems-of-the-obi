#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  
  vector< vector<int> > triangle(n);

  triangle[0] = vector<int>(n);
  for (int j = 0; j < n; j++)
    cin >> triangle[0][j];

  for (int i = 1; i < n; i++) {
    triangle[i] = vector<int>(n - i);
    for (int j = 0; j < n - i; j++)
      triangle[i][j] = triangle[i-1][j] * triangle[i-1][j+1];
  }

  cout << (triangle[n-1][0] == 1 ? "preta" : "branca")  << endl;

  return 0;
}
