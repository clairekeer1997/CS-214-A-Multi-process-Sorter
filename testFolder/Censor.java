import java.util.*;
class Censor{
	public static String censor(String a, String b){
		int index = 0;
		String newstring = a;
		String s = "";
		for(int i = 0; i < b.length(); i++){
			s += "*";
		}
		for(int i = 0; i < a.length(); i++){
			if(a.charAt(i) == ' '){
				if(index == 0){
					if(a.substring(index,i).equals(b)){
					newstring = s + newstring.substring(i);
					}else{
						index = i + 1;
					}
				}else if(a.substring(index,i).equals(b)){
					newstring = newstring.substring(0,index) + s + newstring.substring(i);
				}
				else
					index = i + 1;
			}

		}
		return newstring;
	}
	public static void main(String[] args) {
		String c = "he the house hks wid";
		String d = "at";
		System.out.println(censor(c,d));
	}
}