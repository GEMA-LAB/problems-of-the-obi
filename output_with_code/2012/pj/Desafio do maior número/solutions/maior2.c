#include <stdio.h>

int
main ()
{
  int num, maior;

  scanf ("%d", &num);
  maior = num;

  while (num != 0)
    {
      if (num > maior)
        maior = num;
      scanf ("%d", &num);
    }
  printf ("%d\n", maior);

  return 0;
}
