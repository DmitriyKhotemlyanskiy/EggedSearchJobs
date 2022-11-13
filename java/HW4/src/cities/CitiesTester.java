// 1724871
package cities;

import java.util.List;

import util.Tester;
import util.Tester.Optional;

// Structure
class CitySk implements Comparable<City> {
	public CitySk(String name, Country country, int population) {
	}

	public String getName() {
		return null;
	}

	public Country getCountry() {
		return null;
	}

	public int getPopulation() {
		return 0;
	}

	public String toString() {
		return null;
	}

	public boolean equals(Object o) {
		return false;
	}

	public int compareTo(City other) {
		return 0;
	}
}

class CountrySk implements Comparable<Country> {
	public CountrySk(String name) {
	}

	public void addCity(City city) {
	}

	public int population() {
		return 0;
	}

	public String toString() {
		return null;
	}

	public List<City> smallCities(int under) {
		return null;
	}

	public String report() {
		return null;
	}

	public int compareTo(Country o) {
		return 0;
	}
	
	@Optional
	public boolean equals(Object other) {
		return false;
	}
}

class WorldSk {
	public WorldSk() {
	}

	public void addCountry(String name) {
	}

	public void addCity(String name, String countryName, int population) {
	}

	public int population() {
		return 0;
	}
	public String report() {
		return null;
	}
	public List<City> smallCities(int under) {
		return null;
	}

}

public class CitiesTester extends Tester {

	void testStructure() {
		testEqualClasses(City.class, CitySk.class);
		testEqualClasses(Country.class, CountrySk.class);
		testEqualClasses(World.class, WorldSk.class);
	}

	void testCity() {
		initPublishedTest(City.class);
		Country country = new Country("USA");
		City c = new City("Chicago", country, 10);
		checkEq(c.getCountry(), country, "getCountry");
		checkEq(c.getName(), "Chicago", "getName");
		checkEq(c.getPopulation(), 10, "getName");
		checkEq(c.toString(), "Chicago (of USA)", "toString");
		City c2 = new City("Chicago", country, 100);
		check(((Object) c).equals((Object) c2),
				"different City instances that have the same name and the same country should be equal. "
						+ "\nIf you wrote equals(City) instead of equals(Object) this will happen.");
	}

	void testCountry() {
		initPublishedTest(Country.class);
		Country country = new Country("USA");
		City c = new City("Chicago", country, 10);
		City c2 = new City("Detroit", country, 100);
		country.addCity(c);
		country.addCity(c2);
		checkEq(country.population(), 110, "population()");
		checkEq(country.report(), "USA(110) : Chicago(10), Detroit(100)", "report()");

		checkEq(country.smallCities(40).toString(), "[Chicago (of USA)]", "smallCities()");

		City c3 = new City("Chicago", country, 1000);
		country.addCity(c3);
		checkEq(country.report(), "USA(110) : Chicago(10), Detroit(100)",
				"adding a copy of the same city should not work");

		City c4 = new City("Istanbul", new Country("Turkey"), 1);
		checkThrows(() -> {
			country.addCity(c4);
		}, IllegalArgumentException.class, "adding a city of a different country");
	}

	void testWorld() {
		initPublishedTest(World.class);
		World w = new World();
		w.addCountry("Brazil");
		w.addCity("Salvador", "Brazil", 2677000);
		w.addCountry("Spain");
		w.addCity("Barcelona", "Spain", 1615000);
		w.addCity("Rio de Janeiro", "Brazil", 6320000);
		w.addCity("Granada", "Spain", 233764);

		checkEqStr(w.report(),
				"Brazil(8997000) : Rio de Janeiro(6320000), Salvador(2677000)\n"
						+ "Spain(1848764) : Barcelona(1615000), Granada(233764)\n" + "Total population is 10845764\n",
				"report()");
		checkEq(w.smallCities(2000000).toString(), "[Barcelona (of Spain), Granada (of Spain)]", "smallCities");
	}

	// ------------------------------------------------------------

	public static void main(String[] args) {
		new CitiesTester().myMain("cities");
	}

	// ------------------------------------------------------------
	// Here you can choose which tests to run.

	public void myTests() {
		testStructure();
		testCity();
		testCountry();
		testWorld();
	}
}
