// OBI2021 - Fase3
// Sr. Sapo

#include <bits/stdc++.h>

using namespace std;

int L, C, P;
queue<pair<int,int>> q;

int main(void){
  scanf("%d%d", &C, &L);
  int lago[C+1][L+1], visitado[C+1][L+1];

  memset(lago, 0, sizeof(lago));
  memset(visitado, 0, sizeof(visitado));
  
  scanf("%d", &P);

  for (int i = 0; i < P; i++) {
    int col, lin;
    scanf("%d%d", &col, &lin);
    lago[col][lin] = 1;
  }
  
  int c_ini, l_ini, c_dest, l_dest;
  scanf("%d%d", &c_ini, &l_ini);
  scanf("%d%d", &c_dest, &l_dest);

  // BFS
  q.push( {c_ini,l_ini} );

  char resp = 'N';
  while ( not q.empty() ) {
    auto l = q.front(); q.pop();
    int i = l.first;
    int j = l.second;

    if (i == c_dest && j == l_dest) {
      resp = 'S';
      break;
    }

    if (!visitado[i][j]) {
      visitado[i][j] = true;

      // possiveis pulos
      int a, b;
      for (int dist = 1; dist <= 3; dist++) {
	a = i + dist; b = j;
	if ( a <= C && lago[a][b] == 1 && !visitado[a][b] )
	  q.push( {a,b} );
	a = i - dist; b = j;
	if ( a > 0 && lago[a][b] == 1 && !visitado[a][b] )
	  q.push( {a,b} );
	a = i; b = j + dist;
	if ( b <= L && lago[a][b] == 1 && !visitado[a][b] )
	  q.push( {a,b} );
	a = i; b = j - dist;
	if ( b > 0 && lago[a][b] == 1 && !visitado[a][b] )
	  q.push( {a,b} );
      }
    }
  }
  printf("%c\n", resp);
  return 0;
}
