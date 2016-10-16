import java.util.Random;
import java.util.Scanner;

public class DummyRun {
	public static void main(String[] args) {
		Random rand = new MyRandom(new int[] {
			0, 1, 2, 3, 4, // playerのカップのダイスの目
			0, 1, 2, 3, 4, // comのカップのダイスの目
			0, // (2) comは「開」しない
			0, 1, // (3) comの次の「宣言」はダイスの個数を2こ増やしたもの(2, 3)
			3 // (6) comは「開」する
		});
		Scanner scan = new Scanner(
			"2 1 " // (1) ダイスの目、個数はそれぞれ 2, 1
			+ "0 " // (4) playerは「開」しない
			+ "2 4 " // (5) ダイスの目、個数はそれぞれ 2, 4
		);
		ChuiniuGame game = new ChuiniuGame(rand, scan);
		game.play();
	}
}

