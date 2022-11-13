package shop;

public enum Type {
	ACOUSTIC("Acoustic"), ELECTRIC("Electric"), CLASSICAL("Classical");

	private String name;

	Type(String name) {
		this.name = name;
	}

	public String toString() {
		return name;
	}
}
