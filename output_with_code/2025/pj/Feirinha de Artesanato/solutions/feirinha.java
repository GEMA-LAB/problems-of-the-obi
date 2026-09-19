import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;
public class feirinha {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
        ArrayList<Integer> objetos1 = new ArrayList<Integer>();
        ArrayList<Integer> objetos2 = new ArrayList<Integer>();
        int[] tipo = new int[n];
        for(int i = 0; i < n; i++) tipo[i] = in.nextInt(); 
        for(int i = 0; i < n; i++) {
            int p = in.nextInt();
            if(tipo[i] == 1) objetos1.add(p);
            else objetos2.add(p);
        }
        Collections.sort(objetos1);
        Collections.sort(objetos2);
        int sum = 0, aux1 = 0, aux2 = 0;
        int c = in.nextInt();
        for(int i = 0; i < c; i++) {
            int t = in.nextInt();
            if(t == 1 && aux1 < objetos1.size()) {
                sum += objetos1.get(aux1);
                aux1++;
            } else if(t == 2 && aux2 < objetos2.size()) {
                sum += objetos2.get(aux2);
                aux2++;
            } else if(t == 0) {
                int obj1 = Integer.MAX_VALUE;
                if(aux1 < objetos1.size()) obj1 = objetos1.get(aux1);
                int obj2 = Integer.MAX_VALUE;
                if(aux2 < objetos2.size()) obj2 = objetos2.get(aux2);
                
                if(aux1 == objetos1.size() && aux2 == objetos2.size()) continue;
                if(obj1 <= obj2) {
                    sum += obj1;
                    aux1++;
                } else {
                    sum += obj2;
                    aux2++;
                }
            }
        }
        System.out.println(sum);
	}
}