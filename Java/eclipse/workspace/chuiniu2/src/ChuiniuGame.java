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

		System.out.println("> **水牛(Chuiniu)ゲーム開始**");
		System.out.println("> Playerのカップのダイスは " + formatDices(dices, 0, 5) + " です");

		while (true) {
			// Playerの宣言
			ChuiniuCall call = this.askPlayerCall(lastCall);
			System.out.println("Player: " + call.dice + " が " + call.count + " 個!");

			// Comの開
			if (rand.nextInt(4) >= 3) {
				System.out.println("Com: 開!");
				this.openCups();
				playerWin = rule.satisfy(this.dices, call.dice, call.count, diceOneHasBeenCalled);
				break; // while
			}

			// ゲームの状況のデータの更新
			if (call.dice == 1)
				diceOneHasBeenCalled = true;
			lastCall = call;

			// Comの宣言
			call = this.askComputerCall(lastCall);
			System.out.println("Com: " + call.dice + " が " + call.count + " 個!");

			// Playerの開
			System.out.println("> 「開」しますか？(0=しない、1=する)");
			int ans = scan.nextInt();
			if (ans == 1) {
				this.openCups();
				playerWin = ! rule.satisfy(this.dices, call.dice, call.count, diceOneHasBeenCalled);
				break; // while
			}

			// ゲームの状況のデータの更新
			if (call.dice == 1)
				diceOneHasBeenCalled = true;
			lastCall = call;
		}

		// ゲームの結果の表示
		if (playerWin) {
			System.out.println("> Playerの勝ちです!");
			System.out.println("Com: 負けた");
		} else {
			System.out.println("> Playerの負けです");
			System.out.println("Com: 勝った！");
		}
	}

	/**　ダイスの配列の一部をフォーマットする
	 * 
	 * @param dices ダイスの目の配列, not {@code null}
	 * @param from 印字する最初のダイスの添字
	 * @param to 印字する最後のダイスの添字 + 1
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
		System.out.println("> Playerの宣言を入力してください");
		while (true) {
			System.out.print("> ダイスの目: ");
			int dice = scan.nextInt();
			System.out.print("> 個数: ");
			int count = scan.nextInt();
			if (! rule.isValidCall(dice, count)) {
				System.out.println("> 宣言が不正です");
			}

			if (lastCall != null && ! rule.largerThan(dice, count, lastCall.dice, lastCall.count)) {
				System.out.println("> 前回の宣言より大きな数を宣言してください");
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
		System.out.println("> Playerのカップのダイスは " + formatDices(dices, 0, 5) + " です");
		System.out.println("> Comのカップのダイスは " + formatDices(dices, 5, 10) + " です");
	}

}
