#include <bits/stdc++.h>
using namespace std;
 
int main() {
  int n;
  cin >> n;
  int resp = 0;
  while (n > 0) {
    int x = n;
    int max_digit = 0;
    while (x > 0) {
      int digit = x % 10;
      max_digit = max(max_digit, digit);
      x /= 10;
    }
    n -= max_digit;
    resp++;
  }
  cout << resp << endl;
  return 0;
}
