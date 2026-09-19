// Guilherme A. Pinto, OBI 2020, caixas

#include <iostream>

using namespace std;

int A,B,C;

int main() {
  
  cin >> A >> B >> C;

  if ( A == B and B == C ) {
    cout << 3 << endl;
    return 0;
  }

  if ( A < B and B < C ) {
    cout << 1 << endl;
    return 0;
  }

  if ( A == B and A+B < C ) {
    cout << 1 << endl;
    return 0;
  }

  cout << 2 << endl;
  return 0;
}
