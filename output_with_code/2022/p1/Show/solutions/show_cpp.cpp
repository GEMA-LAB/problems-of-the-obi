// OBI2022
// Tarefa Show

#include<bits/stdc++.h>

using namespace std;

int a, n, m;

int main (void) {
    int melhor_fila = 1000;
    int x, seguidas;

    scanf ("%d%d%d", &a, &n, &m);

    for (int i=0; i<n; i++) {
      seguidas = 0;
      for (int j=0; j<m; j++) {
	scanf ("%d", &x);
	if (x == 0)
	  seguidas++;
	else
	  seguidas = 0;
	if (seguidas == a)
	  melhor_fila = n - i;
      }
    }

    if (melhor_fila == 1000)
      melhor_fila = -1;
    printf("%d\n", melhor_fila);
  
    return 0;
}
