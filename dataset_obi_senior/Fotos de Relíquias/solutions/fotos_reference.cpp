#include <iostream>
using namespace std;

const int MAXN = 1e5;
int arr[MAXN + 5];

int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++)
    cin >> arr[i];

  int prev = -1, ptr = 0;
  while (ptr < n && arr[ptr] == 0)
    ptr++;

  long long ans = 0;
  while (ptr < n) {
    int curr = ptr;
    ptr++;

    while (ptr < n && arr[ptr] == 0)
      ptr++;

    ans += (long long)(curr - prev) * (long long)(ptr - curr);
    prev = curr;
  }

  cout << ans << "\n";
}
