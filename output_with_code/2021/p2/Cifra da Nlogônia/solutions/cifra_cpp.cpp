/********************************************************\
 * Pedro Suyama Leston Rey                              *
 * Colégio Etapa - P2                                   *
 *                                                      *
 * Eu autorizo a OBI a utilizar meu código como desejar.*
\********************************************************/

#include <bits/stdc++.h>

using namespace std;

int main() {
	set<char> vogais{'a', 'e', 'i', 'o', 'u'};
	//lê a string
	string s;
	cin >> s;

	for (char c: s) {
		//Independente do caracter sua cifra comecará com o
		//prórpio caracter
		printf("%c", c);

		//podemos ignorar o resto se for uma vogal
		if (vogais.count(c)) continue;
		//Agora, c é uma consoante.
		//Vamos iterar pelas vogais e escolher a mais próxima de c.
		//Note que a mais próxima do início do alfabeto será processada primeiro
		//e se existe outra vogal com a mesma distância, ela será ignorada.
		char v = 'a';
		for (int i: vogais)
			if (abs(i - c) < abs(v - c)) v = i;
		//imprime o segundo caracter da cifra
		printf("%c", v);

		//Temos que tomar cuidado pois o alfabeto dado não tem as
		//letras w e y.
		if (c == 'z') printf("z");
		else if (c == 'v') printf("x");
		else if (c == 'x') printf("z");
		//se a próxima letra é uma vogal, imprimimos c+2
		else if (vogais.count(c+1)) printf("%c", c+2);
		//caso contrário ela é uma consoante, imprimimos c+1
		else printf("%c", c+1);

		//Nota: Cada caracter é um número positivo na tabela ASCII
		//      somar um a um caracter o leva para o próximo na
		//      tabela ASCII
	}
	printf("\n");
}