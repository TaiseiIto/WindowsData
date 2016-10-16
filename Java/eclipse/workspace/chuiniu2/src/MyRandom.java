import java.util.Random;

public class MyRandom extends Random {
	public int[] numbers;
	public int consumed = 0;

	public MyRandom(int[] numbers) {
		this.numbers = numbers;
	}

	@Override
	public int nextInt(int upperBound) {
		int v = numbers[consumed++];
		System.err.println(v);
		if (v < 0)
			return 0;
		if (v >= upperBound)
			return upperBound;
		return v;
	}
}
