class Main {
	public static void main(String[] args) {
		ChuiniuRule cr = new ChuiniuRule();
		int[] dices1 = { 1, 2, 3 };
		if (! cr.satisfy(dices1, 2, 2, false))
			throw new UnittestFailure();
		int[] dices2 = { 2, 2, 3 };
		if (! cr.satisfy(dices2, 2, 3, false))
			throw new UnittestFailure();
	}
}
