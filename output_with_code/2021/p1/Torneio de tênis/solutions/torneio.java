// OBI2021
// Torneio de Tênis

import java.util.Scanner;
import java.io.*;

public class torneio {
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	    
	int vitorias = 0;
	char resultado;
	
	for (int i=0; i<6; i++) {
	    resultado = in.next().charAt(0);
	    if(resultado == 'V')
		vitorias++;
	}
		
	if (vitorias == 0)
	    System.out.println(-1);
	else if(vitorias <= 2)
	    System.out.println(3);
	else if(vitorias <= 4)
	    System.out.println(2);
	else
	    System.out.println(1);
    }
}
