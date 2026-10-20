#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 510;

int n, m, k, x, tmp=0;

char s[MAXN];
char palavras[MAXN][MAXN];

int pos[MAXN];

int main()
{
  scanf("%d %d %d", &n, &m, &k);
  scanf("%s", s);
  for(int i = 0; i < n; i++)
    if(s[i] == '#')
      pos[tmp++] = i;
  for(int i = 0; i < m; i++)
    scanf("%s", palavras[i]);
  scanf("%d", &x);
  // se usar sub tarefa m==1, k==3
  // if(m == 1 && k == 3)
  // {
  //   char alvo = 'a';
  //   for(int a = 0; a < 3; a++)
  //     for(int b = 0; b < 3; b++)
  //       for(int c = 0; c < 3; c++)
  //       {
  //         if(a == b || a == c || b == c) continue;
  //         if(palavras[0][a] < palavras[0][b] && palavras[0][b] < palavras[0][c])
  //         {
  //           if(x == 1) alvo = palavras[0][a];
  //           if(x == 2) alvo = palavras[0][b];
  //           if(x == 3) alvo = palavras[0][c];
  //         }
  //       }
  //   s[pos[0]] = alvo;
  //   printf("%s\n", s);
  // } 
  // else if(m == 1)
  if (m == 1) {
    sort(palavras[0], palavras[0] + k);
    s[pos[0]] = palavras[0][x - 1];
    printf("%s\n", s);
  }
  else {
    x--;
    for (int i = 0; i < m; i++)
      sort(palavras[i], palavras[i] + k);
    for (int i = 0; i < m; i++)
      s[pos[i]] = palavras[i][0];
    for (int i = m - 1; i >= 0; i--)
    {
      if (x == 0) break;
      tmp = x % k;
      s[pos[i]] = palavras[i][tmp];
      x /= k;
    }
    printf("%s\n", s);
  }
  return 0;
}
