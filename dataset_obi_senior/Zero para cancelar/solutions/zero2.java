// OBI2021
// Tarefa Zero para Cancelar

import java.util.Scanner;
import java.util.ArrayList;

public class zero2 {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int x, num=0;
		int[] comandos=new int[100000];
		
		for (int i=0; i<n; i++){
		    x = in.nextInt();		    
		    if (x == 0)
		        num--;
		    else
		        comandos[num++] = x;

		}

		int total=0;
		for (int i=0; i<num; i++){
		    total += comandos[i];
		}
		
		System.out.printf("%d\n",total); 
	}
}
