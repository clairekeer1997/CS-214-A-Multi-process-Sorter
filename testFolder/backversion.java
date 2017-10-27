import java.util.*;
class backversion{
	public static String back(String s){
		if(s.length() == 0){
			return "";
		}else{
			if(s.length() == 1){
				return back("") + s.charAt(0); 
			}
			return back(s.substring(1)) + s.charAt(0); 
		}
	}
	public static void main(String[] args) {
		String s = back("abcdefgh");
		System.out.println(s);
	}
}