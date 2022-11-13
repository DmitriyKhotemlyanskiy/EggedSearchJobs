// 7247835
package iterator;

import util.Tester;

interface IteratorSk {
	boolean hasNext();
	int next();
}

class ArraySk implements MyIterator {
	public ArraySk(int[] a) {
	}

	public boolean hasNext() {
		return false;
	}

	public int next() {
		return 0;
	}
}

class FibonacciSk implements MyIterator {
	public FibonacciSk(int upperBound) {
	}

	public boolean hasNext() {
		return false;
	}

	public int next() {
		return 0;
	}
}


class BaseIteratorTester extends Tester {
	void checkIt(MyIterator it, int[] a, String msg) {
		for (int i = 0; i < a.length; i++) {
			checkEq(it.hasNext(), true, msg + " : " + i + "-th hasNext() ");
			checkEq(it.next(), a[i], msg + " : " + i + "-th next() ");
		}
		checkEq(it.hasNext(), false, msg + "last hasNext() ");
	}	
}

public class IteratorTester extends BaseIteratorTester {
	void testStructure() {
		testEqualClasses(MyIterator.class, IteratorSk.class);
		testEqualClasses(MyArray.class, ArraySk.class);
		testEqualClasses(Fibonacci.class, FibonacciSk.class);
	}

	void testArray() {
		initPublishedTest(MyArray.class, "array is {1, 3, 2}. iterating all, and then one more.");
		int[] a = { 1, 3, 2 };
		MyIterator it = new MyArray(a);
		checkIt(it, a, "array [1,3,2]");
		checkThrows(() -> it.next(), IndexOutOfBoundsException.class, "array [1,3,2] finished");
	}

	void testFibonnaci() {
		initPublishedTest(Fibonacci.class, "initialized with 10. iterating all, and then one more.");
		MyIterator it = new Fibonacci(10);
		checkIt(it, new int[] { 1, 1, 2, 3, 5, 8 }, "Fibonacci(10)");
		checkEq(it.next(), 8, "After end, should still return last element.");
	}

	void testIteratorToString() {
		initPublishedTest(Fibonacci.class, "Fibonnaci(20) toString");
		MyIterator it = new Fibonacci(20);
		checkEq(IteratorToString.toString(it), "[1 1 2 3 5 8 13]", " when called with new Fibonnaci(20)");
	}

	// ------------------------------------------------------------

	public static void main(String[] args) {
		new IteratorTester().myMain("iterator");
	}

	// ------------------------------------------------------------
	// Here you can choose which tests to run.

	public void myTests() {
		testStructure();
		testArray();
		testFibonnaci();
		testIteratorToString();
	}
}