// OBI2021
// 19341-E
// Gabriela Barbieri Stroeh, Colégio Etapa Valinhos
// Problema: A idade de Camila
// Eu autorizo a OBI a utilizar meu código como desejar.

#include<bits/stdc++.h>

using namespace std;

int main () {
    int resp=0, x, y, z;
    scanf ("%d %d %d", &x, &y, &z);
    
    // Se x>=y e x<=z, x é o número do meio
    if (x>=y && x<=z) {
        resp=x;
    }
    
    // Se x>=z e x<=y, x é o número do meio
    if (x>=z && x<=y) {
        resp=x;
    }
    
    // Se y>=x e y<=z, y é o número do meio
    if (y>=x && y<=z) {
        resp=y;
    }
    
    // Se y>=z e y<=x, y é o número do meio
    if (y>=z && y<=x) {
        resp=y;
    }
    
    // Se z>=x e z<=y, z é o número do meio
    if (z>=x && z<=y) {
        resp=z;
    }
    
    // Se z>=y e z<=x, z é o número do meio
    if (z>=y && z<=x) {
        resp=z;
    }
    printf ("%d\n", resp);
}
