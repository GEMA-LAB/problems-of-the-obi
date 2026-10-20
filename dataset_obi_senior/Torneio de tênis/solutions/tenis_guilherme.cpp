#include <bits/stdc++.h>

#define MAX 10000

using namespace std;

int main(){
  int A,B,C,D;

  cin >> A >> B >> C >> D;
  
  int res = 2*MAX;
  
  res = min( res, abs((A+B)-(C+D)) );
  res = min( res, abs((A+C)-(B+D)) );
  res = min( res, abs((A+D)-(B+C)) );
  
  cout << res << endl;
  
  return 0;
}
