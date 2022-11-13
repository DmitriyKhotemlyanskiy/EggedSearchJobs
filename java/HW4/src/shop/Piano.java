package shop;

public class Piano extends Instrument {
	private int octaves;
	private int serial;

	public Piano(String company, int price, int octaves) {
		super(company, price);
		this.octaves = octaves;
		serial = Instrument.getCounter();
	}

	public int getOctaves() {
		return octaves;
	}

	public int getSerial() {
		return serial;
	}

	@Override
	public String toString() {
		String toRet = "";
		return toRet + "Piano(" + getOctaves() + " octaves) " + getCompany() + "(" + getSerial() + "), price = "
				+ getPrice();
	}

	@Override
	public Type getType() {
		return null;
	}
}
