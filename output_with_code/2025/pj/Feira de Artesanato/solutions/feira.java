import java.util.*;
class Pair implements Comparable<Pair> {
    private int first, second;
    public Pair(int f, int s) {
        first = f;
        second = s;
    }
    public int getFirst() { return first; }
    public int getSecond() { return second; }
    public int compareTo(Pair other) {
        if(first != other.first) return first - other.first;
        return second - other.second;
    }
    public String toString() {
        return "(" + first + ", " + second + ")";
    }
}
public class feira {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int t = in.nextInt();
        ArrayList<Integer>[] objetos = (ArrayList<Integer>[]) new ArrayList[t + 1];
        for(int j = 1; j <= t; j++) objetos[j] = new ArrayList<Integer>();
        int[] tipo = new int[n];
        for(int i = 0; i < n; i++) tipo[i] = in.nextInt(); 
        for(int i = 0; i < n; i++) {
            int p = in.nextInt();
            objetos[tipo[i]].add(p);
        }
        for(int j = 1; j <= t; j++) {
            Collections.sort(objetos[j]);
        }
        
        long sum = 0;
        int[] aux = new int[t + 1];
        int mini = Integer.MAX_VALUE;
        int tipoMin = -1;
        TreeSet<Pair> minimos = new TreeSet<>();
        for(int j = 1; j <= t; j++) 
            if(objetos[j].size() > 0)
                minimos.add(new Pair(objetos[j].get(0), j));

        int c = in.nextInt();
        for(int i = 0; i < c; i++) {
            int ti = in.nextInt();
            
            if(ti == 0) {
                if(minimos.size() == 0) continue;
                
                Pair p = minimos.first();
                minimos.remove(minimos.first());
                sum += p.getFirst();
                aux[p.getSecond()]++;
                if(aux[p.getSecond()] < objetos[p.getSecond()].size()) {
                    minimos.add(new Pair(objetos[p.getSecond()].get(aux[p.getSecond()]), p.getSecond()));
                }
            } else {
                if(aux[ti] == objetos[ti].size()) continue;
                
                sum += objetos[ti].get(aux[ti]);
                minimos.remove(new Pair(objetos[ti].get(aux[ti]), ti));
                aux[ti]++;
                if(aux[ti] == objetos[ti].size()) continue;
                minimos.add(new Pair(objetos[ti].get(aux[ti]), ti));
            }
        }
        System.out.println(sum);
    }
}