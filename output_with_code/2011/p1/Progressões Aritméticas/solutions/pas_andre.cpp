#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define MAX 100005

using namespace std;

int main(){
	int N, v[MAX];

	//Faz a leitura da entrada
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf ("%d", &v[i]);

	//Inicializa as variaveis
	int resp = 0;
	int b = 0;

	//Loop principal pra resolver o problema
	for (int i = 1; i < N; i++){
		//Se a razao nao eh igual a razao entre os dois primeiros termos 
		//da PA atual devemos comecar uma nova PA e indicar isso
		if (v[i] - v[i-1] != v[b+1] - v[b]){
			//b indica a posicao em que comeca a PA
			b = i;

			resp++;
			//i eh incrementado porque quaisquer dois elementos formam 
			//uma PA e nao precisamos comparar b+1 com b
			i++;
		}
	}
        resp++;

	printf("%d\n", resp);
	return 0;
}
