public class Test {

	public static void main(String[] args) {
		double result = 0.5;
		for (int i = 0; i <= 1000000; i++) {
			result = (0.36 * result + 0.27) / (0.28 * result + 0.41);
		}
		System.out.println(result);
	}

}
