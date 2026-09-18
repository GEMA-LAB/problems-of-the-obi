// OBI2020
// emoticons
import java.util.Scanner;

public class solucao {
    public static final String divertido = ":-)";
    public static final String chateado = ":-(";
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	String str1 = in.nextLine();
	String str2 = str1;
	int i, num_chateado = 0, num_divertido = 0;

	i = str1.indexOf(divertido);
	while (i != -1) {
	    num_divertido++;
	    str1 = str1.substring(i+3);
	    i = str1.indexOf(divertido);
	}   
	i = str2.indexOf(chateado);
	while (i != -1) {
	    num_chateado++;
	    str2 = str2.substring(i+3);
	    i = str2.indexOf(chateado);
	}
	if (num_divertido > num_chateado)
	    System.out.println("divertido");
	else if (num_divertido < num_chateado)
	    System.out.println("chateado");
	else
	    System.out.println("neutro");
    }
}
