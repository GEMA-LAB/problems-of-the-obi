#include <bits/stdc++.h>
using namespace std;

int main() {
  int k, n;
  string alphabet, message;

  cin >> k >> n;

  cin >> alphabet;
  set<char> alphabet_set(alphabet.begin(), alphabet.end());

  cin >> message;
  for (char c : message) {
    if (!alphabet_set.count(c)) {
      cout << "N" << endl;
      return 0;
    }
  }

  cout << "S" << endl;
  return 0;
}
