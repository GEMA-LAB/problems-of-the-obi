#include <stdio.h>

int main()
{
    int i, j, v[3], w[3], t;
    
    for (i=0; i<3; i++)
    {
        w[i] = i+1;
        scanf("%d", &v[i]);
    }
    
    for (i=2; i>0; i--)
    {
        for (j=0; j<i; j++)
        {
            if (v[j] > v[j+1])
            {
                t = v[j];
                v[j] = v[j+1];
                v[j+1] = t;
                t = w[j];
                w[j] = w[j+1];
                w[j+1] = t;
            }
        }
    }
    
    for (i=0; i<3; i++)
        printf("%d\n", w[i]);
    return 0;
}