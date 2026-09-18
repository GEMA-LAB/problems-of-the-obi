// OBI2021 - Fase 2
// Pesquisa de preços

import java.util.Scanner;

public class pesquisa {

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);


    int n;
    String estado;
    float alcool, gasolina;
    boolean existe = false;

    n = in.nextInt();

    for (int i=0; i<n; i++) {
	estado = in.next();
	alcool = in.nextFloat();
	gasolina = in.nextFloat();
	if (alcool/gasolina <= 0.70) {
	    System.out.println(estado);
	    existe = true;
    }
  }

  // se não imprimiu nenhum estado, imprime asterisco
  if (!existe)
    System.out.println("*");
  }
}
