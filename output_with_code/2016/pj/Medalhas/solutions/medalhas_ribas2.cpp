#include <stdio.h>
#include <algorithm>

using namespace std;

int main(void)
{
  pair<int,int> tempos[3];
  for(int i=0;i<3;i++)
  {
    scanf("%d",&tempos[i].first);
    tempos[i].second=i+1;
  }

  /* PJ ordenacao N^2 vale, i'm sorry */
  for(int i=0;i<3;i++)
    for(int j=i+1;j<3;j++)
      if(tempos[j].first < tempos[i].first)
      {
        pair<int,int> aux;
        aux=tempos[i];
        tempos[i]=tempos[j];
        tempos[j]=aux;
      }

  for(int i=0;i<3;i++)
    printf("%d\n",tempos[i].second);

}
