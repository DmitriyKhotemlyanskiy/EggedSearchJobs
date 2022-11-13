package cities;

public class City implements Comparable<City> {
	private String name;
	private Country country;
	private int population;

	public City(String name, Country country, int population) {
		this.name = name;
		this.country = country;
		this.population = population;
	}

	public String getName() {
		return name;
	}

	public Country getCountry() {
		return country;
	}

	public int getPopulation() {
		return population;
	}

	public String toString() {
		String toRet = "";
		return toRet + getName() + " (of " + country.toString() + ")";
	}

	@Override
	public int compareTo(City o) {
		if (country.equals(o.getCountry()))
			return name.compareTo(o.getName());
		return country.compareTo(o.getCountry());
	}

	@Override
	public boolean equals(Object obj) {
		if (obj instanceof City)
			return country.equals(((City) obj).country);
		return false;
	}
}
