import java.util.Scanner;

public class suco {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int resp = 0;

		for (int i = 1 ; i <= n ; i++) {
			int a = sc.nextInt();
            int b = sc.nextInt();

			if (a == 1)
                resp++ ; 
			else
                if (b == 0)
                    resp++ ;  
		}

        System.out.println(resp);
    }
}
