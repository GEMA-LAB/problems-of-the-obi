// OBI2022 - Fase 2
// Tarefa Troféu
// Yan Silva

import java.util.Scanner;

public class trofeu {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

        int[] pontuacoes = new int[5];

        for(int i = 0; i < 5; i++)
            pontuacoes[i] = in.nextInt();

        int maximo = 0, segundoMaximo = 0;

        for(int i = 0; i < 5; i++)
        {
            if( maximo < pontuacoes[i] )
            {
                segundoMaximo = maximo;
                maximo = pontuacoes[i];
            }
            else if( segundoMaximo < pontuacoes[i] && pontuacoes[i] != maximo )
                segundoMaximo = pontuacoes[i];
        }

		int qtdMaximo = 0, qtdSegundoMaximo = 0;

        for(int i = 0; i < 5; i++)
        {
            if( pontuacoes[i] == maximo )
                qtdMaximo++;
            
            if( pontuacoes[i] == segundoMaximo )
                qtdSegundoMaximo++;
        }

        System.out.printf("%d %d\n",qtdMaximo,qtdSegundoMaximo);
	}
}

