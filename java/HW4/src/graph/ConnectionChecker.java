package graph;

import java.util.*;

public class ConnectionChecker<V> {
	private Set<V> VisetdeVertices;
	private GraphInterface<V> G;
	
	public ConnectionChecker(GraphInterface<V> g) {
		G = g;
	}

	public boolean check(V v1, V v2) {
		VisetdeVertices = new HashSet<V>();
		return goDeep(v1, v2);
	}

	private boolean goDeep(V Vin, V Vwant) {
		if (VisetdeVertices.contains(Vin))
			return false;
		VisetdeVertices.add(Vin);
		Collection<V> Neighbor = G.neighbours(Vin);
		if (Neighbor != null) {
			for (V i : Neighbor) {
				if (i == null)
					return false;
				if (i.equals(Vwant))
					return true;
				if (goDeep(i, Vwant) == true)
					return true;
			}
		}
		return false;

	}
}