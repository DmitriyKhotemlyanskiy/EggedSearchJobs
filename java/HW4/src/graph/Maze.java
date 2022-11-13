package graph;

import java.util.*;

public class Maze implements GraphInterface<Place> {
	private int[][] maze;
	private int size;
	private Place[][] placDarr = null;;
	private Graph<Place> G;

	public Maze(int size, int startx, int starty, int endx, int endy) {
		this.size = size;

		placDarr = new Place[size][size];

		IsInRange(startx);
		IsInRange(starty);
		IsInRange(endx);
		IsInRange(endy);
		maze = new int[size][size];
		cleanMaze();
		addKind(startx, starty, 1);
		addKind(endx, endy, 2);
	}

	public boolean addWall(int x, int y) {
		IsInRange(x);
		IsInRange(y);
		return addKind(x, y, -1);
	}

	public String toString() {
		StringBuilder sb = new StringBuilder();
		int i, j;
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				if (maze[i][j] == 0)
					sb.append(".");
				if (maze[i][j] == -1)
					sb.append("@");
				if (maze[i][j] == 1)
					sb.append("S");
				if (maze[i][j] == 2)
					sb.append("E");
			}
			sb.append("\n");
		}

		return sb.toString();
	}

	public boolean isSolvable() {

		Place start = null;
		Place end = null;
		int i, j;
		try {
			Creat_PlaceMaze_G();
		} catch (GraphException e1) {
			e1.printStackTrace();
		}
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {

				if (maze[i][j] == 1) {
					start = placDarr[i][j];
					NeighborsToGraph(i, j);
				}
				if (maze[i][j] == 2) {
					end = placDarr[i][j];
					NeighborsToGraph(i, j);
				}
				if (maze[i][j] == 0) {
					NeighborsToGraph(i, j);
				}

			}
		}

		try {
			return G.connected(start, end);
		} catch (GraphException e) {
			e.printStackTrace();
		}
		return false;
	}

	private void NeighborsToGraph(int i, int j) {
		Neighbors(i, j, i - 1, j);
		Neighbors(i, j, i + 1, j);
		Neighbors(i, j, i, j - 1);
		Neighbors(i, j, i, j + 1);

	}
	/*
	 * private void Neighbors(int i, int j,int it,int jt,Map<Place, Set<Place>>
	 * edgesInd) 1. testing the Neighbor in in range (if not leave) 2. testing if
	 * its not a wall 3.add addEdge 4.add to vertices neighbor lists
	 */

	private void Neighbors(int i, int j, int it, int jt) {

		if (IsInRangeNoException(it) && IsInRangeNoException(jt)) {

			if (!(maze[it][jt] == -1)) {
				try {
					G.addEdge(placDarr[i][j], placDarr[it][jt]);
				} catch (GraphException e) {
				}
			}

		}

	}

	private void Creat_PlaceMaze_G() throws GraphException {
		G = new Graph<>();
		int i, j;
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				Place p = new Place(i, j, size);
				placDarr[i][j] = p;
				G.addVertex(placDarr[i][j]);
			}
		}
	}

	private void Creat_PlaceMaze_P() {
		if (placDarr[0][0] == null) {
			int i, j;
			for (i = 0; i < size; i++) {
				for (j = 0; j < size; j++) {
					Place p = new Place(i, j, size);
					placDarr[i][j] = p;
				}
			}
		}
	}

	private void cleanMaze() {
		int i, j;
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				maze[i][j] = 0;
			}
		}
	}

	private void IsInRange(int index) {
		if (index >= size || index < 0)
			throw new IllegalArgumentException();
	}

	private boolean IsInRangeNoException(int index) {
		if (index >= size || index < 0)
			return false;
		return true;
	}

	private boolean addKind(int x, int y, int kind) {
		if (maze[x][y] == 1 || maze[x][y] == 2 || maze[x][y] == -1)
			return false;
		maze[x][y] = kind;
		return true;
	}

	@Override
	public Collection<Place> neighbours(Place v) {
		if (v == null)
			return null;
		HashSet<Place> hasH = new HashSet<>();
		int x = v.getX();
		int y = v.getY();
		Creat_PlaceMaze_P();
		NeighborsToPlace(x - 1, y, hasH);
		NeighborsToPlace(x + 1, y, hasH);
		NeighborsToPlace(x, y - 1, hasH);
		NeighborsToPlace(x, y + 1, hasH);
		return hasH;
	}

	private void NeighborsToPlace(int xt, int yt, HashSet<Place> hasH) {
		if (IsInRangeNoException(xt) && IsInRangeNoException(yt)) {
			if (!(maze[xt][yt] == -1)) {
				hasH.add(placDarr[xt][yt]);
			}
		}
	}

}
