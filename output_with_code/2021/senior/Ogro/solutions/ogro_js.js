// OBI2021
// Fase 3
// Ogro

var n;

scanf("%d", "n");

// mão esquerda
if (n >= 5)
   for (var i=0; i<5; i++)
      printf("I");
else if (n > 0)
   for (var i=0; i<n; i++)
      printf("I");
else
   printf("*");
printf("\n");

n -= 5;

// mão direita
if (n > 0)
   for (var i=0; i<n; i++)
      printf("I");
else
   printf("*");
printf("\n");
