package shop;

import java.util.ArrayList;
import java.util.List;

public class Shop {
	private List<Instrument> shop = new ArrayList<Instrument>();

	public void add(Instrument i) {
		shop.add(i);
	}

	public Instrument get(int serial) throws MusicShopException {
		try {
			if (shop.get(serial) != null)
				return shop.get(serial);
		} catch (IndexOutOfBoundsException e) {
			throw new MusicShopException();
		}
		return null;

	}

	public List<Integer> allSerials() {
		List<Integer> toRet = new ArrayList<Integer>();
		for (Instrument i : shop) {
			toRet.add(i.getSerial());
		}
		return toRet;
	}

	public List<Integer> guitarsOfType(Type t) throws MusicShopException {
		List<Integer> toRet = new ArrayList<Integer>();
		for (Instrument i : shop) {
			if (get(i.getSerial()).getType() == t)
				toRet.add(i.getSerial());
		}
		return toRet;
	}

	public void sell(int serial) throws MusicShopException {
		int serialOfInstrument = 0;
		int count = 0;

		for (Instrument i : shop) {
			if (i.getType() != null)
				count++;
		}
		if (count <= 1)
			new MusicShopException("Sorry, we have only 1 guitar");
			try {
				for (Instrument j : shop) {
					if (j.getSerial() == serial) {
						shop.remove(serialOfInstrument);
						return;
					}
					serialOfInstrument++;
				}
			} catch (IndexOutOfBoundsException e) {
				new MusicShopException("Item with this serial not found");
			}

		
	}

	public int sellAll(int[] serials) throws MusicShopException {
		int i = 0, j = 0, toCompare;
		while (i < shop.size() || j < serials.length) {
			try {
				toCompare = ((Instrument) shop.get(i)).getSerial();
				if (toCompare == serials[j]) {
					sell(toCompare);
					continue;
				}
				if (toCompare < serials[j]) {
					i++;
					continue;
				} else
					j++;

			} catch (MusicShopException e) {
				throw e;
			} catch (Exception e) {
				new ArrayIndexOutOfBoundsException();
				break;
			}
		}
		return allSerials().size();
	}

}
