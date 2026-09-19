#include <stdio.h>

#define MAX 300001
#define MAXL ((int)('Z'-'A'+2))
#define INF 0x3f3f3f3f

char s[MAX];
int tamanho[MAX];
int maior;

void acha(char c)
{
    int i;
    int maior = 0;
    for (i= c - 'A'+1; i>=0; i--)
    {
        if (tamanho[i] > maior)
            maior = tamanho[i];
    }
    
    tamanho[c - 'A' + 1] = maior + 1;
    
}

int main()
{
    int i;
    int pos;
    int maior = 0;
    
    scanf("%s", s);
    
    
    for (i=1; i < MAXL; i++)
        tamanho[i] = -INF;
    
    tamanho[0] =  0;
    
    for (i=0; s[i]; i++)
    {
        acha(s[i]);
    }
    
    for (i=0; i<MAXL; i++)
        if (tamanho[i] > maior)
            maior = tamanho[i];
    printf("%d\n", maior);
    
    return 0;
}
