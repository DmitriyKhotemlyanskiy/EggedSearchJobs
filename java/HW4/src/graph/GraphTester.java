// 20202946
package graph;

import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;

import util.Tester;
import util.Tester.Optional;

// Structure

class PlaceSk {
	public PlaceSk(int x, int y, int max) {
	}

	public int getX() {
		return 0;
	}

	public int getY() {
		return 0;
	}

	public boolean equals(Object o) {
		return false;
	}

	public int hashCode() {
		return 0;
	}

	@Optional
	public boolean equals(int x, int y) {
		return false;
	}
}

class GraphSk<V> {
	public GraphSk() {
	}

	public void addVertex(V v) throws GraphException {
	}

	public void addEdge(V v1, V v2) throws GraphException {
	}

	public boolean hasEdge(V v1, V v2) {
		return false;
	}

	public boolean connected(V v1, V v2) throws GraphException {
		return false;
	}
}

@SuppressWarnings("serial")
class GraphExceptionSk extends Exception {
	public GraphExceptionSk(String msg) {
		super(msg);
	}
}

class ConnectionCheckerSk<V> {
	public ConnectionCheckerSk(GraphInterface<V> g) {
	}

	public boolean check(V v1, V v2) {
		return false;
	}
}

//--------------------------------------------------------------------

class MazeSk implements GraphInterface<Place> {
	public MazeSk(int size, int startx, int starty, int endx, int endy) {
	}

	public boolean addWall(int x, int y) {
		return false;
	}

	public boolean isSolvable() {
		return false;
	}

	public String toString() {
		return null;
	}

	public Collection<Place> neighbours(Place v) {
		return null;
	}
}

public class GraphTester extends Tester {

	void testStructure() {
		testEqualClasses(Place.class, PlaceSk.class);
		testEqualClasses(Graph.class, GraphSk.class);
		testEqualClasses(GraphException.class, GraphExceptionSk.class);
		testEqualClasses(Maze.class, MazeSk.class);
		testEqualClasses(ConnectionChecker.class, ConnectionCheckerSk.class);
	}

	private Maze simpleMaze() {
		Maze m = new Maze(4, 0, 0, 3, 3);
		m.addWall(1, 1);
		m.addWall(3, 1);
		m.addWall(0, 1);
		m.addWall(2, 3);
		m.addWall(2, 3);
		m.addWall(1, 3);
		return m;
	}

	void testPlace() {
		initPublishedTest(Place.class);
		Place p = new Place(3, 10, 20);
		checkEq(p.getX(), 3, "getX");
		checkEq(p.getY(), 10, "geyY");
		checkThrows(() -> new Place(3, 10, 8), IllegalArgumentException.class, "y too large");
		checkThrows(() -> new Place(10, 3, 8), IllegalArgumentException.class, "x too large");
	}

	void testMaze() {
		initPublishedTest(Maze.class);
		Maze m = simpleMaze();
		checkEqStr(m, "S@..\n" + ".@.@\n" + "...@\n" + ".@.E\n", "");
	}

	void testGraph() throws GraphException {
		initPublishedTest(Graph.class);
		Graph<String> g = new Graph<>();
		g.addVertex("A");
		g.addVertex("B");
		g.addEdge("A", "B");
		g.addVertex("C");
		g.addEdge("C", "B");
		g.addVertex("D");
		g.addVertex("E");
		g.addEdge("D", "E");

		checkThrows(() -> g.addVertex("A"), GraphException.class, "Adding an existing vertex");
		checkThrows(() -> g.addEdge("B", "C"), GraphException.class, "Adding an existing edge");
		checkThrows(() -> g.addEdge("B", "F"), GraphException.class, "Adding an edge with non-existent vertex");
		check(g.connected("A", "C"), "connected 1");
		check(g.connected("C", "A"), "connected 2");
		check(!g.connected("D", "A"), "connected 3");
		checkThrows(() -> g.connected("A", "W"), GraphException.class, "connected() with non-existent vertex");
	}

	void testMaze2() {
		initPublishedTest("checking isSolvable()");
		Maze m = simpleMaze();
		check(m.isSolvable(), "");
		m.addWall(2, 2);
		check(!m.isSolvable(), "");
	}

	private static class GIExample implements GraphInterface<Integer> {
		@Override
		public Collection<Integer> neighbours(Integer v) {
			if (v == 0)
				return Arrays.asList(1, 2);
			else if (v == 1)
				return Arrays.asList(0);
			else if (v == 2)
				return Arrays.asList(0, 4);
			else if (v == 4)
				return Arrays.asList(2);
			else
				return Collections.emptyList();
		}
	}

	void testConnectionChecker() {
		initPublishedTest(ConnectionChecker.class);
		GraphInterface<Integer> g = new GIExample();
		ConnectionChecker<Integer> cc = new ConnectionChecker<>(g);
		check(cc.check(1, 4), "check(1, 4)");
		check(!cc.check(3, 4), "check(3, 4)");
	}

	void testMaze3() {
		initPublishedTest(ConnectionChecker.class, "Checking the basic maze");

		Maze m = simpleMaze();
		ConnectionChecker<Place> cc = new ConnectionChecker<>(m);
		check(cc.check(new Place(0, 0, 4), new Place(3, 3, 4)), "");
	}

	// -------------------------------------------------------------------------------
	// main

	// ------------------------------------------------------------

	public static void main(String[] args) {
		new GraphTester().myMain("graph");
	}

	// ------------------------------------------------------------
	// Here you can choose which tests to run.

	public void myTests() throws GraphException {
		testStructure();
		testPlace();
		testMaze();
		testGraph();
		testMaze2();
		testConnectionChecker();
		testMaze3();
	}
}
