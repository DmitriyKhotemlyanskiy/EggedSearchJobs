package equiv;

public class Main {

	public static void main(String[] args) {
		Equiv<String> equiv = new Equiv<>();
		equiv.add("ball", "balloon");
		equiv.add("child", "person");
		equiv.add("girl", "child");
		equiv.add("ball", "sphere");
		equiv.add("sphere", "circle");
		equiv.add("dog", "cat");

		System.out.println(equiv.are("balloon", "circle"));
		System.out.println(equiv.are("child", "girl"));
		System.out.println(equiv.are("sun", "sun"));	
		System.out.println(equiv.are("dog", "ball"));
		System.out.println(equiv.are("table", "dog"));
	}

}
