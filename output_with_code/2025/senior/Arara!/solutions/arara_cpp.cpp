/*
    OBI 2025 - Fase 2
    Araras
*/

#include<bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int araras, gaiolas;
    cin >> araras >> gaiolas;
    int qtd = (gaiolas+4)/5;
    if(qtd >= araras)
        cout << "S\n";
    else
        cout << "N\n";
    return 0;
}