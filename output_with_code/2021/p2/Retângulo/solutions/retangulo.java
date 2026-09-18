// OBI2021
// rectangulo
import java.io.BufferedReader; 
import java.io.IOException; 
import java.io.InputStreamReader; 
import java.util.Scanner; 
import java.util.StringTokenizer;

public class retangulo {

    public static final int MAXN = 100000;
    public static int n;
    public static int[] trees;
    public static int arc_sum=0, half_circ, p=0, q=0, np=0, i;

    static class FastReader 
    { 
        BufferedReader br; 
        StringTokenizer st; 
  
        public FastReader() 
        { 
            br = new BufferedReader(new
				    InputStreamReader(System.in)); 
        } 
  
        String next() 
        { 
            while (st == null || !st.hasMoreElements()) 
		{ 
                try
		    { 
			st = new StringTokenizer(br.readLine()); 
		    } 
                catch (IOException  e) 
		    { 
			e.printStackTrace(); 
		    } 
		} 
            return st.nextToken(); 
        } 
  
        int nextInt() 
        { 
            return Integer.parseInt(next()); 
        } 
  
        long nextLong() 
        { 
            return Long.parseLong(next()); 
        } 
  
        double nextDouble() 
        { 
            return Double.parseDouble(next()); 
        } 
  
        String nextLine() 
        { 
            String str = ""; 
            try
		{ 
		    str = br.readLine(); 
		} 
            catch (IOException e) 
		{ 
		    e.printStackTrace(); 
		} 
            return str; 
        } 
    } 

    public static void main(String[] args) {
	FastReader in  = new FastReader();
	n = in.nextInt();
	trees = new int[n];
	for (int i=0; i<n; i++) {
	    trees[i] = in.nextInt();
	    arc_sum = arc_sum + trees[i];
	}
	if (arc_sum % 2 == 1) {
	    System.out.printf("N\n");
	    return;
	}
	half_circ = arc_sum/2;
	arc_sum = 0;
	//search for two pairs of diametrical points
	while (q != n && np < 2) {
	    if (arc_sum < half_circ) {  //advance q
		arc_sum = arc_sum + trees[q];
		q++;
	    }
	    else if (arc_sum > half_circ) { // advance p
		arc_sum = arc_sum - trees[p];
		p++;
	    }
	    else {  // advance p and q
		arc_sum = arc_sum - trees[p] + trees[q];
		p++; q++; 
		//if (arc_sum > 0) 
		np++;
	    }
	}
	if (np >= 2)
	    System.out.printf("S\n");
	else
	    System.out.printf("N\n");
    }
}
