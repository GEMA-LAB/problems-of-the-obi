// OBI2021 - Fase 2
// Cubo e quadrado

import java.util.Scanner;

public class cubo {

    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	
	int a, b, resp;
	
	a = in.nextInt();
	b = in.nextInt();

	int raiz_cubica = (int) Math.floor(Math.pow(a,1./3.));
	int cubo = raiz_cubica * raiz_cubica * raiz_cubica;
	if (cubo < a) {   // raiz_cubica foi truncada, pode ser menor do que a
	    raiz_cubica++;
	    cubo = raiz_cubica * raiz_cubica * raiz_cubica;
	}

	//procura por cubos entre a e b, verificando se é também um quadrado
	resp = 0;
	while (cubo <= b) {
	    int raiz_quadrada = (int) Math.floor(Math.sqrt(cubo));
	    int quadrado = raiz_quadrada * raiz_quadrada;
	    if (quadrado == cubo) {
		resp++;
	    }
	    raiz_cubica++;
	    cubo = raiz_cubica * raiz_cubica * raiz_cubica;
	}	
	System.out.println(resp);
    }
}
