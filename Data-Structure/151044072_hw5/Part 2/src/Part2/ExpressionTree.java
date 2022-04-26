package Part2;


import java.util.Scanner;

public class ExpressionTree<E extends Comparable<E>> extends BinaryTree<E> {
 //   private String str;
    Scanner in;
    BinaryTree<String> node;
    ExpressionTree(String str){
        root = new Node(str);
        in = new Scanner(toString());
       node = readBinaryTree(in);
        System.out.print(node);
     //   this.toString();

    }

    @Override
    public BinaryTree<String> readBinaryTree(Scanner Scan) {
        if(Scan.hasNext()){
            String data = Scan.next();
            if (!(data.equals("null"))) {
                BinaryTree<String> leftTree, rightTree;
                    leftTree = readBinaryTree(Scan);
                    rightTree = readBinaryTree(Scan);
                return new BinaryTree<String>(data, leftTree, rightTree);
            }
        }
        return null;
     /*   if(Scan.hasNext()) {
           node = super.readBinaryTree(Scan);
            //System.out.println(node);
            return node;
        }
        else
            return null;*/
    }
    private boolean operator(String data){
        if(data.equals("+")  || data.equals("-")  || data.equals("*")  || data.equals("/") )
            return true;
        return false;
    }
    public static int eval(){
        return 0;
    }
}
