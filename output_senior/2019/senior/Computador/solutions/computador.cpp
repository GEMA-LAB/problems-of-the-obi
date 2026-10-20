// Guilherme A. Pinto, seletiva 2018-2019, computador, O(M\log N) 

#include <iostream>

using namespace std;

//#define MAXN 100001
//#define MAX 131072 // 2^17 > MAXN
#define MAXN 200001
#define MAX 262144 // 2^18 > MAXN

#define MEIO(i,f) ((i)+(((f)-(i)+1)/2)-1)
#define ESQ(i) (2*(i))
#define DIR(i) (2*(i)+1)

typedef long long i64;

struct segment {
  i64 F,T,Fcnt,Tcnt;
  int i, f;
};

segment t[2*MAX+1]; // segment tree
int N,M;

void init( int k, int i, int f ){
  t[k].i = i; t[k].f = f;
  t[k].F = t[k].T = 0LL;
  t[k].Fcnt = t[k].Tcnt = 0LL;
  if ( i > N ) return;
  if ( i != f ){
    init( ESQ(k), i, MEIO(i,f) );
    init( DIR(k), MEIO(i,f)+1, f );
  }
}

// range update
void update( int k, i64 v, bool dir_frente, int l, int r ){

  // estritamente fora, sem recursao
  if ( t[k].i > r or t[k].f < l ) return;

  // estritamento dentro, sem recursao
  if ( t[k].i >= l and t[k].f <= r ){
    if ( dir_frente ){
      t[k].F += v-(i64)(t[k].i-l);
      t[k].Fcnt++;
    } else {
      t[k].T += v-(i64)(r-t[k].f);
      t[k].Tcnt++;
    }
    return;
  }

  // recursao, nem dentro, nem fora
  update( ESQ(k), v, dir_frente, l, r );
  update( DIR(k), v, dir_frente, l, r );
}

// point query
i64 query( int k, int p ){
  
  // calcula a contribuicao do segmento k
  i64 aux = t[k].F-(((i64)(p-t[k].i))*t[k].Fcnt) +
            t[k].T-(((i64)(t[k].f-p))*t[k].Tcnt);
  
  if ( t[k].i == t[k].f ) // t[k].i == p, sem recursao
    return aux;
  else
    if ( p <= t[ESQ(k)].f ) // ESQ
      return aux + query( ESQ(k), p );
    else // DIR
      return aux + query( DIR(k), p );
}

int main(){
  int o,i,v;

  scanf("%d %d", &N, &M);

  int pw = 1; while( pw < N ) pw *= 2;

  // inicializa segtree
  init( 1, 1, pw );
  /////////////////////
  
  while ( M-- > 0 ){
    scanf("%d",&o);
    switch( o ){
    case 3:
      scanf("%d",&i);
      printf( "%lld\n", query( 1, i ) );
      break;
    case 1:
      scanf("%d %d", &i, &v);
      update( 1, (i64)v, true, i, min(i+v-1,N) );
      break;
    case 2:
      scanf("%d %d", &i, &v);
      update( 1, (i64)v, false, max(i-v+1,0), i );
    }
  }

  return 0;
}
