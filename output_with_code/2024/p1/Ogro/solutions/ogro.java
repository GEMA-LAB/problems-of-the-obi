// OBI2024 - Fase 1
// Ogro

import java.util.*;

public class ogro {

    public static void main(String[] args) {

	Scanner in = new Scanner(System.in);

	int e = in.nextInt();
	int d = in.nextInt();
	int res;
	
	if (e > d) {
	    res = e + d;
	}
	else {
	    res = 2 * (d - e);
	}

	System.out.println(res);
    }
}
