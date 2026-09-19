#include <iostream>
using namespace std;

#define MAXN 100001

int p[10][MAXN];  // prefix sum for each 0..9
int c[10] = {0};

int main(){
  int N,M,cur,next,i,k,first,num;
  
  cin >> N >> M;

  for ( k = 0; k < 10; k++ ) p[k][0] = 0;
  for ( i = 1; i <= N; i++ ){
    for ( k = 0; k < 10; k++ ) p[k][i] = p[k][i-1];
    cin >> num;
    p[num][i]++;
    if ( i == 1 ) first = num;
  }

  cin >> cur;
  c[first]++;
  while( M-- > 1 ){
    cin >> next;
    for ( k = 0; k < 10; k++ )
      if ( next > cur ) c[k] += p[k][next]-p[k][cur];
      else c[k] += p[k][cur-1]-p[k][next-1];
    cur = next;
  }

  for ( int i = 0; i < 10; i++ ){
    if ( i > 0 ) cout << " ";
    cout << c[i];
  }
  cout << endl;
  
  return 0;
}
