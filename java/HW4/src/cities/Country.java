package cities;

import java.util.*;

public class Country implements Comparable<Country> {
	private String name;
	private Set<City> cities;

	public Country(String name) {
		this.name = name;
		cities = new TreeSet<City>();
	}

	public void addCity(City city) throws IllegalArgumentException {
		if (equals(city.getCountry()))
			cities.add(city);
		else
			throw new IllegalArgumentException();
	}

	public int population() {
		int toRet = 0;
		for (City i : cities)
			toRet += i.getPopulation();
		return toRet;
	}

	public String toString() {
		return name;
	}

	public List<City> smallCities(int under) {
		List<City> cityList = new LinkedList<City>();
		for (City i : cities) {
			if (i.getPopulation() < under)
				cityList.add(i);
		}
		return cityList;
	}

	@Override
	public int compareTo(Country o) {
		return name.compareTo(o.toString());
	}

	@Override
	public boolean equals(Object obj) {
		if (obj instanceof Country)
			return ((Country) obj).name.equals(name);
		return false;
	}

	public String report() {
		StringBuilder str = new StringBuilder();
		str.append(name + "(" + population() + ") : ");
		for (City city : cities) {
			str.append(city.getName() + "(" + city.getPopulation() + "), ");

		}
		str.delete(str.length() - 2, str.length()); // remove ", " in the end.
		return str.toString();
	}
}
