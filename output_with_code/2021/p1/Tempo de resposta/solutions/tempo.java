// OBI2021
// Tarefa Tempo de Resposta
// 07149-J
// Paulo Davi de Oliveira Pires

import java.util.Scanner;

public class tempo {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        
        int N = in.nextInt();
        int [] amigos = new int[101];
        int [] amigosRespondidos = new int [101];
        int [] tempoDoAmigo = new int [101];
        int [] ultimoTempoDoAmigo = new int[101];
        
        int tempo = 0;
        
        for (int i = 0; i < N; i++) {
	    char evento = in.next().charAt(0);
	    int val = in.nextInt();
	    if (evento == 'T') {
		tempo += val - 1;
	    } else if (evento == 'R') {
		amigos[val] = 1;
		tempo += 1;
		ultimoTempoDoAmigo[val] = tempo;
		amigosRespondidos[val] = 1;
	    } else if (evento == 'E') {
		amigosRespondidos[val] = 0;
		tempo += 1;
		tempoDoAmigo[val] += tempo - ultimoTempoDoAmigo[val];     		
	    }
        }
        
        for (int i = 1; i < 101; i++) {
	    if (amigos[i] == 1) {
		if (amigosRespondidos[i] == 0) {
		    System.out.println(i + " " + tempoDoAmigo[i]);
		} else {
		    System.out.println(i + " " + -1);
		}
	    }
        }
    }
}
