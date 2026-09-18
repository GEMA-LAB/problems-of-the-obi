// OBI-2019 Fase 2
// Problema Ponto Medio

import java.util.Scanner;

public class medio_java {
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	long lado;

	int N = in.nextInt();
	lado = 2;
	while (N-- > 0) lado += lado-1;

	System.out.println(lado*lado);
    }
}
