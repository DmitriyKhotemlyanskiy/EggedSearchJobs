package graph;

public class Main {

	public static void main(String[] args) {
		Maze m = new Maze(4, 0, 0, 3, 3);
		m.addWall(1, 1);
		m.addWall(3, 1);
		m.addWall(0, 1);
		m.addWall(2, 3);
		m.addWall(2, 3);
		m.addWall(1, 3);
		ConnectionChecker<Place> cc = new ConnectionChecker<>(m);
		System.out.println(cc.check(new Place(0,0,4), new Place(3,3,4)));

	}

}
