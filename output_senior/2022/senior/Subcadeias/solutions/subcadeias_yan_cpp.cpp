// OBI2022 - Fase 2
// Tarefa Subcadeias
// Yan Silva

#include <iostream>

using namespace std;

int n;

string s;

int main()
{   
    cin >> n >> s;

    int resposta = 0;

    for(int l = 0 ; l < n ; l++)
    {
        for(int r = l ; r < n ; r++)
        {
            bool ehPalindromo = true;

            for(int pl = l, pr = r ; pl <= pr ; pl++, pr--)
                if( s[pl] != s[pr] ) ehPalindromo = false;

            if( ehPalindromo )
                resposta = max(resposta, r - l + 1);
        }
    }

    cout << resposta << endl;
}