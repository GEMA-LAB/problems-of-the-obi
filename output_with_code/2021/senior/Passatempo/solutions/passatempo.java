// OBI2021 - fase 2
// passatempo

import java.io.*;
import java.util.*;

class passatempo {

    static final int MAX=100;
    static Scanner scan = new Scanner(new BufferedReader (new InputStreamReader(System.in)));

    public static void main(String[] arg) {
        TreeMap<String, Integer> vars = new TreeMap<String, Integer>();
	int i,j,l,c;
	String x;

	l=scan.nextInt();
	c=scan.nextInt();

	int[] vlines=new int[l];
	int[] vcols=new int[c];
	String[][] puzzle=new String[l][c];
	for (i = 0; i < l; i++) {
	    for (j = 0; j < c; j++) {
		x=scan.next();
		puzzle[i][j]=x;
		if (vars.containsKey(x))
		    continue;
		vars.put(x,Integer.MIN_VALUE);
	    }
	    vlines[i]=scan.nextInt();
	    
	}
	for (j = 0; j < c; j++)
	    vcols[j]=scan.nextInt();

	int solved=0,which_i,which_j,n_v;
	while (solved!=vars.size()) {
	    // find in columns
	    for (j = 0; j < c; j++) {
		which_i=-1; n_v=0;
		for (i = 0; i < l; i++) {
		    if (vars.get(puzzle[i][j])==Integer.MIN_VALUE) {
			if (which_i==-1) {
			    which_i=i;
			    n_v++;
			}
			else if (!puzzle[i][j].equals(puzzle[which_i][j])) {
			    n_v++;
			}
		    }
		}
		if (n_v==1) { // solve it for puzzle[which_i][j] in column j
		    int sol=vcols[j], n=0;
		    for (i = 0; i < l; i++) {
			if (!puzzle[i][j].equals(puzzle[which_i][j]))
			    sol-=vars.get(puzzle[i][j]);
			else
			    n++;
		    }
		    if (sol%n != 0) System.exit(1);
		    vars.put(puzzle[which_i][j],sol/n);
		    solved++;
		    continue;
		}
	    }
	    // find in lines
	    for (i = 0; i < l; i++) {
		which_j=-1; n_v=0;
		for (j = 0; j < c; j++) {
		    if (vars.get(puzzle[i][j])==Integer.MIN_VALUE) {
			if (which_j==-1) {
			    which_j=j;
			    n_v++;
			}
			else if (!puzzle[i][j].equals(puzzle[i][which_j])) {
			    n_v++;
			}
		    }
		}
		if (n_v==1) { // solve it for puzzle[i][which_j] in line i 
		    int sol=vlines[i], n=0;
		    for (j = 0; j < c; j++) {
			if (!puzzle[i][j].equals(puzzle[i][which_j]))
			    sol-=vars.get(puzzle[i][j]);
			else
			    n++;
		    }
		    if (sol%n != 0) System.exit(1);
		    vars.put(puzzle[i][which_j],sol/n);
		    solved++;
		    continue;
		}
	    }
	}
	for (String k: vars.keySet())
	    System.out.printf("%s %d\n", k, vars.get(k));

    }
}
