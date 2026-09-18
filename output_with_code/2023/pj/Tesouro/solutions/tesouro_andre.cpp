#include <cstdio>
using namespace std;
const int MAXM = 1010;
char mapa[MAXM][MAXM];
int marc[MAXM][MAXM];
int main() {
  int m;
  scanf("%d", &m);
  for(int i = 1; i <= m; i++)
    for(int j = 1; j <= m; j++)
      scanf(" %c", &mapa[i][j]);
  int l, c;
  scanf("%d %d", &l, &c);
  int resp = -1;
  while(true) {
    if(l < 1 || l > m || c < 1 || c > m) {
      resp = -1;
      break;
    }
    
    if(marc[l][c] == 1) {
      resp = 0;
      break;
    }
  
    marc[l][c] = 1;
    resp++;
    
    if(mapa[l][c] == 'X') break;
    
    if(mapa[l][c] == 'N') l--;
    else if(mapa[l][c] == 'S') l++;
    else if(mapa[l][c] == 'O') c--;
    else c++;
  }
  
  printf("%d\n", resp);
}