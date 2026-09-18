// OBI2022
// Tarefa Hotel

#include<bits/stdc++.h>

using namespace std;

int d, a, n;

int main (void) {
    scanf ("%d%d%d", &d, &a, &n);

    //vamos usar chegada para calcular o valor da diária
    int chegada = n;

    if (chegada > 15)
      chegada = 15;

    int diaria = d + (chegada-1)*a;

    printf("%d\n",(31 - n + 1)*diaria);

    return 0;
}
