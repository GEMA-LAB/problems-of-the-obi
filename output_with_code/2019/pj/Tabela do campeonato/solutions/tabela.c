// Problema tabela
// OBI2019 - Fase 2

#include <stdio.h>

int main()
{
  int n, i;
  int njogos, npontos, nvit, nemp, nderr;
  int nvit1, nvit2, nemp1, nemp2;
  int tnjogos, tnderr, tnpontos;

  scanf("%d%d%d%d%d",&njogos,&npontos,&nvit,&nemp,&nderr);
  if (nvit != -1) 
    nvit1 = nvit2 = nvit;
  else {
    nvit1 = 0;
    nvit2 = 100;
  }
  
  if (nemp != -1) 
    nemp1 = nemp2 = nemp;
  else {
    nemp1 = 0;
    nemp2 = 100;
  }
  if (njogos == -1 && nderr == -1) nderr = 0;
  
  for (nvit=nvit1; nvit<=nvit2; ++nvit)
    for (nemp=nemp1; nemp<=nemp2; ++nemp) {
      tnjogos=njogos; 
      tnderr=nderr; 
      tnpontos=npontos;
      if (njogos == -1) tnjogos = nvit+nemp+nderr;
      else if (nderr == -1) tnderr = njogos-nvit-nemp;
      
      if (npontos == -1) tnpontos = 3*nvit+nemp;
      
      if (tnjogos == nvit+nemp+tnderr &&
	   tnjogos >= 0 && tnjogos <= 100 &&
	   tnderr >= 0 && tnderr <= 100 &&
	   tnpontos==3*nvit+nemp) {
	// encontramos solução, imprime resultado
	printf("%d %d %d %d %d\n", tnjogos, tnpontos, nvit, nemp, tnderr);
      }
    }
  
  return 0;
}
