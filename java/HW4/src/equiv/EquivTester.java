// 5506192

package equiv;

import util.Tester;

// Structure
class EquivSk<E> {
	public EquivSk() {

	}

	public void add(E e1, E e2) {
	}

	public boolean are(E e1, E e2) {
		return false;
	}
}

public class EquivTester extends Tester {

	void testStructure() {
		testEqualClasses(Equiv.class, EquivSk.class);
	}

	void testEquiv() {
		initPublishedTest(Equiv.class);
		Equiv<String> equiv = new Equiv<>();
		equiv.add("ball", "balloon");
		equiv.add("child", "person");
		equiv.add("girl", "child");
		equiv.add("ball", "sphere");
		equiv.add("sphere", "circle");
		equiv.add("dog", "cat");

		checkEq(equiv.are("balloon", "circle"), true, "are(ballon, circle)");
		checkEq(equiv.are("child", "girl"), true, "are(child, girl)");
		checkEq(equiv.are("sun", "sun"), true, "are(sun, sun)");
		checkEq(equiv.are("dog", "ball"), false, "are(dog, ball)");
		checkEq(equiv.are("table", "dog"), false, "are(table, dog)");
	}
	
	void testEquiv2() {
		initPublishedTest(Equiv.class);
		Equiv<Integer> equiv = new Equiv<>();
		equiv.add(1, 4);
		
		checkEq(equiv.are(4, 1), true, "are(4, 1)");
		checkEq(equiv.are(3, 1), false, "are(3, 1)");
	}

	// ------------------------------------------------------------

	public static void main(String[] args) {
		new EquivTester().myMain("equiv");
	}

	// ------------------------------------------------------------
	// Here you can choose which tests to run.

	public void myTests() {
		testStructure();
		testEquiv();
		testEquiv2();
	}

}
