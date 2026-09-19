// OBI2022
// Tarefa Cinema

import java.util.Scanner;

public class cinema {

    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	
	int x = in.nextInt();
	int y = in.nextInt();
	int resp = 0;
	    
	    
	if (x < 18)
	    resp += 15;
	else if (x < 60)
	    resp += 30;
	else
	    resp += 20;
	
	if (y < 18)
	    resp += 15;
	else if (y < 60)
	    resp += 30;
	else
	    resp += 20;
	
	System.out.printf("%d\n", resp);
    
    }
}
