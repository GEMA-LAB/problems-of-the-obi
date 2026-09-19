// Guilherme A. Pinto, OBI-2015, codigo

#include <iostream>

#define MAX 10000

using namespace std;

int seq[MAX];

int main(){
  int N;
  
  cin >> N;
  for( int i = 0; i < N; i++ ) cin >> seq[i];

  int res = 0;
  for( int k = 2; k < N; k++ )
    if ( seq[k-2] == 1 && seq[k-1] == 0 && seq[k] == 0 )
      res++;

  cout << res << endl;

  return 0;
}
