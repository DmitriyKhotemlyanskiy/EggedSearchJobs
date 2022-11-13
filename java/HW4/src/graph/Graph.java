package graph;

import java.util.*;

public class Graph<V> {
	private Set<V> vertices = new HashSet<V>();
	private Map<V, Set<V>> edges = new HashMap<>();
	private Set<V> VisetdeVertices;

	public void addVertex(V v) throws GraphException {
		isInGraph(v);
		vertices.add(v);
	}

	public void addEdge(V v1, V v2) throws GraphException {
		isInNGraph(v1);
		isInNGraph(v2);
		AreNeighborS(v1, v2);
		NewNeighborS(v1, v2);
	}

	public boolean hasEdge(V v1, V v2) {
		Set<V> edge = edges.get(v1);
		if (edge == null)
			return false;
		else if (!(edge.contains(v2)))
			return false;
		Set<V> edge2 = edges.get(v2);
		if (edge2 == null)
			return false;
		if (!(edge2.contains(v1)))
			return false;
		return true;
	}

	public boolean connected(V v1, V v2) throws GraphException {
		isInNGraph(v1);
		isInNGraph(v2);
		VisetdeVertices = new HashSet<V>();
		return goDeep(v1, v2);

	}

	private boolean goDeep(V Vin, V Vwant) {
		if (VisetdeVertices.contains(Vin))
			return false;
		VisetdeVertices.add(Vin);
		Set<V> Neighbor = edges.get(Vin);
		for (V i : Neighbor) {
			if (i == Vwant)
				return true;
			if (goDeep(i, Vwant) == true)
				return true;
		}
		return false;

	}

	private void isInGraph(V v) throws GraphException {
		if (vertices.contains(v))
			throw new GraphException("Vertex already in Graph");
	}

	private void isInNGraph(V v) throws GraphException {
		if (!(vertices.contains(v)))
			throw new GraphException("Vertex not in Graph");
	}

	private void AreNeighborS(V v1, V v2) throws GraphException {
		if (hasEdge(v1, v2))
			throw new GraphException("Vertex neighbor already");
	}

	private void NewNeighborS(V v1, V v2) {
		Set<V> edge = edges.get(v1);
		if (edge == null) {
			edge = new HashSet<V>();
			edges.put(v1, edge);
		}
		edge.add(v2);
		Set<V> edge2 = edges.get(v2);
		if (edge2 == null) {
			edge2 = new HashSet<V>();
			edges.put(v2, edge2);
		}
		edge2.add(v1);
	}

}
