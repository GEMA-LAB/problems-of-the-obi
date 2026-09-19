#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
    int N,K;
    vector<string> lista;

    scanf("%d %d",&N,&K);
    for(int i = 0; i < N; i++)
    {
        char s[32];
        scanf("%s",s);
        lista.push_back(string(s));
    }
    sort(lista.begin(),lista.end());
    printf("%s\n",lista[K-1].c_str());

    return(0);
}

