#include <stdio.h>
#include <algorithm>

using namespace std;

int main(void)
{
  pair<int,int> pa,pb,pc;
  scanf("%d %d %d %d",&pa.first,&pb.first,&pc.first);
  pa.second=1;
  pb.second=2;
  pc.second=3;

  pair<int,int> aux;
  if(pa > pb)
    aux=pa,pa=pb,pb=aux;

  if(pb > pc)
    aux=pb,pb=pc,pc=aux;

  if(pa > pb)
    aux=pa,pa=pb,pb=aux;

  printf("%d\n%d\n%d\n",pa.second,pb.second,pc.second);
}
