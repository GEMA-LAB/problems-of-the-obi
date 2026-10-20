// OBI2022 - Fase 2
// Tarefa Piramide
// Yan Silva

#include <iostream>

using namespace std;

const int MAXN = 110;

int n;

int piramide[MAXN][MAXN];

int main()
{
    int n;
    cin >> n;

    for(int nivel = 1 ; nivel <= (n + 1)/2 ; nivel++)
        for(int i = nivel ; i <= n - nivel + 1 ; i++)
            for(int j = nivel ; j <= n - nivel + 1 ; j++)
                piramide[i][j]++;

    for(int i = 1 ; i <= n ; i++)
    {
        for(int j = 1 ; j <= n ; j++)
            printf("%d ",piramide[i][j]);

        printf("\n");
    }
}