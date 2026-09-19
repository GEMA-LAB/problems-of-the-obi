import java.util.*;
public class codigo {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		String s = in.next();
		String last = "0";
		int qtd = 0;
		for(int i = 0; i < n; i++) {
		  String letter = s.substring(i, i + 1);
		  if(letter.equals(last)) qtd++;
		  else {
		    if(!last.equals("0")) System.out.print(" " + qtd + " " + last);
		    
		    qtd = 1;
		  }
		  
		  last = letter;
		}
		System.out.println(" " + qtd + " " + last);
	}
}
