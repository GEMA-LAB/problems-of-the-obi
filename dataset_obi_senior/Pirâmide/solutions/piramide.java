// OBI2022 - Fase 2
// Tarefa Piramide
// Yan Silva

import java.util.Scanner;

public class piramide {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

        int n = in.nextInt();

        for(int i = 1 ; i <= n ; i++)
        {
            for(int j = 1 ; j <= n ; j++)
            {
                int distanciaBorda = Math.min(i, j);
                distanciaBorda = Math.min(distanciaBorda, n - i + 1);
                distanciaBorda = Math.min(distanciaBorda, n - j + 1);

                System.out.printf("%d ",distanciaBorda);
            }

            System.out.printf("\n");
        }
	}
}

