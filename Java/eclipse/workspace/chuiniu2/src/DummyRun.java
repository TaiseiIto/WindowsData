import java.util.Random;
import java.util.Scanner;

public class DummyRun {
	public static void main(String[] args) {
		Random rand = new MyRandom(new int[] {
			0, 1, 2, 3, 4, // player�̃J�b�v�̃_�C�X�̖�
			0, 1, 2, 3, 4, // com�̃J�b�v�̃_�C�X�̖�
			0, // (2) com�́u�J�v���Ȃ�
			0, 1, // (3) com�̎��́u�錾�v�̓_�C�X�̌���2�����₵������(2, 3)
			3 // (6) com�́u�J�v����
		});
		Scanner scan = new Scanner(
			"2 1 " // (1) �_�C�X�̖ځA���͂��ꂼ�� 2, 1
			+ "0 " // (4) player�́u�J�v���Ȃ�
			+ "2 4 " // (5) �_�C�X�̖ځA���͂��ꂼ�� 2, 4
		);
		ChuiniuGame game = new ChuiniuGame(rand, scan);
		game.play();
	}
}

