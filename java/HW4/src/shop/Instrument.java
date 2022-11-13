package shop;

public abstract class Instrument {
	private int price;
	private String company;
	private static int counter=0;

	public Instrument(String company, int price) {
		this.company = company;
		this.price = price;
		SerialAdd();
	}

	private void SerialAdd() {
		counter++;
	}

	public static int getCounter() {
		return counter-1;
	}

	public int getPrice() {
		return price;
	}

	public String getCompany() {
		return company;
	}

	public abstract String toString();
	public abstract int getSerial();
	public abstract Type getType();
}
