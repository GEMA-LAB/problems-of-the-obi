// OBI2022
// Tarefa magico

#include<bits/stdc++.h>

using namespace std;

int n;
int ii, jj;

int main (void) {
    scanf("%d", &n);
    int magico[n][n];

    for (int i=0; i<n; i++) {
      for (int j=0; j<n; j++ ) {
        scanf("%d", &magico[i][j]);
        if (magico[i][j] == 0) {
	  ii = i;
	  jj = j;
        }
      }
    }
    
    // soma correta
    int soma = 0;
    for (int i=0; i<n; i++) {
      if (i == ii) continue;
      for (int j=0; j<n; j++ ) {
        soma += magico[i][j];
      }
      break;
    }

    // soma sem o número ilegível
    int s = 0;
    for (int j=0; j<n; j++ ) {
      s += magico[ii][j]; 
    }

    // imprime a resposta
    printf("%d\n", soma - s);
    printf("%d\n", ii+1);
    printf("%d\n", jj+1);
    
    return 0;
}
