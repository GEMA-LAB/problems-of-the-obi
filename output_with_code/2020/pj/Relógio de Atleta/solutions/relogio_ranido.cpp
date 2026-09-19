// OBI2020
// relogio

#include <cstdio>


int main(void){
  int r,f,c;

  scanf("%d%d%d", &r, &f, &c);

  if (f > 3*r || c < 95)
    printf("diminuir\n");
  else if (f < 2*r && c > 97)
    printf("aumentar\n");
  else
    printf("manter\n");

  return 0;
}
