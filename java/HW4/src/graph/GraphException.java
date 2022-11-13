package graph;

public class GraphException extends Exception {
	public GraphException(String s) {
		super("GraphException in:" + s);
	}

}
