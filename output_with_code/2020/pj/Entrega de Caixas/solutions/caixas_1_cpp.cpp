// Guilherme A. Pinto, OBI 2020, caixas

#include <iostream>

using namespace std;

int A,B,C;

int main() {
  
  cin >> A >> B >> C;
  
  if ( A == B ) {
    if ( B == C ) { 
      cout << 3 << endl;
    } else {
      if ( A+B < C ) cout << 1 << endl;
      else cout << 2 << endl;
    }
  } else {
    if ( B < C ) {
      cout << 1 << endl;
    } else {
      cout << 2 << endl;
    }
  }

  return 0;
}
