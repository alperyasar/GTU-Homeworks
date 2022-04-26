/**
 * Edge class for implementing graphs. Vertices are represented by the type int
 * @author Alper YASAR
 *
 */
public class Edge {
    //Data Fields
    /**
     * Destination vertex for an edge
     */
    private int dest;
    /**
     * Source vertex for an edge
     */
    private int source;

    //Constructors
    /**
     * Construct an edge from source to dest and sets weight to 1.0
     * @param source The source vertex for the edge
     * @param dest The destination vertex for the edge
     */
    public Edge(int source, int dest){
        this.source = source;
        this.dest = dest;
    }


    //Methods
    /**
     * Compares two edges for equality. Edges are equal if their source and destination vertices are the same.
     *    Weight is not considered.
     * @param e The edge we are comparing to.
     * @return true if equals
     */
    public boolean equals(Edge e){
        return (this.source == e.source && this.dest == e.dest);
    }

    /**
     * Getter for destination vertex
     * @return The destination vertex of this edge
     */
    public int getDest(){
        return this.dest;
    }

    /**
     * Getter for source vertex
     * @return The source vertex of this edge
     */
    public int getSource(){
        return this.source;
    }


    /**
     * Return the hash code for an edge. The hash code depends only on the source and destination
     * @return The hash code for this edge
     */
    public int hashCode(){
        return Integer.hashCode(source) + Integer.hashCode(dest);
    }

    /**
     * String representation of edge
     */
    public String toString(){
        return source + "." + dest;
    }

}
