package cities;

import java.util.*;

public class World {
	private Map<String, Country> countries;

	public World() {
		countries = new HashMap<>();
	}

	public void addCountry(String name) {
		countries.put(name, new Country(name));
	}

	public void addCity(String name, String countryName, int population) throws IllegalArgumentException {

		try {
			countries.get(countryName).addCity(new City(name, countries.get(countryName), population));
		} catch (IllegalArgumentException e) {
			throw new IllegalArgumentException("A country with that name does not exist");
		}
	}

	public int population() {
		int toRet = 0;
		for (Map.Entry<String, Country> i : countries.entrySet()) {
			toRet += i.getValue().population();
		}
		return toRet;
	}

	public List<City> smallCities(int under) {
		Set<Country> countryTree = new TreeSet<Country>();
		List<City> cityList = new LinkedList<City>();
		for (Map.Entry<String, Country> i : countries.entrySet()) {
			countryTree.add(i.getValue());
		}
		for (Country i : countryTree) {
			cityList.addAll(i.smallCities(under));
		}
		return cityList;
	}

	public String report() {
		String toRet = "";
		for (Map.Entry<String, Country> i : countries.entrySet()) {
			toRet += i.getValue().report() + "\n";
		}
		toRet += "Total population is " + population() + "\n";
		return toRet;
	}
}
