import java.util.*;
class changetime{
	public static void main(String[] args) {
		int number = 7;
		int[] arr = {2,2,3,1,2,1,2};
		int count = 0;
		for(int i = arr.length - 1; i >= 0; i--){
			for(int j = 0; j < arr.length; j++){
				if(i == 3 && j == 1){
					int a = arr[i];
					arr[i] = arr[j];
					arr[j] = a;
					count++;
				}
			}
		}
	}
}