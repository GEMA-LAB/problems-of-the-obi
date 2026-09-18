// OBI-2020, escher, Guilherme A. Pinto

#include <iostream>

#define MAX 10001

using namespace std;

int A[MAX];

int main(){
  int N;

  cin >> N;
  for( int i = 1; i <= N; i++ )
    cin >> A[i];

  bool escher = true;
  int H = A[1]+A[N];

  for( int i = 1; i <= N; i++ )
    if ( A[i]+A[N-i+1] != H )
      escher = false;

  if ( escher ) cout << "S" << endl;
  else cout << "N" << endl;

  return 0;
}