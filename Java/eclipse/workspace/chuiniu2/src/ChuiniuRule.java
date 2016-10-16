public class ChuiniuRule {
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
			if (di == 1 && ! diceOneHasBeenCalled && callDice != 1)
				++c;
		}
		return c >= callCount;
	}

	/** 宣言が前回の宣言より大きいか判定する
	 * 
	 * @param callDice 宣言のダイスの目
	 * @param callCount 宣言のダイスの個数
	 * @param lastCallDice 前回の宣言のダイスの目
	 * @param lastCallCount 前回の宣言のダイスの個数
	 * 
	 * @return 宣言が前回の宣言より大きければ{@code true}。さもなければ{@code false}
	 * 
	 */
	public boolean largerThan(int callDice, int callCount, int lastCallDice, int lastCallCount) {
		// fixme
		if ((callDice > lastCallDice && callCount >= lastCallCount) || (callDice >= lastCallDice && callCount > lastCallCount)) {
			return true;
		} else
			return false;
	}

	/** 宣言が正しい形式か判定する
	 *
	 * @param callDice 宣言のダイスの目
	 * @param callCount 宣言のダイスの個数
	 * 
	 * @return 宣言が正しい形式なら{@code true}。さもなければ{@code false}
	 * 
	 */
	public boolean isValidCall(int callDice, int callCount) {
		// todo ダイスの目が不正(1-6 以外)だったら false
		// todo 個数が不正(1-10 以外)だったら false
		if(1 <= callDice && callDice <= 6  && 1 <= callCount && callCount <= 10 )return true;
		else return false;
	}
}
