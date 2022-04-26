/**
 * Tester class for graphs
 * @author Alper YASAR
 *
 */
public class Test {
    public static void main(String[] args){

        try {
            Graph g = AbstractGraph.createGraph(false, "List");
            System.out.println(g.toString());
        } catch(Exception e){
            e.printStackTrace();
        }
    }
}