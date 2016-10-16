import java.util.*;

public class ChuiniuGame {
	private int[] dices; // 0, 1, ..., 4 -> player, 5, 6, ..., 9 -> computer
	private Random rand;
	private Scanner scan;

	public ChuiniuGame(Random rand, Scanner scan) {
		this.rand = rand;
		this.scan = scan;

		dices = new int[10];
		for (int i = 0; i < dices.length; ++i)
			dices[i] = rand.nextInt(6) + 1;
	}

	public void play() {
		ChuiniuRule rule = new ChuiniuRule();

		boolean diceOneHasBeenCalled = false;
		boolean playerWin = false;
		ChuiniuCall lastCall = null;

		System.out.println("> **����(Chuiniu)�Q�[���J�n**");
		System.out.println("> Player�̃J�b�v�̃_�C�X�� " + formatDices(dices, 0, 5) + " �ł�");

		while (true) {
			// Player�̐錾
			ChuiniuCall call = this.askPlayerCall(lastCall);
			System.out.println("Player: " + call.dice + " �� " + call.count + " ��!");

			// Com�̊J
			if (rand.nextInt(4) >= 3) {
				System.out.println("Com: �J!");
				this.openCups();
				playerWin = rule.satisfy(this.dices, call.dice, call.count, diceOneHasBeenCalled);
				break; // while
			}

			// �Q�[���̏󋵂̃f�[�^�̍X�V
			if (call.dice == 1)
				diceOneHasBeenCalled = true;
			lastCall = call;

			// Com�̐錾
			call = this.askComputerCall(lastCall);
			System.out.println("Com: " + call.dice + " �� " + call.count + " ��!");

			// Player�̊J
			System.out.println("> �u�J�v���܂����H(0=���Ȃ��A1=����)");
			int ans = scan.nextInt();
			if (ans == 1) {
				this.openCups();
				playerWin = ! rule.satisfy(this.dices, call.dice, call.count, diceOneHasBeenCalled);
				break; // while
			}

			// �Q�[���̏󋵂̃f�[�^�̍X�V
			if (call.dice == 1)
				diceOneHasBeenCalled = true;
			lastCall = call;
		}

		// �Q�[���̌��ʂ̕\��
		if (playerWin) {
			System.out.println("> Player�̏����ł�!");
			System.out.println("Com: ������");
		} else {
			System.out.println("> Player�̕����ł�");
			System.out.println("Com: �������I");
		}
	}

	/**�@�_�C�X�̔z��̈ꕔ���t�H�[�}�b�g����
	 * 
	 * @param dices �_�C�X�̖ڂ̔z��, not {@code null}
	 * @param from �󎚂���ŏ��̃_�C�X�̓Y��
	 * @param to �󎚂���Ō�̃_�C�X�̓Y�� + 1
	 */
	public static String formatDices(int[] dices, int from, int to) {
		StringBuilder buf = new StringBuilder();
		for (int i = from; i < to; ++i) {
			if (i > from)
				buf.append(", ");
			buf.append(dices[i]);
		}
		return buf.toString();
	}

	public ChuiniuCall askPlayerCall(ChuiniuCall lastCall) {
		ChuiniuRule rule = new ChuiniuRule();
		System.out.println("> Player�̐錾����͂��Ă�������");
		while (true) {
			System.out.print("> �_�C�X�̖�: ");
			int dice = scan.nextInt();
			System.out.print("> ��: ");
			int count = scan.nextInt();
			if (! rule.isValidCall(dice, count)) {
				System.out.println("> �錾���s���ł�");
			}

			if (lastCall != null && ! rule.largerThan(dice, count, lastCall.dice, lastCall.count)) {
				System.out.println("> �O��̐錾���傫�Ȑ���錾���Ă�������");
				continue; // while
			}

			return new ChuiniuCall(dice, count);
		}
	}

	public ChuiniuCall askComputerCall(ChuiniuCall lastCall) {
		ChuiniuCall call = new ChuiniuCall(lastCall.dice, lastCall.count);
		if (call.dice < 6 && rand.nextInt(3) >= 2) {
			call.dice += 1;
		} else {
			call.count += rand.nextInt(3) + 1;
		}
		return call;
	}

	public void openCups() {
		System.out.println("> Player�̃J�b�v�̃_�C�X�� " + formatDices(dices, 0, 5) + " �ł�");
		System.out.println("> Com�̃J�b�v�̃_�C�X�� " + formatDices(dices, 5, 10) + " �ł�");
	}

}
