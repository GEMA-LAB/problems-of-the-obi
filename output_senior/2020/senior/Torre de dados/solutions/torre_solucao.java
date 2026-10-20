// OBI2020 - Fase 3
// torre de dados

import java.util.Scanner;
import java.util.Arrays;
import java.util.Collections;

public class solucao {


    public static int n;
    public static int[][] dado;
    public static int[] lado = {5, 3, 4, 1, 2, 0};

    public static int max_lado(int n, int top) {
	int bottom = lado[top];
	int max=0;
	for (int i=0; i<6; i++) {
	    if (i==top || i==bottom) continue;
	    if (max < dado[n][i])
		max = dado[n][i];
	}
	return max;
    }

    public static int encontra(int n, int value) {
	for (int i=0; i<6; i++) {
	    if (dado[n][i] == value)
		return i;
	}
	return -1;
    }
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	int n = in.nextInt();
	dado = new int[n][6];
	
	for (int i=0;i<n;i++)
	    for (int j=0;j<6;j++)
		dado[i][j] = in.nextInt();
  
	// processa
	int resultado = 0;
	for (int primeiro = 0; primeiro <6; primeiro++) {
	    int base_anterior = dado[0][lado[primeiro]];
	    int soma = max_lado(0, primeiro);
	    for (int i=1;i<n;i++) {
		int topo_corrente = encontra(i,base_anterior);
		soma += max_lado(i,topo_corrente);
		base_anterior = dado[i][lado[topo_corrente]];
	    }
	    if (soma > resultado)
		resultado = soma;
	}
	
	// escreve resultado
	System.out.printf("%d\n", resultado);
    }
}
