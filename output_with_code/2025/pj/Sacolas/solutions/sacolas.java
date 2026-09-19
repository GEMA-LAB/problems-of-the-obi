import java.util.Scanner;
public class sacolas {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int s = in.nextInt();
		int resp = 1;
		int soma = 0;
		for(int i = 1; i <= n; i++) {
		    int p = in.nextInt();
			if(soma + p > s) {
                resp++;
                soma = p;
            } else {
                soma += p;
            }
		}
		System.out.print(resp);
	}
}