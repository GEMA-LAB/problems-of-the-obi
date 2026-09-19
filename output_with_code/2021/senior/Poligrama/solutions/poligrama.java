// OBI2021 - Fase 2
// Poligrama

import java.util.Arrays;
import java.util.Scanner;

public class poligrama {

    public static String ordenaString(String entrada) {
        char tempArray[] = entrada.toCharArray();
        Arrays.sort(tempArray);
        return new String(tempArray);
    }
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	
	int n;
	String s, a, b;
	boolean ok;
	
	n = in.nextInt();
	s = in.next();
	
	for (int k = 1; k < n; ++k) {
	    if (n % k == 0) {
		a = s.substring(0, k);
		a = ordenaString(a);
		//System.out.printf("n=%d, k=%d, a=%s\n",n,k,a);
		ok = true;
		
		for (int i = k; i < n; i += k) {
		    b = s.substring(i, i+k);
		    b = ordenaString(b);
		    //System.out.printf("%d %d b=%s\n",i,k,b);
		    if (!a.equals(b)) {
			//System.out.printf("%s %s %s\n",a,b,a==b);
			ok = false;
			break;
		    }
		}
		
		if (ok) {
		    System.out.println(s.substring(0, k));
		    return;
		}
	    }
	}
	
	System.out.println("*");
    }
}
