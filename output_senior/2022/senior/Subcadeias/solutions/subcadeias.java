// OBI2022 - Fase 2
// Tarefa Subcadeias
// Yan Silva

import java.util.Scanner;

public class subcadeias {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

        int n = in.nextInt();
        String s = in.next();

        int resposta = 0;

        for(int l = 0 ; l < n ; l++)
        {
            for(int r = l ; r < n ; r++)
            {
                boolean ehPalindromo = true;

                for(int pl = l, pr = r ; pl <= pr ; pl++, pr--)
                    if( s.charAt(pl) != s.charAt(pr) ) ehPalindromo = false;

                if( ehPalindromo )
                    resposta = Math.max(resposta, r - l + 1);
            }
        }

        System.out.printf("%d\n",resposta);
	}
}

