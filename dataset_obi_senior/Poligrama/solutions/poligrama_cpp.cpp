#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int n;
string s, a, b;

int main(void) {
  cin >> n;
  cin >> s;

  for (int k = 1; k < n; ++k) {
    if (n % k == 0) {
      a = s.substr(0, k);
      sort(a.begin(), a.end());
      bool ok = true;
      
      for (int i = k; i < n; i += k) {
	b = s.substr(i, k);
	sort(b.begin(), b.end());
	if (a != b) {
	  ok = false;
	  break;
	}
      }

      if (ok) {
	cout << s.substr(0, k) << endl;
	return 0;
      }
    }
  }
  
  cout << "*" << endl;
  
  return 0;
}

