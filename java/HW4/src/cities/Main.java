package cities;

public class Main {

	public static void main(String[] args) {
		World w = new World();
		w.addCountry("Spain");
		w.addCity("Granada", "Spain", 233764);
		w.addCountry("Brazil");
		w.addCity("Salvador", "Brazil", 2677000);
		w.addCity("Barcelona", "Spain", 1615000);
		w.addCity("Rio de Janeiro", "Brazil", 6320000);

		System.out.println(w.report());
		int bound = 2000000;
		System.out.println("Cities with population under " + bound + ":");
		System.out.println(w.smallCities(bound));

	}

}
