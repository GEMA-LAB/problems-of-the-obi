#include <stdio.h>

int main(void)
{
	char c; int x = 0, ans = 1;
	while((c = getchar()) != EOF)
	{
		if(c == '{')
			x++;
		else if(c == '}')
			x--;
		if(x < 0)
			ans = 0;
	}
	printf("%c\n", (ans == 0 || x != 0) ? 'N' : 'S');
}