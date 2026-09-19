// OBI2020
// tesouro

import java.util.Scanner;

public class solucao {
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	int moedas = in.nextInt();
	int marinheiros = in.nextInt();
	int parte, capitao;

	capitao = 2;
	parte = moedas/(marinheiros+capitao);
	System.out.println(2*parte);
    }
}
