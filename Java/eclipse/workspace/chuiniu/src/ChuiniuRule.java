class ChuiniuRule {
	/** �_�C�X���ڂ̐錾�𖞂����Ă��邩�𔻒肷��
	 * 
	 * @param dices ��ɏo���ꂽ���ꂼ��̃_�C�X�̖�, not {@code null}
	 * @param callDice �錾�̃_�C�X�̖�
	 * @param callCount �錾�̃_�C�X�̌�
	 * @param diceOneHasBeenCalled �ߋ��ɂP��ł�1�̖ڂ��錾����Ă����{@code true}�B�����Ȃ����{@code false}�B
	 * 
	 * @return ��ɏo���ꂽ�_�C�X���錾�𖞂����Ă����{@code true}�B�����Ȃ����{@code false}�B
	 * 
	 * ����{@code diceOneHasBeenCalled}�͋L������Ȃ��B�i���Ȃ킿�A�ߋ���{@code true}��n����ČĂт�����Ă��A
	 * ����{@code false}��n����ČĂт����ꂽ�Ƃ��́A�P�����C���h�J�[�h�Ƃ��Ĉ����B�j
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
