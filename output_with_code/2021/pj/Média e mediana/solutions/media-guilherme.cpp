// Guilherme A. Pinto, mean media

#include <bits/stdc++.h>
using namespace std;

int main(){
  int A, B;

  cin >> A >> B;
  cout << min(A,B)-(max(A,B)-min(A,B)) << endl;

  return 0;  
}
