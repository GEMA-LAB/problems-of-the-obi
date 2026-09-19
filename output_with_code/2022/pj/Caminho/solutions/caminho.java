// OBI2022 - Fase 2
// Tarefa Caminho
// Yan Silva

import java.util.Scanner;

public class caminho {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

        int n = in.nextInt();

        int[] potencias = new int[n];

        for(int i = 0 ; i < n ; i++)
            potencias[i] = in.nextInt();

        int resposta = 0;
        int tamanhoAtual = 0;

        for(int i = 0 ; i < n ; i++)
        {
            if( potencias[i%n] + potencias[(i + 1)%n] < 1000 )
                tamanhoAtual++;
            else
                tamanhoAtual = 0;

            resposta = Math.max(resposta, tamanhoAtual);
        }

        resposta = Math.min(resposta, n);

        System.out.printf("%d\n",resposta);
	}
}

