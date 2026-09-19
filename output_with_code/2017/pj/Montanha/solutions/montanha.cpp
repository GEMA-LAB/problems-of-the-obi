// Guilherme A. Pinto, OBI-2017, montanha

#include <iostream>

#define MAX 1001

using namespace std;

int A[MAX];

int main(){
  int N;
  
  cin >> N;
  for ( int i = 1; i <= N; i++ )
    cin >> A[i];

  char resposta = 'N';
  
  for ( int i = 2; i <= N-1; i++ )
    if ( A[i-1] > A[i] && A[i] < A[i+1] )
      resposta = 'S';

  cout << resposta << endl;
  
  return 0;
}
