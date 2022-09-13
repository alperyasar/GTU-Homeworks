import java.util.*;

/**
 * An implementation of a graph that uses an array of lists to represent the edges
 * @author Alper YASAR
 *
 */
public class ListGraph extends AbstractGraph {
    //Data Fields
    /**
     * An array of Lists to contain the edges that originate with each vertex
     */
    private List<Edge>[] edges;

    /**
     * Construct a graph with the specified number of vertices and directionality
     * @param numV The number of vertices
     * @param directed The directionality flag
     */
    @SuppressWarnings("unchecked")
    public ListGraph(int numV, boolean directed) {
        super(numV, directed);
        edges = new List[numV];
        for(int i = 0; i < numV; i++){
            edges[i] = new LinkedList<Edge>();
        }
    }

    public boolean isEdge(int source, int dest){
        return edges[source].contains(new Edge(source, dest));
    }

    public void insert(Edge edge){
        edges[edge.getSource()].add(edge);
    }

    public Iterator<Edge> edgeIterator(int source){
        return edges[source].iterator();
    }

    public Edge getEdge(int source, int dest){
        Edge target = new Edge(source, dest);
        for(Edge edge : edges[source]){
            if(edge.equals(target))
                return edge; //Desired edge found; return it
        }
        //Assert: All edges for source checked.
        return target; //Desired edge not found.
    }

    public String toString(){
        StringBuilder sb = new StringBuilder();
        int end = edges.length;
        sb.append("\t ");
        for (int i=0; i < end; i++){
            sb.append( i + "     ");
        }
        sb.append("\n");
        for(int i=0; i < end; i++){
            sb.append(i + "   ");
            int j=0;
            for(Edge e : edges[i]){
                while (e.getDest() != j){
                    j++;
                    sb.append("      ");
                }
                j++;
                sb.append( e.toString() + "   ");
            }
            sb.append("\n");
        }
        return sb.toString();
    }

    @Override
    public void loadEdgesFromFile(Scanner scan){
        //System.out.println(edges.length);
        while(scan.hasNextLine())//while there are still more edges
        {
            Edge e = parseFileString(scan.nextLine());//parse a new Edge
            edges[e.getSource()].add(e); //Add the edge to the list of its source's edges
        }
        scan.close();
    }

    private Edge parseFileString(String input)
    {
        Edge toReturn = null;//initialize an Edge to return
        Scanner sc = new Scanner(input);//scan a line as an edge
        sc.useDelimiter(AbstractGraph.DELIM);//use only comma delimiter
        try
        { //in case we fail to parse anything, such as format didn't work
            int source = sc.nextInt();//scan x position of point

            int dest = sc.nextInt();//scan y position of point
            toReturn = new Edge(source, dest);
        }
        catch(Exception e)
        {
            System.out.println("Failed to parse Edge: "+input);
        }
        sc.close();//close scanner
        return toReturn;//return the scanned point
    }

}