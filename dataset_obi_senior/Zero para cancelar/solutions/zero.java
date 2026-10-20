// OBI2021
// Tarefa Zero para Cancelar
// 22461-I
// Paulo Ricardo Alves Chagas

import java.util.Scanner;
import java.util.ArrayList;

public class zero {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int nt,t=0;
		ArrayList<Integer> numeros = new ArrayList();
		
		for(int i=0;i<n;i++){
		    nt = in.nextInt();
		    
		    if(nt != 0){
		        numeros.add(nt);
		    }else{
		        numeros.remove(numeros.size() - 1);
		    }
		}
		
		for(int i=0;i<numeros.size();i++){
		    t+=numeros.get(i);
		}
		
		System.out.printf("%d\n",t); 
	}
}
