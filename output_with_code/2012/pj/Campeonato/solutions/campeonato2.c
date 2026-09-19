#include <stdio.h>

int Vc, Ec, Sc;
int Vf, Ef, Sf;

int cmp() {
	int Pc = 3 * Vc + Ec;
	int Pf = 3 * Vf + Ef;
	if (Pc != Pf) return (Pc > Pf) - (Pc < Pf);
	return (Sc > Sf) - (Sc < Sf);
}

int main() {
	scanf("%d %d %d", &Vc, &Ec, &Sc);
	scanf("%d %d %d", &Vf, &Ef, &Sf);
	switch (cmp()) {
		case -1:
			puts("F");
			break;
		case 0:
			puts("=");
			break;
		case +1:
			puts("C");
			break;
	};
	return 0;
}
