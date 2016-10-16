import java.util.*;

public class Run {
	public static void main(String[] args) {
		Random rand = new Random();
		Scanner scan = new Scanner(System.in);
		ChuiniuGame game = new ChuiniuGame(rand, scan);
		game.play();
	}
}