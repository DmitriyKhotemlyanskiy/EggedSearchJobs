// 17466339

package shop;

import java.util.Arrays;
import java.util.List;

import util.Tester;

// Structure
class ShopSk {
	public ShopSk() {
	}
	
	public Instrument get(int serial) {
		return null;
	}

	public List<Integer> allSerials() {
		return null;
	}
	
	public List<Integer> guitarsOfType(Type t) {
		return null;
	}
	
	public void add(Instrument i) {
	}

	public void sell(int serial) throws MusicShopException {
	}

	public int sellAll(int[] serials) {
		return 0;
	}
}

@SuppressWarnings("serial")
class MusicShopExceptionSk extends Exception {
	public MusicShopExceptionSk(String msg) {
		super("");
	}
}

public class ShopTester extends Tester {

	void testStructure() {
		testEqualClasses(Shop.class, ShopSk.class);
		testEqualClasses(MusicShopException.class, MusicShopExceptionSk.class);
	}

	void testType() {
		initPublishedTest(Type.class);
		checkEqStr(Type.ACOUSTIC, "Acoustic", "toString of ACOUSTIC");
		checkEqStr(Type.ELECTRIC, "Electric", "toString of ELECTRIC");
		checkEqStr(Type.CLASSICAL, "Classical", "toString of CLASSICAL");
	}

	void testShop() throws MusicShopException {
		initPublishedTest(Shop.class);

		Guitar g = new Guitar("Gibson", 1000, Type.ACOUSTIC);
		checkEq(g.getPrice(), 1000, "g.getPrice()");
		checkEq(g.getCompany(), "Gibson", "g.getCompany()");
		checkEq(g.getType(), Type.ACOUSTIC, "g.getType()");
		checkEq(g.getSerial(), 0, "g.getSerial()");
		checkEqStr(g, "Guitar(Acoustic) Gibson(0), price = 1000", "g.toString()");

		Piano p = new Piano("Yamaha", 5000, 7);
		checkEq(p.getPrice(), 5000, "p.getPrice()");
		checkEq(p.getCompany(), "Yamaha", "p.getCompany()");
		checkEq(p.getOctaves(), 7, "p.getOctaves()");
		checkEq(p.getSerial(), 1, "p.getSerial()");
		checkEqStr(p, "Piano(7 octaves) Yamaha(1), price = 5000", "p.toString()");

		Shop s = new Shop();
		
		s.add(g);
		s.add(p);
		s.add(new Piano("Yamaha", 10000, 7));
		s.add(new Guitar("Fender", 4000, Type.ELECTRIC));

		checkEqStr(s.get(1), "Piano(7 octaves) Yamaha(1), price = 5000", "s.get(1)");
		checkSame(s.get(6), null, "s.get(6)");
		
		s.sell(2);
		checkThrows(() -> s.sell(10), MusicShopException.class,
				"Selling a non-existant item");
		
		s.add(new Guitar("Fender", 3000, Type.ACOUSTIC));
		s.add(new Piano("Steinway", 10000, 6));
		checkEq(s.allSerials(), Arrays.asList(0,1,3,4,5));
		checkEq(s.guitarsOfType(Type.ACOUSTIC), Arrays.asList(0, 4));
		checkEq(s.sellAll(new int[] { 1, 2, 3 }), 1, "sellAll(1,2,3)");
		checkEq(s.allSerials(), Arrays.asList(0,4,5));
		checkEqStr(s.get(4), "Guitar(Acoustic) Fender(4), price = 3000", "s.get(6)");
	}

	// ------------------------------------------------------------

	public static void main(String[] args) {
		new ShopTester().myMain("shop");
	}

	// ------------------------------------------------------------
	// Here you can choose which tests to run.

	public void myTests() throws MusicShopException {
		testStructure();
		testType();
		testShop();
	}

}
