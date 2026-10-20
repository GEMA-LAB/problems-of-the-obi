import java.util.*;
class Celula {
  public int linha, coluna;
  public long poder; 
  public Celula(int l, int c, long p) {
    linha = l;
    coluna = c;
    poder = p;
  }
}
class CelulaComparator implements Comparator<Celula> {
  public int compare(Celula a, Celula b) {
    return (int)(a.poder - b.poder);
  }
}
public class poder
{
  static final int MAXN = 100010;
  static int[] pai = new int[MAXN];
  static long[] soma = new long[MAXN];
  static ArrayList<ArrayList<Celula>> componente = new ArrayList<ArrayList<Celula>>();
  static int[] dx = {0, 1, 0, -1};
  static int[] dy = {1, 0, -1, 0};

  public static int find(int v) {
    if(pai[v] == v) return v;
    return find(pai[v]);
  }
  
  public static void une(int a, int b) {
    a = find(a);
    b = find(b);
    
    if(a == b) return;
    
    if(componente.get(a).size() > componente.get(b).size()) {
      int c = a;
      a = b;
      b = c;
    }
    
    for(int i = 0; i < componente.get(a).size(); i++) {
      componente.get(b).add(componente.get(a).get(i));
    }
    pai[a] = b;
    soma[b] += soma[a];
    componente.get(a).clear();
  }
  
	public static void main(String[] args) {
	  ArrayList<ArrayList<Long>> poderes = new ArrayList<ArrayList<Long>>();
    ArrayList<ArrayList<Long>> resp = new ArrayList<ArrayList<Long>>();
	  ArrayList<ArrayList<Integer>> ativo = new ArrayList<ArrayList<Integer>>();
	  ArrayList<ArrayList<Integer>> indice = new ArrayList<ArrayList<Integer>>();
    
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int m = in.nextInt();
		ArrayList<Celula> celulas = new ArrayList<Celula>();
		int id = 0;
		componente.add(new ArrayList<Celula>());
		for(int i = 0; i < n; i++) {
		  poderes.add(new ArrayList<Long>());
		  resp.add(new ArrayList<Long>());
		  ativo.add(new ArrayList<Integer>());
		  indice.add(new ArrayList<Integer>());
      for(int j = 0; j < m; j++) {
        long p = in.nextLong();
        
        poderes.get(i).add(p);
        resp.get(i).add(new Long(0));
        ativo.get(i).add(0);
        id++;
        indice.get(i).add(id);
        componente.add(new ArrayList<Celula>());
        
        Celula nova = new Celula(i, j, p);
        celulas.add(nova);
      }
		}
    Collections.sort(celulas, new CelulaComparator());
    
    for(int i = 0; i < celulas.size(); i++) {
      int l = celulas.get(i).linha;
      int c = celulas.get(i).coluna;
      long p = celulas.get(i).poder;
      
      ativo.get(l).set(c, 1);
      id = indice.get(l).get(c);
      pai[id] = id;
      soma[id] = p;
      componente.get(id).add(celulas.get(i));
      for(int k = 0; k < 4; k++) {
        int vizl = l + dx[k];
        int vizc = c + dy[k];
        if(vizl < 0 || vizl >= n || vizc < 0 || vizc >= m) continue;
        if(ativo.get(vizl).get(vizc) == 0) continue;
        
        int vizid = indice.get(vizl).get(vizc);
        int vizpai = find(vizid);
        if(p <= soma[vizpai]) {
          une(id, vizpai);
        } else {
          for(int t = 0; t < componente.get(vizpai).size(); t++) {
            int lcel = componente.get(vizpai).get(t).linha;
            int ccel = componente.get(vizpai).get(t).coluna;
            resp.get(lcel).set(ccel, soma[vizpai]);
          }
          componente.get(vizpai).clear();
          une(vizpai, id);
        }
      }
      
    }
    
    int llast = (celulas.get(celulas.size() - 1)).linha;
    int clast = (celulas.get(celulas.size() - 1)).coluna;
    int idlast = indice.get(llast).get(clast);
    int pailast = find(idlast);
    for(int t = 0; t < componente.get(pailast).size(); t++) {
      int lcel = componente.get(pailast).get(t).linha;
      int ccel = componente.get(pailast).get(t).coluna;
      resp.get(lcel).set(ccel, soma[pailast]);
    }
    
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
        System.out.print(resp.get(i).get(j) + " ");
      }
      System.out.println();
    }
	}
}