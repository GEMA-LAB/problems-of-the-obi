#include <stdio.h>

char resolve(int a, int b, int c)
{
  int x;
  if(a < b){
    x = a; a = b; b = x;
  }
  if(a < c){
    x = a; a = c; c = x;
  }

  if(a >= b + c)
    return 'n';
  if(a*a < b*b + c*c)
    return 'a';
  if(a*a > b*b + c*c)
    return 'o';
  return 'r';
}

int main()
{
  int a, b, c;
  scanf(" %d %d %d", &a, &b, &c);
  printf("%c\n", resolve(a, b, c));
  return 0;
}
