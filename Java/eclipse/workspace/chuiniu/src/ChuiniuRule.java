class ChuiniuRule {
	/** ダイスが目の宣言を満たしているかを判定する
	 * 
	 * @param dices 場に出されたそれぞれのダイスの目, not {@code null}
	 * @param callDice 宣言のダイスの目
	 * @param callCount 宣言のダイスの個数
	 * @param diceOneHasBeenCalled 過去に１回でも1の目が宣言されていれば{@code true}。さもなければ{@code false}。
	 * 
	 * @return 場に出されたダイスが宣言を満たしていれば{@code true}。さもなければ{@code false}。
	 * 
	 * 引数{@code diceOneHasBeenCalled}は記憶されない。（すなわち、過去に{@code true}を渡されて呼びだされても、
	 * 次に{@code false}を渡されて呼びだされたときは、１をワイルドカードとして扱う。）
	 */
	public boolean satisfy(int[] dices, int callDice, int callCount, boolean diceOneHasBeenCalled) {
		int c = 0;
		for (int i = 0; i < dices.length; ++i) {
			int di = dices[i];
			if (di == callDice)
				++c;
			if (di == 1 && ! diceOneHasBeenCalled)
				++c;
		}
		return c >= callCount;
	}
}
