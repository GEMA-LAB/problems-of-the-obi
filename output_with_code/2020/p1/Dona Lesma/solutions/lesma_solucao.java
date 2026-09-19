// OBI2020 - Fase 2
// dona lesma

import java.util.Scanner;

public class solucao {
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	int altura = in.nextInt();
	int sobe = in.nextInt();
	int desce = in.nextInt();
	int distancia = 0;
	int dias = 0;

	while (true) {
	    dias = dias + 1;
	    distancia = distancia + sobe;
	    if (distancia >= altura)
		break;
	    distancia = distancia - desce;
	}
	System.out.println(dias);
    }
}
