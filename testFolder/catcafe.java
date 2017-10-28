import java.util.*;
public class catcafe{
	public static void main(String[] args) {
		Song track1 = new Song("Cat Scratch Fever","Cat Stevens");
		Song track2 = new Song("Cat Scratch Fever","Cat Stevens");
		System.out.println(track1 == track2);
		Album cats = new Album("Cats","Cat Stevens",5);
		if(cats.addsong(track1)){
			System.out.println("Successfully added track");
		}
		cats.addsong(track2);

	}
}