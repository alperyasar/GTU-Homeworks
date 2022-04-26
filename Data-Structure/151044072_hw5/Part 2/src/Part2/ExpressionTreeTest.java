package Part2;

public class ExpressionTreeTest {

    public static void main(String[] args) {
        //Create a tree for preorder expression
        ExpressionTree expTree = new ExpressionTree("+ + 10 * 5 15 20");
        //Create a tree for postorder expression
        ExpressionTree expTree2 = new ExpressionTree("10 5 15 * + 20 +");

        //Evaluate expressions
       // int result1 = expTree.eval();
     //   int result2 = expTree2.eval();

    }
}
