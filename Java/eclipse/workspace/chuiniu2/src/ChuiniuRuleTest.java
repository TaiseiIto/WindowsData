import static org.junit.Assert.*;
import java.util.*;

import org.junit.Test;

public class ChuiniuRuleTest {

	@Test
	public void satisfyTest1() {
		ChuiniuRule chuiniuRule = new ChuiniuRule();
		int[] dices = {1,2,3};
		assertTrue(chuiniuRule.satisfy(dices, 2, 2, false));
	}

	@Test
	public void satisfyTest2() {
		ChuiniuRule chuiniuRule = new ChuiniuRule();
		int[] dices = {2,2,3};
		assertFalse(chuiniuRule.satisfy(dices, 2, 3, false));
	}

	@Test
	public void largerThanTest1() {
		ChuiniuRule chuiniuRule = new ChuiniuRule();
		assertFalse(chuiniuRule.largerThan(1,2, 2, 1));
	}
	
	@Test
	public void largerThanTest2() {
		ChuiniuRule chuiniuRule = new ChuiniuRule();
		assertFalse(chuiniuRule.largerThan(1,2, 1, 3));
	}
	
	@Test
	public void largerThanTest3() {
		ChuiniuRule chuiniuRule = new ChuiniuRule();
		assertFalse(chuiniuRule.largerThan(1,2, 1, 2));
	}
	
	@Test
	public void largerThanTest4() {
		ChuiniuRule chuiniuRule = new ChuiniuRule();
		assertTrue(chuiniuRule.largerThan(1,2, 1, 1));
	}
	
	@Test
	public void isValidCallTest1() {
		ChuiniuRule chuiniuRule = new ChuiniuRule();
		assertTrue(chuiniuRule.isValidCall(6, 1));
	}
}
