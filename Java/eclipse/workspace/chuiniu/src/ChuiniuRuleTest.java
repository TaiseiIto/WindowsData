import static org.junit.Assert.*;

import org.junit.Test;

public class ChuiniuRuleTest {

	@Test
	public void test() {
		ChuiniuRule chuiniuRule = new ChuiniuRule();
		int[] dices = new int[10];
		int callDice;
		int callCount;
		boolean diceOneHasBeenCalled;
		for(dices[0]=1;dices[0]<=6;dices[0]++)
			for(dices[1]=1;dices[1]<=6;dices[1]++)
				for(dices[2]=1;dices[2]<=6;dices[2]++)
					for(dices[3]=1;dices[3]<=6;dices[3]++)
						for(dices[4]=1;dices[4]<=6;dices[4]++)
							for(dices[5]=1;dices[5]<=6;dices[5]++)
								for(dices[6]=1;dices[6]<=6;dices[6]++)
									for(dices[7]=1;dices[7]<=6;dices[7]++)
										for(dices[8]=1;dices[8]<=6;dices[8]++)
											for(dices[9]=1;dices[9]<=6;dices[9]++)
												for(callDice=1;callDice<=6;callDice++)
													for(callCount=1;callCount<=10;callCount++)
													{
														diceOneHasBeenCalled = true;
														int c = 0;
														for (int i = 0; i < dices.length; ++i) {
															int di = dices[i];
															if (di == callDice)
																++c;
															if (di == 1 && ! diceOneHasBeenCalled)
																++c;
														}
														assertTrue((c >= callCount) == chuiniuRule.satisfy(dices, callDice, callCount, diceOneHasBeenCalled));
														diceOneHasBeenCalled = false;
														c = 0;
														for (int i = 0; i < dices.length; ++i) {
															int di = dices[i];
															if (di == callDice)
																++c;
															if (di == 1 && ! diceOneHasBeenCalled)
																++c;
														}
														assertTrue((c >= callCount) == chuiniuRule.satisfy(dices, callDice, callCount, diceOneHasBeenCalled));
													}
		return;
	}
}
