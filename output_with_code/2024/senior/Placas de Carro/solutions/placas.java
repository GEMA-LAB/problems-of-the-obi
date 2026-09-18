import java.util.*;

public class placas
{
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
	    String placa = in.next();
	    if(isOld(placa)) System.out.println(1);
	    else if(isNew(placa)) System.out.println(2);
	    else System.out.println(0);
	}
	
	private static boolean isDigit(String s) {
	  char d = s.charAt(0);
	  return ('0' <= d) && (d <= '9');
	}
	
	private static boolean isLetter(String s) {
	  char d = s.charAt(0);
	  return ('A' <= d) && (d <= 'Z');
	}
	
	private static boolean isOld(String s) {
	  //OBI-2024
	  if(s.length() != 8) return false;
	  if(!isLetter(s.substring(0, 1))) return false;
	  if(!isLetter(s.substring(1, 2))) return false;
	  if(!isLetter(s.substring(2, 3))) return false;
	  if(!s.substring(3, 4).equals("-")) return false;
	  if(!isDigit(s.substring(4, 5))) return false;
	  if(!isDigit(s.substring(5, 6))) return false;
	  if(!isDigit(s.substring(6, 7))) return false;
	  if(!isDigit(s.substring(7, 8))) return false;
	  return true;
	}
	
	private static boolean isNew(String s) {
	  //OBI2P24
	  if(s.length() != 7) return false;
	  if(!isLetter(s.substring(0, 1))) return false;
	  if(!isLetter(s.substring(1, 2))) return false;
	  if(!isLetter(s.substring(2, 3))) return false;
	  if(!isDigit(s.substring(3, 4))) return false;
	  if(!isLetter(s.substring(4, 5))) return false;
	  if(!isDigit(s.substring(5, 6))) return false;
	  if(!isDigit(s.substring(6, 7))) return false;
	  return true;
	}
}
