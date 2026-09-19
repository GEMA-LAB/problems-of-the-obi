#include <bits/stdc++.h>
using namespace std;

const int MAX_A = 100000;
int freq[MAX_A + 1];

int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    int alt;
    cin >> alt;
    freq[alt]++;
  }

  int resp = 0;
  for (int i = 1; i <= MAX_A; i++) {
    resp += freq[i] / 2;
  }
  
  cout << resp << endl;
  return 0;
}
