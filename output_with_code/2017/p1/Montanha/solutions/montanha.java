// r. anido
// problema montanha, OBI2017

import java.util.Scanner;

public class montanha {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in); 
        int n;
        int a[];                 // vamos usar um vetor para facilitar, mas apenas porque 
                                 // o enunciado diz que a sequência tem poucos elementos (no máximo 1000)
                                 // se o vetor fosse muito grande, a melhor solução seria usar apenas três variáveis
                                 // para percorrer a sequência de valores.

        n=in.nextInt();                        // lê valor de N
        a= new int[n];
        for (int i=0; i<n; i++)
            a[i]=in.nextInt();                 // lê os valores da sequência e armazena no vetor

        for (int i=2; i<n; i++) {              // agora percorre o vetor, verificando a condição de dois picos
            if (a[i-2]>a[i-1] && a[i]>a[i-1]) {
                System.out.println("S");       // montanha tem dois picos, nem precisa verificar o restante da sequência
                return;
            }
        }
        System.out.println("N");                // se chegou aqui, montanha tem um pico
    }
}
