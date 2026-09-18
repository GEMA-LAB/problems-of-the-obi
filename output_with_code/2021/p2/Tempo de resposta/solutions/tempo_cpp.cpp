/********************************************************\
 * Pedro Suyama Leston Rey                              *
 * Colégio Etapa - P2                                   *
 *                                                      *
 * Eu autorizo a OBI a utilizar meu código como desejar.*
\********************************************************/

#include <bits/stdc++.h>

using namespace std;

const int MAXX = 110;

//lst[x] = ultimo momento em que recebi uma mensagem da pessoa x
int lst[MAXX];
//total[x] = tempo de resposta total atual da pessoa x
int total[MAXX];
//waiting[x] = true se, e só se, ainda não respondi a pessoa x 
bool waiting[MAXX];
//exist[x] = true se, e só se, existe alguma pessoa com o id x
bool exist[MAXX];

int main() {
	//Lê o número de registros
	int n;
	scanf("%d", &n);

	//tmp é o horário atual, e t é true se, e só se, o registro anterior é do tipo 'T'
	int tmp = 0; bool t = false;
	for (int qq = 0; qq < n; ++qq) {
		//Lê um registro
		char c; int x;
		scanf(" %c%d", &c, &x);

		//Se o anterior não é um registro 'T' e o atual não é um registro 'T',
		//significa que se passou 1 segundo.
		if (!t && c != 'T') ++tmp;

		//Se c == 'T', então precisamops aumentar o horário atual.
		if (c == 'T') {
			tmp += x;
			t = true;
			continue;
		}
		//Se c == 'R' a pessoa x está aguardando pela resposta, 
		//a ultima vez que ela enviou uma mensagem agora é tmp e
		//ela, obviamente existe.
		if (c == 'R') {
			waiting[x] = true;
			lst[x] = tmp;
			exist[x] = true;
		}
		//Se c == 'E', a pessoa x não está mais aguardando resposta,
		//e podemos incrementar seu tempo total de espera.
		else {
			waiting[x] = false;
			total[x] += tmp - lst[x];
		}
		//O atual vai se tornar o anterior na próxima iteração, 
		//e como não é um registro do tipo 'T', a flag t será falsa.
		t = false;
	}

	//Vamos iterar por todos os possiveis ids. Seja i um id,
	//se ele existe e não esta esperando por uma resposta,
	//o tempo de resposta total está armazenado no vetor total.
	//Caso contrário, o tempo de resposta total é -1.
	//Note que isso vai imprimir os resultados em ordem crescente de ids
	for (int i = 0; i <= 100; ++i)
		if (exist[i] && !waiting[i]) printf("%d %d\n", i, total[i]);
		else if (exist[i]) printf("%d -1\n", i);
}