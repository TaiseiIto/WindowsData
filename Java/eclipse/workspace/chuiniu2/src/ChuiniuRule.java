public class ChuiniuRule {
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
			if (di == 1 && ! diceOneHasBeenCalled && callDice != 1)
				++c;
		}
		return c >= callCount;
	}

	/** �錾���O��̐錾���傫�������肷��
	 * 
	 * @param callDice �錾�̃_�C�X�̖�
	 * @param callCount �錾�̃_�C�X�̌�
	 * @param lastCallDice �O��̐錾�̃_�C�X�̖�
	 * @param lastCallCount �O��̐錾�̃_�C�X�̌�
	 * 
	 * @return �錾���O��̐錾���傫�����{@code true}�B�����Ȃ����{@code false}
	 * 
	 */
	public boolean largerThan(int callDice, int callCount, int lastCallDice, int lastCallCount) {
		// fixme
		if ((callDice > lastCallDice && callCount >= lastCallCount) || (callDice >= lastCallDice && callCount > lastCallCount)) {
			return true;
		} else
			return false;
	}

	/** �錾���������`�������肷��
	 *
	 * @param callDice �錾�̃_�C�X�̖�
	 * @param callCount �錾�̃_�C�X�̌�
	 * 
	 * @return �錾���������`���Ȃ�{@code true}�B�����Ȃ����{@code false}
	 * 
	 */
	public boolean isValidCall(int callDice, int callCount) {
		// todo �_�C�X�̖ڂ��s��(1-6 �ȊO)�������� false
		// todo �����s��(1-10 �ȊO)�������� false
		if(1 <= callDice && callDice <= 6  && 1 <= callCount && callCount <= 10 )return true;
		else return false;
	}
}
