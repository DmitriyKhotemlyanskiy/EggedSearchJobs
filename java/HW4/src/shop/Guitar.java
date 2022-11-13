package shop;

public class Guitar extends Instrument{
	private Type type;
	private int serial;
	
	public Guitar(String company, int price, Type type) {
		super(company,price);
		this.type = Type.valueOf(type.name());
		serial = Instrument.getCounter();
	}
	
	public Type getType() {
		return Type.valueOf(type.name());
	}
	public int getSerial() {
		return serial;
	}
	
	@Override
	public String toString() {
		String toRet="";
		return toRet+"Guitar("+type.toString()+") "+getCompany()+
				"("+getSerial()+"), price = "+getPrice();
	}
}
