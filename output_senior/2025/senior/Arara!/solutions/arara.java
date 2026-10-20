import java.util.Scanner;
public class arara {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int araras = in.nextInt();
		int gaiolas = in.nextInt();
		int qtd = (gaiolas + 4)/5;
		if(qtd >= araras) System.out.println("S");
		else System.out.println("N");
	}
}