package graph;

import java.util.*;

public interface GraphInterface<V> {
	public Collection<V> neighbours(V v);
}