package shop;

public class Main {

	public static void main(String[] args) throws MusicShopException{
		Shop s = new Shop();
		s.add(new Guitar("Gibson", 1000, Type.ACOUSTIC));
		s.add(new Piano("Yamaha", 5000, 6));
		s.add(new Piano("Yamaha", 10000, 7));
		s.add(new Guitar("Fender", 4000, Type.ELECTRIC));

		System.out.println(s.allSerials());
		System.out.println(s.sellAll(new int[] {1, 3, 5, 0}));
		System.out.println(s.allSerials());

	}

}
