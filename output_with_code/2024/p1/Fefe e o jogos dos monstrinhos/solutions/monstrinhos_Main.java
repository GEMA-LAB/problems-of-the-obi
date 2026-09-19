import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        
        try{
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));   
        
            
            int countMonster = Integer.parseInt(br.readLine());
            List<Integer> monsterList = new ArrayList<>(countMonster);
            
            int countFairy = Integer.parseInt(br.readLine());
            List<Integer[]> fairyList = new ArrayList<>(countFairy);

            for( int i=0; i<countMonster; i++ ){
                monsterList.add(Integer.parseInt(br.readLine()));
            }
            for( int i=0; i<countFairy; i++ ){
                Integer[] fairy = new Integer[2];
                fairy[0] = Integer.parseInt(br.readLine());
                fairyList.add(fairy);
            }
            for( int i=0; i<countFairy; i++ ){
                fairyList.get(i)[1] = Integer.parseInt(br.readLine());
            }

            fairyList.sort((o1,o2) -> Integer.compare(o1[0], o2[0]));
            monsterList.sort((o1,o2) -> o1.compareTo(o2));


            //Combat > 

            int idxMonster = 0;
            for(int i=0; i<countFairy; i++){
                int fairyPower = fairyList.get(i)[0];
                int fairyCountAtk = fairyList.get(i)[1];

                for(; idxMonster<countMonster && fairyCountAtk > 0; idxMonster++,fairyCountAtk--){
                    int monsterPower = monsterList.get(idxMonster);
                    if( monsterPower >= fairyPower ){
                        break;
                    }
                }
                

            }
            System.out.println((idxMonster));
            
        }catch(Exception e){
            e.printStackTrace();
        }

    }

}