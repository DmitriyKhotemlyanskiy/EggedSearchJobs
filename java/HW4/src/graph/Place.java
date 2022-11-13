package graph;

public class Place {
	private int x;
	private int y;

	public Place(int x, int y, int bound) {
		if (!(x < bound && x >= 0) || !(y < bound && y >= 0))
			throw new IllegalArgumentException();
		this.x = x;
		this.y = y;
	}

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}

	@Override
	public int hashCode() {
		return y * 128 + x;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o)
			return true;
		if (!(o instanceof Place))
			return false;
		return (x == ((Place) o).getX() && y == ((Place) o).getY());
	}

}
