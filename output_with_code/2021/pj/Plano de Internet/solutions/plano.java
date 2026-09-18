import java.util.Scanner;


public class plano {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
	int x = input.nextInt();
        int n = input.nextInt();

        int soma = 0;
        for (int i=0; i<n; i++){
            soma += input.nextInt();
        }
	System.out.println(x*(n+1) - soma);
    }
}
