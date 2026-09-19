#include <stdio.h>

int
main ()
{
  int num, maior = -1;

  for (scanf ("%d", &num); num != 0; scanf ("%d", &num))
    {
      if (num > maior)
        maior = num;
    }
  printf ("%d\n", maior);
  return 0;
}
